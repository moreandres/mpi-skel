#include <stdio.h>

#include "utils.h"
#include "log.h"

log_t *_log;

log_t *log_create(int options)
{

	log_t *log = NULL;

	printd("(%d)", options);

	assert(options >= 0);

	_log = calloc(1, sizeof(log_t));

	_log->name = calloc(FILENAME_SIZE, sizeof(char));
	_log->fd = open(log->name, 0);

	return _log;
}

#include <unistd.h>

int log_destroy(log_t *log)
{

	int result = -1;

	printd("(%p)", log);

	assert(log != NULL);

	free(log);
	log = NULL;

	result = close(log->fd);

	return result;
}
