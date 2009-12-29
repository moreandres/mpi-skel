#include "log.h"

static log_t *log_create(int options)
{

	log_t *log = NULL;

	printd("%d", options);

	assert(options >= 0);

	log = calloc(1, sizeof(log_t));

	log->name = calloc(FILENAME_SIZE, sizeof(char));
	log->fd = open(log->name, 0);

	return log;
}

#include <unistd.h>

static int log_destroy(log_t *log)
{

	int result = -1;

	printd("%p", log);

	assert(log != NULL);

	free(log);
	log = NULL;

	result = close(log->fd);

	return result;
}
