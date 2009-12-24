#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "args.h"

int main(int argc, char *argv[])
{
	struct arguments arguments;

	/* argp handler? */
	arguments.verbose = 0;
	arguments.file = "-";

	argp_parse(&argp, argc, argv, 0, NULL, &arguments);

	/* signal handler? */

	/* mpi initialization? */

	return 0;
}

typedef struct pipeline_s {
} pipeline_t;

typedef void *(*fn_t) (void *args);

typedef struct stage_s {
	fn_t fn;
	int options;
} stage_t;

static void setup_signal_handler(void)
{

	return;
}

static void setup_mpi(void)
{

	return;
}

static void setup_driver(void)
{

	return;
}

static stage_t *stage_create(fn_t fn, int options)
{

	stage_t *stage = NULL;

	assert(fn != NULL);
	assert(options > 0);

	stage = calloc(1, sizeof(stage_t));

	stage->fn = fn;
	stage->options = options;

	return stage;
}

static int stage_destroy(stage_t *stage, int options)
{

	int result;

	assert(stage != NULL);
	assert(options >= 0);

	free(stage);
	stage = NULL;

	return result;
}

static int stage_execute(stage_t *stage, int options)
{

	int result = 1;

	assert(stage != NULL);
	assert(options >= 0);

	return result;
}

static void stage_show(stage_t *stage)
{

	assert(stage != NULL);

	return;
}

static pipeline_t *pipeline_create(stage_t **stages, int count, int options)
{

	pipeline_t *pipeline = NULL;
	int i = 0;

	assert(stages != NULL);
	assert(count > 0);
	assert(options >= 0);

	i = 1;

	pipeline = calloc(1, sizeof(pipeline_t));

	return pipeline;
}

static int pipeline_destroy(pipeline_t *pipeline, int options)
{

	int result = -1;

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

static int pipeline_start(pipeline_t *pipeline, int options)
{

	int result = -1;

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

static int pipeline_stop(pipeline_t *pipeline, int options)
{

	int result = -1;

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

static void pipeline_show(pipeline_t *pipeline, int options)
{

	printd("%p, %d", pipeline, options);

	assert(pipeline != NULL);
	assert(options >= 0);

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

	assert(mpi != NULL);
	assert(options >= 0);

	result = MPI_Finalize();

	return result;
}
