#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "args.h"
#include "log.h"

int main(int argc, char *argv[])
{
	printd("%d, %p", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	args = setup_argp(argc, argv);

	print_args(args);

	_log = log_create(0);

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
