#include <stdlib.h>

#include "utils.h"
#include "mpi.h"

static mpi_t *_mpi;

mpi_t *get_mpi(void)
{
	return _mpi;
}

static mpi_t *mpi_init(int *argc, char **argv[], int options)
{

	int result = -1;
	mpi_t *mpi = NULL;

	printd("(%p, %p, %d)", argc, argv, options);

	assert(argc != NULL);
	assert(argv != NULL);
	assert(options >= 0);

	result = MPI_Init(argc, argv);

	mpi = calloc(1, sizeof(mpi_t));

	result = MPI_Comm_rank(MPI_COMM_WORLD, &mpi->rank);
	result = MPI_Comm_size(MPI_COMM_WORLD, &mpi->size);

#define HOSTNAME_SIZE 64

	mpi->name = calloc(HOSTNAME_SIZE, sizeof(char));

	result = MPI_Get_processor_name(mpi->name, &mpi->length);

	return mpi;
}

static int mpi_finalize(mpi_t *mpi, int options)
{

	int result = -1;

	printd("(%p, %d)", mpi, options);

	assert(mpi != NULL);
	assert(options >= 0);

	result = MPI_Finalize();

	return result;
}
