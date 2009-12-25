#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "args.h"

int main(int argc, char *argv[])
{
	printd("%d, %p", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	args = setup_argp(argc, argv);

	print_args(args);

	return 0;
}

static void setup_signal_handler(void)
{

	printd("()");

	return;
}

static void setup_mpi(void)
{
	printd("()");

	return;
}

static void setup_driver(void)
{

	printd("()");

	return;
}

typedef struct log_s {
	int fd;
	char *name;
} log_t;

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME_SIZE 64

static log_t *log_create(int options)
{

	log_t *log = NULL;

	printd("%d", options);

	assert(options >= 0);

	log = calloc(1, sizeof(log_t));

	log->name = calloc(FILENAME_SIZE, sizeof(char));
	log->fd = open(log->name, 0);

	return log;
}

#include <unistd.h>

static int log_destroy(log_t *log)
{

	int result = -1;

	printd("%p", log);

	assert(log != NULL);

	free(log);
	log = NULL;

	result = close(log->fd);

	return result;
}

typedef struct mpi_s {
	int rank;
	int size;
	char *name;
	int length;
} mpi_t;

#include "/usr/lib/openmpi/1.3.2-gcc/include/mpi.h"

static mpi_t *mpi_init(int *argc, char **argv[], int options)
{

	int result = -1;
	mpi_t *mpi = NULL;

	printd("%p, %p, %d", argc, argv, options);

	assert(argc != NULL);
	assert(argv != NULL);
	assert(options >= 0);

	result = MPI_Init(argc, argv);

	result = MPI_Comm_rank(MPI_COMM_WORLD, &mpi->rank);
	result = MPI_Comm_size(MPI_COMM_WORLD, &mpi->size);
	result = MPI_Get_processor_name(mpi->name, &mpi->length);

	return mpi;
}

static int mpi_finalize(mpi_t *mpi, int options)
{

	int result = -1;

	printd("%p, %d", mpi, options);

	assert(mpi != NULL);
	assert(options >= 0);

	result = MPI_Finalize();

	return result;
}
