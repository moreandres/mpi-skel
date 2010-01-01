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
	printd("(%d, %s, %p)", key, arg, state);

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

static int arg_create(int argc, char *argv[])
{
	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	return argp_parse(&argp, argc, argv, 0, NULL, get_arg());
}

static int arg_destroy(void)
{
	printd("()");

	free(_arg->data);
	free(_arg);

	return 0;
}

#define LINE_SIZE 64

static char *arg_print(void)
{
	printd("()");

	char *line = calloc(LINE_SIZE, sizeof(char));

	snprintf(line, LINE_SIZE, "ARG: %d, %s\n",
		 get_arg()->data->verbose, get_arg()->data->file);

	return line;
}

arg_t *get_arg(void)
{
	printd("()");

	if (_arg == NULL) {
		_arg = calloc(1, sizeof(arg_t));
		_arg->create = arg_create;
		_arg->destroy = arg_destroy;
		_arg->print = arg_print;
		_arg->data = calloc(1, sizeof(struct arg_data_s));
	}

	return _arg;
}
