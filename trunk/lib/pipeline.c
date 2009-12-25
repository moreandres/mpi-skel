#include <assert.h>
#include "utils.h"
#include "pipeline.h"

stage_t *stage_create(fn_t fn, int options)
{

	stage_t *stage = NULL;

	printd("%p, %d", fn, options);

	assert(fn != NULL);
	assert(options > 0);

	stage = calloc(1, sizeof(stage_t));

	stage->fn = fn;
	stage->options = options;

	return stage;
}

int stage_destroy(stage_t *stage, int options)
{

	int result;

	printd("%p, %d", stage, options);

	assert(stage != NULL);
	assert(options >= 0);

	free(stage);
	stage = NULL;

	return result;
}

int stage_execute(stage_t *stage, int options)
{

	int result = 1;

	printd("%p, %d", stage, options);

	assert(stage != NULL);
	assert(options >= 0);

	return result;
}

void stage_show(stage_t *stage)
{
	printd("%p", stage);

	assert(stage != NULL);

	return;
}

pipeline_t *pipeline_create(stage_t **stages, int count, int options)
{

	pipeline_t *pipeline = NULL;
	int i = 0;

	printd("%p, %d, %d", stages, count, options);

	assert(stages != NULL);
	assert(count >= 0);
	assert(options >= 0);

	i = 1;

	pipeline = calloc(1, sizeof(pipeline_t));

	return pipeline;
}

int pipeline_destroy(pipeline_t *pipeline, int options)
{

	int result = -1;

	printd("%p, %d", pipeline, options);

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

int pipeline_start(pipeline_t *pipeline, int options)
{

	int result = -1;

	printd("%p, %d", pipeline, options);

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

int pipeline_stop(pipeline_t *pipeline, int options)
{

	int result = -1;

	printd("%p, %d", pipeline, options);

	assert(pipeline != NULL);
	assert(options >= 0);

	return result;
}

void pipeline_show(pipeline_t *pipeline, int options)
{

	printd("%p, %d", pipeline, options);

	assert(pipeline != NULL);
	assert(options >= 0);

	return;
}
