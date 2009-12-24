#include <stdlib.h>
#include <stdio.h>
#include <mpiskel.h>
#include <assert.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

static double *mm_init(int n)
{
	assert(n > 0);

	double *res = NULL;

	res = malloc(n * n * sizeof(double));

	srandom(time(NULL));

	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			res[i * n + j] = 1.0 * random() / RAND_MAX;

	return res;
}

static int mm_simple(double *a, double *b, double *c, int n)
{
	assert(a != NULL && b != NULL && c != NULL && n > 0);

	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				c[i * n + j] += a[i * n + k] * b[k * n + j];

	return 0;
}

double wtime(void)
{
	double sec;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec + tv.tv_usec / 1000000.0;
	return sec;
}

int mm_check(double *a, double *b, int n)
{
	assert(a != NULL && b != NULL && n > 0);

	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (fabs(a[i * n + j] - b[i * n + j]) > 0.000001)
				return -1;

		}

	return 0;
}
