#ifndef ARGP_H
#define ARGP_H

#include <argp.h>
#include "config.h"

typedef struct arg_data_s *arg_data_t;
typedef struct arg_s {
	arg_data_t data;
	int (*create) (int argc, char *argv[]);
	int (*destroy) (void);
	int (*print) (void);
	int *argc;
	char ***argv;
} arg_t;

arg_t *get_arg(void);

#endif /* ARGP_H */
