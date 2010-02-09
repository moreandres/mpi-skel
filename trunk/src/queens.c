#include <stdio.h>
#include <stdlib.h>

#include <mpiskel.h>

#include "utils.h"
#include "pipe.h"

static int q[20];
static int count = 1;
static int cc = 1;

static int place(int i, int k)
{
	int j = 1;
	while (j < k) {
		if ((q[j] == i) || abs(q[j] - i) == abs(j - k))
			return 0;
		j++;
	}
	return 1;
}

static void set_queens(int k, int n)
{
	int i;
	if (k > n)
		;
	else {
		for (i = 1; i <= n; i++)
			if (place(i, k) == 1) {
				q[k] = i;
				set_queens(k + 1, n);
			}
	}
}

static void *work(void * params)
{
	printd("()");

	set_queens(1, 13);

	return NULL;
}

static void *setup(void * params)
{
	printd("()");

	return NULL;
}

static void *reduce(void * params)
{
	printd("()");

	return NULL;
}

static pipe_t queens = {
	.name = "queens",
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
	return &queens;
}
