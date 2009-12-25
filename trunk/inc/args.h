#ifndef ARGP_H
#define ARGP_H

#include <argp.h>
#include "config.h"

static const char *string = PACKAGE_STRING;
static const char *report = PACKAGE_BUGREPORT;

static const char description[] =
    "mpiskel -- a framework for MPI applications using C callbacks";

static struct argp_option options[] = {
	{"verbose", 'v', NULL, 0, "Produce verbose output"},
	{"output", 'o', "FILE", 0,
	 "Output to FILE instead of standard output"},
	{NULL}
};

typedef struct args_s {
	int verbose;
	char *file;
} args_t;

extern args_t *args;

error_t parse_opt(int key, char *arg, struct argp_state *state);

static struct argp argp = { options, parse_opt, NULL, description };

args_t *setup_argp(int argc, char *argv[]);

void print_args(args_t *args);

#endif /* ARGP_H */
