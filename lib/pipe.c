#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "pipe.h"

typedef struct stage_s {
	void *(*work) (void *);
} stage_t;

#define STAGE_MAX 32

struct pipe_data_s {
	int count;
	stage_t stages[STAGE_MAX];
};

static pipe_t *_pipe;

static int pipe_create(void)
{
	printd("()");

	_pipe->data->count = 5;

	int i = 0;
	while (i < _pipe->data->count) {
		printd("%d", i);
		i++;
	}

	return 0;
}

static int pipe_destroy(void)
{
	printd("()");

	free(_pipe->data);
	free(_pipe);

	return 0;
}

pipe_t *get_pipe(void)
{
	printd("()");

	if (_pipe == NULL) {
		_pipe = calloc(1, sizeof(pipe_t));
		_pipe->create = pipe_create;
		_pipe->destroy = pipe_destroy;
		_pipe->data = calloc(1, sizeof(struct pipe_data_s));
	}

	return _pipe;
}
