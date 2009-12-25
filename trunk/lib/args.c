#include "args.h"
#include "utils.h"

args_t *args;

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	args_t *arguments = state->input;

	switch (key) {
	case 'v':
		arguments->verbose++;
		break;
	case 'o':
		arguments->file = arg;
		break;
	case ARGP_KEY_END:
		if (state->arg_num > 0)
			argp_usage(state);
		break;

	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

#include <string.h>

args_t *setup_argp(int argc, char *argv[])
{
	args_t *result;

	printd("%d, %p", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	result = calloc(1, sizeof(args_t));

	argp_parse(&argp, argc, argv, 0, NULL, result);

	return result;
}

void print_args(args_t *args)
{
	assert(args != NULL);

	printf("%d %s\n", args->verbose, args->file);

	return;
}
