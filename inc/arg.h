#ifndef ARGP_H
#define ARGP_H

#include <argp.h>
#include "config.h"

static const char description[] =
    "mpiskel -- a framework for MPI applications using C callbacks";

static struct argp_option options[] = {
	{"verbose", 'v', NULL, 0, "Produce verbose output"},
	{"log", 'l', "FILE", 0,
	 "Log to FILE instead of timestamped file"},
	{NULL}
};

typedef struct arg_data_s *arg_data_t;
typedef struct arg_s {
	arg_data_t data;
	int (*create) (int argc, char *argv[]);
	int (*destroy) (void);
} arg_t;

error_t parse_opt(int key, char *arg, struct argp_state *state);

static struct argp argp = { options, parse_opt, NULL, description };

void setup_argp(int argc, char *argv[]);

arg_t *get_arg(void);

void print_arg(arg_t *arg);

#endif /* ARGP_H */
