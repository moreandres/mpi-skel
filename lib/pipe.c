#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "pipe.h"
#include "mpi.h"
#include "arg.h"

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
	int error = 0;

	printd("()");

	void *data = NULL;

	int i = 0;
	while (i < _pipe->count) {

		if (_pipe->stages[i].options & 0x1 == 0x1) {
			error = get_mpi()->init(get_arg()->argc,
						get_arg()->argv);
		}

		if (_pipe->stages[i].pre != NULL) {
			_pipe->stages[i].pre(data);
		}

		if (_pipe->stages[i].work != NULL) {
			_pipe->stages[i].work(data);
		}

		if (_pipe->stages[i].post != NULL) {
			_pipe->stages[i].post(data);
		}

		if (_pipe->stages[i].options & 0x1 == 0x1) {
			error = get_mpi()->finalize();
		}

		i++;
	}

	return error;
}

static int pipe_destroy(void)
{
	printd("()");

	return 0;
}

static int pipe_print(void)
{
	printd("()");

	printf("%s: ", _pipe->name);

	int i = 0;
	while (i++ < _pipe->count) {
		printf("%s, ", _pipe->stages[i].name);
	}

	printf("\n");

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
		_pipe->print = pipe_print;

		_pipe->data = calloc(1, sizeof(pipe_data_t));
	}

	return _pipe;
}
