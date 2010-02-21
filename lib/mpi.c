#include <stdlib.h>

#include "utils.h"
#include "mpi.h"

#include </usr/include/mpi.h>

struct mpi_data_s {
	int i;
};

static mpi_t *_mpi;

static int mpi_init(int *argc, char **argv[])
{

	int result = -1;
	mpi_t *mpi = NULL;

	printd("(%p, %p)", argc, argv);

	assert(argc != NULL);
	assert(argv != NULL);

	result = MPI_Init(argc, argv);

	mpi = calloc(1, sizeof(mpi_t));

	result = MPI_Comm_rank(MPI_COMM_WORLD, &mpi->rank);
	result = MPI_Comm_size(MPI_COMM_WORLD, &mpi->size);

#define HOSTNAME_SIZE 64

	mpi->name = calloc(HOSTNAME_SIZE, sizeof(char));

	result = MPI_Get_processor_name(mpi->name, &mpi->length);

	return 0;
}

static int mpi_finalize(void)
{

	int result = -1;

	printd("()");

	result = MPI_Finalize();

	return result;
}

mpi_t *get_mpi(void)
{
	if (_mpi == NULL) {
		_mpi = calloc(1, sizeof(mpi_t));
		_mpi->init = mpi_init;
		_mpi->finalize = mpi_finalize;
		_mpi->data = calloc(1, sizeof(struct mpi_data_s));
	}

	return _mpi;
}
