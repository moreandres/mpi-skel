#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "utils.h"
#include "log.h"

#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <assert.h>

#include "config.h"

struct log_data_s {
	int fd;
	char *name;
};

static log_t *_log;

static int log_create(char *prefix)
{
	char *name = NULL;
	char *tmp = NULL;
	char *stamp = NULL;
	char *suffix = ".log";

	printd("(%s)", prefix);

	assert(prefix != NULL);

	get_log()->data->name = calloc(FILENAME_SIZE, sizeof(char));

	tmp = rindex(prefix, '/');
	if (tmp == NULL) {
		tmp = prefix;
	} else {
		prefix++;
	}

	strncat(get_log()->data->name, prefix, strlen(prefix));

	stamp = timestamp(FILENAME_SIZE
			  - strlen(get_log()->data->name)
			  - strlen(suffix));

	strncat(get_log()->data->name, stamp, strlen(stamp));
	strncat(get_log()->data->name, suffix, strlen(suffix));

	get_log()->data->fd = open(get_log()->data->name,
				   O_CREAT | O_APPEND);

	return 0;
}

#include <unistd.h>

static int log_destroy(void)
{
	int result = -1;

	printd("()");

	result = close(_log->data->fd);

	free(_log);

	return result;
}

log_t *get_log(void)
{
	printd("()");

	if (_log == NULL) {
		_log = calloc(1, sizeof(log_t));
		_log->create = log_create;
		_log->destroy = log_destroy;
		_log->data = calloc(1, sizeof(struct log_data_s));
	}

	return _log;
}
