#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "log.h"

log_t *_log;

log_t *log_create(char *prefix, int options)
{

	log_t *log = NULL;

	char *stamp = NULL;
	char *suffix = ".log";

	printd("(%s, %d)", prefix, options);

	assert(options >= 0);

	log = calloc(1, sizeof(log_t));

	if (log) {
		log->name = calloc(FILENAME_SIZE, sizeof(char));

		strncat(log->name, prefix, strlen(prefix));

		stamp = timestamp(FILENAME_SIZE
				  - strlen(log->name)
				  - strlen(suffix));

		strncat(log->name, stamp, strlen(stamp));
		strncat(log->name, suffix, strlen(suffix));

		printd("%s", log->name);

		log->fd = open(log->name, O_CREAT | O_APPEND);

		printd("%d", log->fd);
		perror("Error");
	}

	return log;
}

#include <unistd.h>

int log_destroy(log_t *log)
{

	int result = -1;

	printd("(%p)", log);

	assert(log != NULL);

	result = close(log->fd);

	free(log);

	return result;
}
