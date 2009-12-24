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

struct arguments {
	char *args[2];
	int verbose;
	char *file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state);

static struct argp argp = { options, parse_opt, NULL, description };

static void setup_argp(void);

#endif /* ARGP_H */
