#include <stdio.h>
#include <stdlib.h>

#include <mpiskel.h>

#include "utils.h"

static int q[20];

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

static int work(void *params)
{
	printd("()");

	set_queens(1, 13);

	return 0;
}

static pipe_t queens = {
	.name = "queens",
	.stages = {
		{ "work", work, 0, NULL, NULL },
		{},
	},
};

pipe_t *get(void)
{
	return &queens;
}