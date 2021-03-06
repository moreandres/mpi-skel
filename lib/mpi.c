#include <stdlib.h>

#include "utils.h"
#include "mpi.h"

#ifdef HAVE_MPI_H

#include "/usr/include/mpi.h"

#endif /* HAVE_MPI_H */

struct mpi_data_s {
	int i;
};

static mpi_t *_mpi;

static int mpi_init(int *argc, char **argv[])
{
	int error = 0;

	printd("(%p, %p)", argc, argv);

	assert(argc != NULL);
	assert(argv != NULL);

#ifdef HAVE_MPI_H

	error = MPI_Init(argc, argv);

	if (!error) {
		error = MPI_Comm_rank(MPI_COMM_WORLD, &_mpi->rank);
		error = MPI_Comm_size(MPI_COMM_WORLD, &_mpi->size);

#define HOSTNAME_SIZE 64

		_mpi->name = calloc(HOSTNAME_SIZE, sizeof(char));

		error = MPI_Get_processor_name(_mpi->name, &_mpi->length);
	}
#endif /* HAVE_MPI_H */

	return error;
}

static int mpi_finalize(void)
{

	int result = -1;

	printd("()");

#ifdef HAVE_MPI_H

	result = MPI_Finalize();
#endif
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
