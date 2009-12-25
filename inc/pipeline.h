#ifndef PIPELINE_H
#define PIPELINE_H

typedef struct pipeline_s {
} pipeline_t;

typedef void *(*fn_t) (void *args);

typedef struct stage_s {
	fn_t fn;
	int options;
} stage_t;

stage_t *stage_create(fn_t fn, int options);
int stage_destroy(stage_t *stage, int options);
int stage_execute(stage_t *stage, int options);
void stage_show(stage_t *stage);

pipeline_t *pipeline_create(stage_t **stages, int count, int options);
int pipeline_destroy(pipeline_t *pipeline, int options);
int pipeline_start(pipeline_t *pipeline, int options);
int pipeline_stop(pipeline_t *pipeline, int options);
void pipeline_show(pipeline_t *pipeline, int options);

#endif /* PIPELINE_H */
