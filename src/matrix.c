#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <syslog.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include <mpiskel.h>

#include "utils.h"

#define SIZE 100

typedef struct data_s {
	double *a;
	double *b;
	double *c;
	int n;
} data_t;

static int setup(void *data)
{
	printd("()");

	data = calloc(1, sizeof(data_t));

	data_t *data2 = (data_t *) data;

	data2->a = calloc(SIZE * SIZE, sizeof(double));
	data2->b = calloc(SIZE * SIZE, sizeof(double));
	data2->c = calloc(SIZE * SIZE, sizeof(double));
	data2->n = SIZE;

	srandom(time(NULL));

	int i, j;

	for (i = 0; i < data2->n; i++)
		for (j = 0; j < data2->n; j++)
			data2->a[i * SIZE + j] = 1.0 * random() / RAND_MAX;

	for (i = 0; i < data2->n; i++)
		for (j = 0; j < data2->n; j++)
			data2->b[i * SIZE + j] = 1.0 * random() / RAND_MAX;

	return 0;
}

static int work(void *data)
{
	printd("()");

	data_t *data2 = (data_t *) data;

	int i, j, k;
	for (i = 0; i < data2->n; i++)
		for (j = 0; j < data2->n; j++)
			for (k = 0; k < data2->n; k++)
				data2->c[i * SIZE + j] += data2->a[i * SIZE + k]
				    * data2->b[k * SIZE + j];

	return 0;
}

static pipe_t matrix = {
	.name = "matrix",
	.stages = {
		   {"setup", setup, 0, NULL, NULL},
		   {"work", work, 0, NULL, NULL},
		   {},
		   },
};

pipe_t *get(void)
{
	return &matrix;
}
