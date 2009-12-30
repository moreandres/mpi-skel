#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <assert.h>

#include "config.h"

#define printv(level, fmt, args...) do { if (arguments.verbosity >= level) { \
			printf(fmt, ## args); }			             \
	} while (0)

#ifdef DEBUG
#define printd(fmt, args...) do { \
			printf("%s:%d:%s", __FILE__, __LINE__, __func__); \
			printf(fmt, ## args); printf("\n"); } while (0)
#else
#define printd(fmt, args...) /* empty */
#endif

int timestamp(char *buffer, int size);
double wtime(void);

#endif /* UTILS_H */
