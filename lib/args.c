#include "args.h"

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

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

void setup_argp(void)
{

	return;
}
