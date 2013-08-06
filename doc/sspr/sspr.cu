#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "cuda_runtime.h"
#include "cublas_v2.h"

/** SSPR - performs the symmetric rank 1 operation A := alpha*x*x**T + A */

/** print both to console and log file */

void print(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	vprintf(fmt, args);
	FILE *file = fopen("sspr.log", "a");
	vfprintf(file, fmt, args);

	va_end(args);
}

static struct cudaDeviceProp capabilities;
static size_t cudaMemGetInfo_free = 0;

/**
 * display error and exit
 *
 * \param msg error message
 * \param ret error code
 * \param desc error description
 */

static int err(char *msg, int ret, const char *desc)
{
	fprintf(stderr, msg, ret, desc);
	exit(EXIT_FAILURE);
}

static char *cublas2str[] = {
	"CUBLAS_STATUS_SUCCESS", /* 0 */
	"CUBLAS_STATUS_NOT_INITIALIZED",
	"unknown",
	"unknown",
	"unknown",
	"unknown", /* 5 */
	"unknown",
	"CUBLAS_STATUS_INVALID_VALUE",
	"unknown",
	"unknown",
	"unknown", /* 10 */
	"CUBLAS_STATUS_MAPPING_ERROR",
};

#define PACKED_SIZE(n) (n * (n + 1) / 2)

#define PRINT(field, format) printf(#field " = " format "\n", field);
#define PRINT_DIV(field, format, divisor)			\
	printf(#field " = " format "\n", field / divisor);
#define PRINT_DIM(field, format)					\
	printf(#field " = " format "\n", field[0], field[1], field[2]);

/** query CUDA device capabilities */

static void cuda_capabilities(void)
{
	cudaError_t ret = cudaGetDeviceProperties(&capabilities, 0);
	if (ret == cudaSuccess) {
		printf("\nDEVICE\n------\n");

		PRINT(capabilities.name, "%s");
		PRINT_DIV(capabilities.totalGlobalMem,
			  "%.2f MB",
			  1024.0f / 1024.0f);
		PRINT_DIV(capabilities.sharedMemPerBlock, "%.2f KB", 1024.0f);
		PRINT(capabilities.regsPerBlock, "%d"); 
		PRINT(capabilities.warpSize, "%d");
		PRINT_DIV(capabilities.memPitch, "%.2f KB", 1024.0f);
		PRINT(capabilities.maxThreadsPerBlock, "%d");
		PRINT_DIM(capabilities.maxThreadsDim, "%d %d %d");
		PRINT_DIM(capabilities.maxGridSize, "%d %d %d");
		PRINT_DIV(capabilities.totalConstMem, "%.2f KB", 1024.0f);
		PRINT(capabilities.major, "%d");
		PRINT(capabilities.minor, "%d");
		PRINT_DIV(capabilities.clockRate, "%.2f MHz", 1024.0f);
		PRINT(capabilities.textureAlignment, "%d");
		PRINT(capabilities.deviceOverlap, "%d");
		PRINT(capabilities.multiProcessorCount, "%d");

		ret = cudaMemGetInfo(&cudaMemGetInfo_free, NULL);
		if (ret != cudaSuccess)
			err("cudaMemGetInfo: %d (%s)",
			    ret, cudaGetErrorString(ret));
		printf("cudaMemGetInfo.free = %d MB\n",
		       cudaMemGetInfo_free / 1024 / 1024);
		printf("\n");
	} else
		err("cudaGetDeviceProperties: %d (%s)",
		    ret, cudaGetErrorString(ret));
}

/** gettimeofday() is not available in Windows, timezone not supported */

#define WINDOWS 1
#if WINDOWS == 1

#include <windows.h>

struct timezone 
{
	int tz_minuteswest; /* minutes W of Greenwich */
	int tz_dsttime;     /* type of dst correction */
};

static int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
 
	if (NULL != tv) {
		GetSystemTimeAsFileTime(&ft);
 
		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
#undef DELTA_EPOCH_IN_MICROSECS

		tmpres /= 10;

		tv->tv_sec = (long) (tmpres / 1000000UL);
		tv->tv_usec = (long) (tmpres % 1000000UL);
	}
  
	return 0;
}
#endif /* WINDOWS */

/** get time in seconds */

static double wtime(void)
{
	struct timeval tv;
  	gettimeofday(&tv, NULL);

	return tv.tv_sec + tv.tv_usec / 1000000.0;
}

#define UPPER 1

/**
 * CPU naive implementation of SSPR
 *
 * Based on http://www.netlib.org/blas/sspr.f and GSL's source_spr.h
 * Only UPPER mode with incx == 1 is implemented
 */

static int sspr_cpu(int uplo,
		    int n,
		    const float alpha,
		    const float *x,
		    int incx,
		    float *ap)
{
	/* parameter check */
	if ((uplo != UPPER) ||
	    n < 0 ||
	    alpha == NULL || 
	    x == NULL ||
	    incx <= 0 ||
	    ap == NULL)
		return EINVAL;

	/* return if nothing to do */
	if (n == 0 || alpha == 0.0)
		return EXIT_SUCCESS;

	/* only UPPER mode with incx == 1 is implemented */
	if (uplo != UPPER || incx != 1)
		return ENOTSUP;

	int i = 0;
	for (i = 0; i < n; i++) {
		const float tmp = alpha * x[i];

		int j = 0;
		for (j = 0; j <= i; j++)
			ap[((i*(i+1))/ 2 + j)] += x[j] * tmp;
	}

	return EXIT_SUCCESS;
}

/** CUBLAS's SSPR call */

static int sspr_cublas(int uplo,
		       int n,
		       const float alpha,
		       const float *x,
		       int incx,
		       float *ap)
{
	cudaError_t ret = cudaSuccess;

	cublasHandle_t handle = NULL;
	cublasStatus_t status = cublasCreate(&handle);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasCreate: %d (%s)", status, cublas2str[status]);

	cublasFillMode_t mode = (uplo == UPPER) ?
		CUBLAS_FILL_MODE_UPPER : CUBLAS_FILL_MODE_LOWER;
	
	int packed_n = PACKED_SIZE(n);

	float *cx = NULL;
	ret = cudaMalloc(&cx, n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cx): %d (%s)", ret, cudaGetErrorString(ret));
		
	status = cublasSetVector(n, sizeof(float), x, 1, cx, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cudaSetVector (x): %d (%s)", status, cublas2str[status]);

	float *cap = NULL;
	ret = cudaMalloc(&cap, packed_n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cap): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasSetVector(packed_n, sizeof(float), ap, 1, cap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasSetVector (ap): %d (%s)", status, cublas2str[status]);

	status = cublasSspr(handle, mode, n, &alpha, cx, incx, cap);
	if (status != CUBLAS_STATUS_SUCCESS)
	 	err("cublasSspr: %d (%s)", status, cublas2str[status]);

	status = cublasGetVector(packed_n, sizeof(float), cap, 1, ap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasGetVector (ap): %d (%s)", status, cublas2str[status]);
			
	ret = cudaFree(cap);
	if (ret != cudaSuccess)
		err("cudaFree (cap): %d (%s)", ret, cudaGetErrorString(ret));

	ret = cudaFree(cx);
	if (ret != cudaSuccess)
		err("cudaFree (cx): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasDestroy(handle);
	if (status != CUBLAS_STATUS_SUCCESS)
                err("cublasDestroy: %d (%s)", status, cublas2str[status]);

	return EXIT_SUCCESS;
}

__global__ void sspr_naive_kernel(int uplo, int n, float alpha,
				  const float *x, int incx, float *ap)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < n) {
		const float tmp = alpha * x[i];

		int j = 0;
		for (j = 0; j <= i; j++)
			ap[((i*(i+1))/ 2 + j)] += x[j] * tmp;
	}
}

static int sspr_naive(int uplo,
		      int n,
		      const float alpha,
		      const float *x,
		      int incx,
		      float *ap)
{
	cudaError_t ret = cudaSuccess;

	cublasHandle_t handle = NULL;
	cublasStatus_t status = cublasCreate(&handle);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasCreate: %d (%s)", status, cublas2str[status]);
	
	int packed_n = PACKED_SIZE(n);

	float *cx = NULL;
	ret = cudaMalloc(&cx, n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cx): %d (%s)", ret, cudaGetErrorString(ret));
		
	status = cublasSetVector(n, sizeof(float), x, 1, cx, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cudaSetVector (x): %d (%s)", status, cublas2str[status]);

	float *cap = NULL;
	ret = cudaMalloc(&cap, packed_n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cap): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasSetVector(packed_n, sizeof(float), ap, 1, cap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasSetVector (ap): %d (%s)", status, cublas2str[status]);

	sspr_naive_kernel<<< (n / capabilities.maxThreadsPerBlock),
		(capabilities.maxThreadsPerBlock) >>>
		(uplo, n, alpha, cx, incx, cap);

	status = cublasGetVector(packed_n, sizeof(float), cap, 1, ap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasGetVector (ap): %d (%s)", status, cublas2str[status]);
			
	ret = cudaFree(cap);
	if (ret != cudaSuccess)
		err("cudaFree (cap): %d (%s)", ret, cudaGetErrorString(ret));

	ret = cudaFree(cx);
	if (ret != cudaSuccess)
		err("cudaFree (cx): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasDestroy(handle);
	if (status != CUBLAS_STATUS_SUCCESS)
                err("cublasDestroy: %d (%s)", status, cublas2str[status]);

	return EXIT_SUCCESS;
}

__global__ void sspr_optimized_kernel(int uplo, int n, float alpha,
				      const float *x, int incx, float *ap)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < n) {

		int tid = threadIdx.x;
		
		extern __shared__ float cache[];
		float *xi = (float *) cache;

		const float tmp = alpha * x[i];
		xi[tid] = x[i];

		int j = 0;
		for (j = 0; j <= i; j++) {
			ap[((i*(i+1))/ 2 + j)] += x[j] * tmp;
		}
	}
}

static int sspr_optimized(int uplo,
			  int n,
			  const float alpha,
			  const float *x,
			  int incx,
			  float *ap)
{
	cudaError_t ret = cudaSuccess;

	cublasHandle_t handle = NULL;
	cublasStatus_t status = cublasCreate(&handle);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasCreate: %d (%s)", status, cublas2str[status]);
	
	int packed_n = PACKED_SIZE(n);

	float *cx = NULL;
	ret = cudaMalloc(&cx, n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cx): %d (%s)", ret, cudaGetErrorString(ret));
		
	status = cublasSetVector(n, sizeof(float), x, 1, cx, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cudaSetVector (x): %d (%s)", status, cublas2str[status]);

	float *cap = NULL;
	ret = cudaMalloc(&cap, packed_n * sizeof(float));
	if (ret != cudaSuccess)
		err("cudaMalloc (cap): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasSetVector(packed_n, sizeof(float), ap, 1, cap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasSetVector (ap): %d (%s)", status, cublas2str[status]);

	sspr_optimized_kernel<<< (n / capabilities.maxThreadsPerBlock),
		(capabilities.maxThreadsPerBlock) >>>
		(uplo, n, alpha, cx, incx, cap);

	status = cublasGetVector(packed_n, sizeof(float), cap, 1, ap, 1);
	if (status != CUBLAS_STATUS_SUCCESS)
		err("cublasGetVector (ap): %d (%s)", status, cublas2str[status]);
			
	ret = cudaFree(cap);
	if (ret != cudaSuccess)
		err("cudaFree (cap): %d (%s)", ret, cudaGetErrorString(ret));

	ret = cudaFree(cx);
	if (ret != cudaSuccess)
		err("cudaFree (cx): %d (%s)", ret, cudaGetErrorString(ret));

	status = cublasDestroy(handle);
	if (status != CUBLAS_STATUS_SUCCESS)
                err("cublasDestroy: %d (%s)", status, cublas2str[status]);

	return EXIT_SUCCESS;
}

/** reduce all elements of a packed matrix of size n */

static float reduce(float *ap, int n)
{
	float res = 0.0;

	int i = 0;
	for (i = 0; i < n; i++)
		res += ap[i];

	return res;
}

static void frand(float *array, int size)
{
	srand(size);

	int i = 0;
	for (i = 0; i < size; i++)
		array[i] = 1.0f * rand() / RAND_MAX;
}

#define SSPR_N_DEFAULT (1 << 12)
#define SSPR_ALPHA_DEFAULT (3.14159265358979323846)

int main(int argc, char *argv[])
{
	cuda_capabilities();

	int n = ( getenv("SSPR_N") ) ? atoi(getenv("SSPR_N")) : SSPR_N_DEFAULT;

	const float alpha =
		(getenv("SSPR_ALPHA")) ?
		atof(getenv("SSPR_ALPHA")) : SSPR_ALPHA_DEFAULT;

	int packed_n = PACKED_SIZE(n);

	printf("INPUT\n-----\nSSPR_N = %d floats (packed %d floats)\nSSPR_ALPHA = %f\n",
	       n, packed_n, alpha);

	int x_bytes = n * sizeof(float);
	int ap_bytes = packed_n * sizeof(float);

	printf("memory = %d MB\n", (x_bytes + ap_bytes ) / 1024 / 1024);

	float *x = (float *) malloc(x_bytes);
	if (!x)
		err("malloc (x): %d (%s)", errno, strerror(errno));
	float *ap = (float *) malloc(ap_bytes);
	if (!ap)
		err("malloc (ap): %d (%s)", errno, strerror(errno));

	printf("\nSSPR\n----\n");

	int k = 0;
	for (k = 0; k < 1; k++) {
		{
			frand(x, n);
			frand(ap, packed_n);
			double start = wtime();			
			int ret = sspr_cpu(UPPER, n, alpha, x, 1, ap);
			double end = wtime();
			print("%s, %d, %f, %d, %f\n",
			      "sspr_cpu", n, end - start, ret, reduce(ap, packed_n));
		}
		{
			frand(x, n);
			frand(ap, packed_n);
			double start = wtime();			
			int ret = sspr_cublas(UPPER, n, alpha, x, 1, ap);
			double end = wtime();
			print("%s, %d, %f, %d, %f\n",
			      "sspr_cublas", n, end - start, ret, reduce(ap, packed_n));
		}
		{
			frand(x, n);
			frand(ap, packed_n);
			double start = wtime();			
			int ret = sspr_naive(UPPER, n, alpha, x, 1, ap);
			double end = wtime();
			print("%s, %d, %f, %d, %f\n",
			      "sspr_naive", n, end - start, ret, reduce(ap, packed_n));
		}
		{
			frand(x, n);
			frand(ap, packed_n);
			double start = wtime();			
			int ret = sspr_optimized(UPPER, n, alpha, x, 1, ap);
			double end = wtime();
			print("%s, %d, %f, %d, %f\n",
			      "sspr_optimized", n, end - start, ret, reduce(ap, packed_n));
		}
	}
	printf("\n");

	return 0;
}
