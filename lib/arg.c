#include "arg.h"
#include "utils.h"
#include "config.h"

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

static int arg_create(int argc, char **argv)
{
	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	_arg->argc = &argc;
	_arg->argv = &argv;

	return argp_parse(&argp, argc, argv, 0, NULL, get_arg());
}

static int arg_destroy(void)
{
	printd("()");

	free(_arg->data);
	free(_arg);

	return 0;
}

static int arg_print(void)
{
	printf("ARG %d, %s\n", _arg->data->verbose, _arg->data->file);

	return 0;
}

/**
 * get_arg - returns a pointer to the arg singleton object
 *
 * The function returns a reference which should be destroyed using the 
 * destroy method. 
 *
 * This function is used to access the object which handles argument parsing
 * and handling. During its first call, it will allocate the object memory
 * and it will assign the object methods.
 */

arg_t *get_arg(void)
{
	/* if not already done, then assing memory and methods */
	if (_arg == NULL) {
		
		/* create main object */
		_arg = calloc(1, sizeof(arg_t));

		/* assign object methods */
		_arg->create = arg_create;
		_arg->destroy = arg_destroy;
		_arg->print = arg_print;

		/* create object private data */
		_arg->data = calloc(1, sizeof(struct arg_data_s));
	}

	return _arg;
}
