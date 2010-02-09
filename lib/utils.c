#include <sys/time.h>
#include <time.h>
#include "utils.h"

char *timestamp(int size)
{
	printd("(%d)", size);

	assert(size >= 0);

	char *buffer = calloc(size, sizeof(char));
	int result = -1;

	struct timeval tv;
	time_t time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec;

	result = strftime(buffer, size, "%m%d%y-%H%M%S", localtime(&time));

	return buffer;
}

double wtime(void)
{
	printd("()");

	double sec;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec + tv.tv_usec / 1000000.0;
	return sec;
}
