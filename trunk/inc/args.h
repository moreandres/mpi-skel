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

typedef struct args_s {
	int verbose;
	char *file;
} args_t;

error_t parse_opt(int key, char *arg, struct argp_state *state);

static struct argp argp = { options, parse_opt, NULL, description };

void setup_argp(int argc, char *argv[]);

args_t *get_args();

void print_args(args_t *args);

#endif /* ARGP_H */
