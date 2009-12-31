#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "args.h"
#include "log.h"

#include <signal.h>

static void handler(int signum)
{
	int result;

	if (_log)
		result = log_destroy(_log);

	return;
}

static void setup_handler(void)
{

	printd("()");

	printv(1, "Setting signal handler...\n");

	signal(SIGINT, handler);

	return;
}

int main(int argc, char *argv[])
{
	char *name = NULL;

	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	setup_argp(argc, argv);

	setup_handler();


#include <strings.h>

	name = rindex(argv[0], '/');
	if (name == NULL) {
		name = argv[0];
	} else {
		name++;
	}

	_log = log_create(name, 0);

	return 0;
}

static void setup_mpi(void)
{
	printd("()");

	return;
}

static void setup_driver(void)
{

	printd("()");

	return;
}
