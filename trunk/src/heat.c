/*
 * This program calculates heat distribution in parallel and outputs
 * data to be processed by gnuplot's pm3d.
 *
 * bugsto: more.andres@gmail.com
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>		/* memcpy, memset */
#include <assert.h>
#include <math.h>

/* Constants */

#define BASE 10			/* strtol */
#define MAX_ITER 50000		/* upper bound */

/* Debugging macro */

#if 0
#define DBG(fmt, args...) do {						\
		printf("%s:%d:%s(", __FILE__, __LINE__, __FUNCTION__);	\
		printf(fmt, ##args); printf(")\n"); } while (0)
#else
#define DBG(fmt, args...)	/* empty */
#endif

#define at(x, y) ((x) * length + (y))

/*
 * Parse arguments from command line.
 */

static void parse_arguments(const int argc, char *argv[],
			    int *length, int *x, int *y, int *heat, int *error)
{

	/* ./heat-omp <length> <x> <y> <heat> <error> */
	assert(argc == 6);

	char *tail = NULL;

	/* grid length */
	*length = strtol(argv[1], &tail, BASE);
	assert(*tail == 0);
	assert(*length > 0);

	/* heat X position */
	*x = strtol(argv[2], &tail, BASE);
	assert(*tail == 0);
	assert(*x > 0);
	assert(*x < *length);

	/* heat Y position */
	*y = strtol(argv[3], &tail, BASE);
	assert(*tail == 0);
	assert(*y > 0);
	assert(*y < *length);

	/* heat value */
	*heat = strtol(argv[4], &tail, BASE);
	assert(*tail == 0);
	assert(*heat > 0);

	/* error */
	*error = strtol(argv[5], &tail, BASE);
	assert(*tail == 0);
	assert(*error > 0);
}

static int main2(int argc, char *argv[])
{

	/* Get command line arguments */
	int length = -1;
	int error = -1;
	int x = -1;
	int y = -1;
	int heat = -1;
	parse_arguments(argc, argv, &length, &x, &y, &heat, &error);

	/* Allocate grid and helper */
	int bytes = sizeof(double) * length * length;
	assert(bytes > 0);
	double *grid = calloc(1, bytes);
	assert(grid != NULL);
	double *tmp = calloc(1, bytes);
	assert(tmp != NULL);

	double diff = RAND_MAX;

	int i = -1;
	int j = -1;
	int k = -1;

	/* Start threading support to avoid delays on each iteration */
	{
		/* Loop until reducing error or reaching maximum iterations */
		for (k = 0; k < MAX_ITER && diff > error; k++) {

			/* Create grid copy and place heat */
			memcpy(&tmp[0], &grid[0], bytes);
			tmp[at(x, y)] = heat;

			error = 0;
			double gap = -1;

			/* Parallel heat distribution */
			for (i = 1; i < length; i++) {
				for (j = 1; j < length; j++) {

					/* Update grid using neighbours average */
					grid[at(i, j)] =
						0.25 * (tmp[at(i, j - 1)] +
							tmp[at(i, j + 1)]
							+ tmp[at(i - 1, j)] +
							tmp[at(i + 1, j)]);

					/* Update max heat difference */
					gap =
						fabs(grid[at(i, j)] -
						     tmp[at(i, j)]);
					if (diff < gap) {
						diff = gap;
					}
				}
			}
		}
	}

	grid[at(x, y)] = heat;

	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			printf("%d %d %f\n", i, j, grid[at(i, j)]);
		}
		printf("\n");
	}

	return 0;
}

#include <mpiskel.h>
#include "pipe.h"
#include "utils.h"

static void *setup(void * params)
{
	printd("()");

	return NULL;
}

static void *work(void * params)
{
	printd("()");

	return NULL;
}

static void *reduce(void * params)
{
	printd("()");

	return NULL;
}

static pipe_t heat = {
	.name = "heat",
	.options = 0,
	.stages = {
		{ "setup", setup, 0, NULL, NULL },
		{ "work", work, 0, NULL, NULL },
		{ "reduce", reduce, 0, NULL, NULL },
	},
};

pipe_t *get(void)
{
	return &heat;
}
