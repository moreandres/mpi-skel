#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "args.h"
#include "log.h"

#include <signal.h>

static void handler(int signum)
{
	int result;

	if (_log)
		result = log_destroy(_log);

	return;
}

static void setup_handler(void)
{

	printd("()");

	signal(SIGINT, handler);

	return;
}

int main(int argc, char *argv[])
{
	char *name = NULL;

	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	setup_handler();

	args = setup_argp(argc, argv);

	print_args(args);

#include <strings.h>

	name = rindex(argv[0], '/');
	if (name == NULL) {
		name = argv[0];
	} else {
		name++;
	}

	_log = log_create(name, 0);

	return 0;
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

	printd("(%p, %p, %d)", argc, argv, options);

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

	printd("(%p, %d)", mpi, options);

	assert(mpi != NULL);
	assert(options >= 0);

	result = MPI_Finalize();

	return result;
}
