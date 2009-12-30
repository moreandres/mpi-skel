#ifndef LOG_H
#define LOG_H

#include <stdlib.h>
#include <assert.h>

#include "config.h"

typedef struct log_s {
	int fd;
	char *name;
} log_t;

extern log_t *_log;

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME_SIZE 64

log_t *log_create(int options);

#include <unistd.h>

int log_destroy(log_t *log);

#endif /* LOG_H */
