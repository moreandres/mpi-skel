#include "arg.h"
#include "utils.h"

static arg_t *_arg;

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

struct arg_data_s {
	int verbose;
	char *file;
};

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	arg_t *arguments = state->input;

	switch (key) {
	case 'v':
		arguments->data->verbose++;
		break;
	case 'l':
		arguments->data->file = arg;
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

static int arg_create(int argc, char *argv[])
{

	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	_arg = calloc(1, sizeof(arg_t));

	argp_parse(&argp, argc, argv, 0, NULL, _arg);

	return 0;
}

static int arg_destroy(void)
{
	return 0;
}

static void print_arg(arg_t *arg)
{
	assert(arg != NULL);

	printf("%d %s\n", arg->data->verbose, arg->data->file);

	return;
}

arg_t *get_arg(void)
{
	printd("()");

	if (_arg == NULL) {
		_arg = calloc(1, sizeof(arg_t));
		_arg->create = arg_create;
		_arg->destroy = arg_destroy;
		_arg->data = calloc(1, sizeof(struct arg_data_s));
	}

	return _arg;
}
