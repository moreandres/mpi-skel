#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <assert.h>

#include <config.h>

extern int verbosity;

#define printv(level, fmt, args...) do { if (verbosity >= level) { \
			printf(fmt, ## args); }			   \
	} while (0)

extern int debug;

#define printd(fmt, args...) do { if (debug) { \
			printf("%s:%d:%s() ", __FILE__, __LINE__, __func__); \
			printf(fmt, ## args); } } while (0)

int timestamp(char *buffer, int size);
double wtime(void);

#endif /* UTILS_H */
