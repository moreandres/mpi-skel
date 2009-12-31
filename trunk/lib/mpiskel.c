#include <stdlib.h>
#include <assert.h>

#include <config.h>
#include <mpiskel.h>

#include "utils.h"
#include "arg.h"
#include "log.h"
#include "mpi.h"

#include <signal.h>

static void handler(int signum)
{
	printd("(%d)", signum);

	printv(1, "Handling signal %d", signum);

	get_mpi()->destroy();
	get_log()->destroy();

	return;
}

int main(int argc, char *argv[])
{
	printd("(%d, %p)", argc, argv);

	assert(argc >= 0);
	assert(argv != NULL);

	signal(SIGINT, handler);

	get_arg()->create(argc, argv);
	get_log()->create(argv[0]);

	return 0;
}
