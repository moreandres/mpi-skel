#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "pipe.h"

static pipe_t *_pipe;

struct pipe_data_s {
};

static int pipe_create(void)
{
	printd("()");

	return 0;
}

static int pipe_execute(void)
{
	printd("()");

	printf("%s\n", _pipe->name);

	int i = 0;
	while (i < _pipe->count) {

		printf("\t%s\n", _pipe->stages[i].name);

		if (_pipe->stages[i].pre != NULL) {
			_pipe->stages[i].pre(NULL);
		}

		if (_pipe->stages[i].work != NULL) {
			_pipe->stages[i].work(NULL);
		}

		if (_pipe->stages[i].post != NULL) {
			_pipe->stages[i].post(NULL);
		}


		i++;
	}

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

		_pipe = get();

		assert(_pipe != NULL);
		assert(_pipe->name != NULL);
		assert(_pipe->count > 0);

		_pipe->create = pipe_create;
		_pipe->execute = pipe_execute;
		_pipe->destroy = pipe_destroy;
		_pipe->data = calloc(1, sizeof(pipe_data_t));
	}

	return _pipe;
}
