#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include "config.h"

#define printv(level, fmt, args...) do { if (1 >= level) { \
      char *stamp = timestamp(32);			   \
      printf("%s: ", stamp);				   \
      printf(fmt, ## args);				   \
      free(stamp); }					   \
  } while (0)

#ifdef DEBUG
#define printd(fmt, args...) do { \
			printf("%s:%d:%s", __FILE__, __LINE__, __func__);    \
			printf(fmt, ## args); printf("\n"); } while (0)
#else
#define printd(fmt, args...) /* empty */
#endif

#define free(x) do { free(x); x = NULL; } while (0)

char *timestamp(int size);
double wtime(void);

#endif /* UTILS_H */
