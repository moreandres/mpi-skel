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
#include <mpiskel.h>
#include "pipe.h"
#include "utils.h"

/* Constants */

#define BASE 10			/* strtol */
#define MAX_ITER 50000		/* upper bound */
#define LENGTH 100              /* square grid size */

#define at(x, y) ((x) * LENGTH + (y))

typedef struct data_s {
	double *grid;
	double *tmp;
	int bytes;
} data_t;

static int setup(void * params)
{
	printd("(%p)", params);

	data_t * data = (data_t *) params;

	data->bytes = sizeof(double) * LENGTH * LENGTH;
	assert(data->bytes > 0);

	/* Allocate grid and helper */
	data->grid = calloc(1, data->bytes);
	assert(data->grid != NULL);

	data->tmp = calloc(1, data->bytes);
	assert(data->tmp != NULL);

	return 0;
}

static inline double update(double *tmp, int i, int j)
{
	return (0.25 * 
		(tmp[at(i, j - 1)] 
		 + tmp[at(i, j + 1)]
		 + tmp[at(i - 1, j)] 
		 + tmp[at(i + 1, j)]));
}

static inline double difference(double *grid, double *tmp, int i, int j)
{
	return (fabs(grid[at(i, j)] - tmp[at(i, j)]));
}

static void *work(void * params)
{
	printd("(%p)", params);

	data_t * data = (data_t *) params;
	
	double * grid = data->grid;
	double * tmp = data->tmp;
	int bytes = data->bytes;

	/* problem details */
	int error = 10;
	int x = 5;
	int y = 5;
	int heat = 50;

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
			for (i = 1; i < LENGTH; i++) {
				for (j = 1; j < LENGTH; j++) {

					/* Update using neighbours average */
					grid[at(i, j)] = update(tmp, i, j);

					/* Update max heat difference */
					gap = difference(grid, tmp, i, j);
					if (diff < gap) {
						diff = gap;
					}
				}
			}
		}
	}

	grid[at(x, y)] = heat;

/*
  for (i = 0; i < length; i++) {
  for (j = 0; j < length; j++) {
  printf("%d %d %f\n", i, j, grid[at(i, j)]);
  }
  printf("\n");
  }
*/

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
	.count = 3,
};

pipe_t *get(void)
{
	return &heat;
}
