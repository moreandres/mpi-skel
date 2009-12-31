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

log_t *get_log(void)
{
	return _log;
}

int log_create(char *prefix)
{
	log_t *log = NULL;

	char *name = NULL;
	char *tmp = NULL;
	char *stamp = NULL;
	char *suffix = ".log";

	printd("(%s)", prefix);

	assert(prefix != NULL);

	log = calloc(1, sizeof(log_t));

	if (log) {
		log->data->name = calloc(FILENAME_SIZE, sizeof(char));

		tmp = rindex(name, '/');
		if (tmp == NULL) {
			tmp = name;
		} else {
			name++;
		}

		strncat(name, prefix, strlen(prefix));

		stamp = timestamp(FILENAME_SIZE
				  - strlen(log->data->name)
				  - strlen(suffix));

		strncat(log->data->name, stamp, strlen(stamp));
		strncat(log->data->name, suffix, strlen(suffix));

		printd("%s", log->data->name);

		log->data->fd = open(log->data->name, O_CREAT | O_APPEND);

		printd("%d", log->data->fd);
		perror("Error");
	}

	return 0;
}

#include <unistd.h>

int log_destroy(void)
{
	int result = -1;

	printd("()");

	result = close(_log->data->fd);

	free(_log);

	return result;
}
