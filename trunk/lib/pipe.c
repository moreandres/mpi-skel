#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "pipe.h"

static pipe_t *_pipe;

static int pipe_create(void)
{
	printd("()");

	return 0;
}

static int pipe_destroy(void)
{
	printd("()");

	return 0;
}

pipe_t *get_pipe(void)
{
	if (_pipe == NULL) {
		_pipe = calloc(1, sizeof(pipe_t));
		_pipe->create = pipe_create;
		_pipe->destroy = pipe_destroy;
		_pipe->data = calloc(1, sizeof(pipe_data_t));
	}

	return _pipe;
}
