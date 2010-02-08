#include <stdio.h>
#include <stdlib.h>

#include <mpiskel.h>

static int q[20];
static int count = 1;
static int cc = 1;

static void print(int n)
{
	int i;
	count++;
	for (i = 1; i <= n; i++)
		printf("(%d,%d)", i, q[i]);

	printf("\n");
}

static int Place(int i, int k)
{
	int j = 1;
	while (j < k) {
		if ((q[j] == i) || abs(q[j] - i) == abs(j - k))
			return 0;
		j++;
	}
	return 1;
}
static void Queens(int k, int n)
{
	int i;
	if (k > n)
		print(n);
	else {
		for (i = 1; i <= n; i++)
			if (Place(i, k) == 1) {
				q[k] = i;
				Queens(k + 1, n);
			}
	}
}
static int main2(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	Queens(1, n);
	printf("\n%d", cc);
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

static pipe_t queens = {
	.name = "queens",
	.options = 0,
	.stages = {
		{ "setup", setup, 0, NULL, NULL },
		{ "work", work, 0, NULL, NULL },
		{ "reduce", reduce, 0, NULL, NULL },
	},
};

pipe_t *get(void)
{
	return &queens;
}
