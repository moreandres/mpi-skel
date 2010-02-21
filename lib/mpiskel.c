#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "arg.h"
#include "log.h"
#include "pipe.h"

#include "mpi.h"

#include <signal.h>

static void handler(int signum)
{
	printd("(%d)", signum);

	assert(signum > 0);
	assert(signum < NSIG);

	printv(1, "Handling signal %d\n", signum);

	get_pipe()->destroy();
	get_log()->destroy();
	get_arg()->destroy();

	return;
}

int main(int argc, char *argv[])
{
	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	signal(SIGINT, handler);

	get_arg()->create(argc, argv);
	get_arg()->print();

	get_log()->create(argv[0]);
	get_log()->print();

	get_pipe()->create();
	get_pipe()->print();
	get_pipe()->execute();

	raise(SIGINT);

	return 0;
}
