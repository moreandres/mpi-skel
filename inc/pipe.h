#ifndef PIPE_H
#define PIPE_H

#define STAGE_MAX 32

typedef struct pipe_data_s *pipe_data_t;

typedef struct stage_s {
	char *name;
	void *(*work) (void *);
	int options;
	void *(*pre) (void *);
	void *(*post) (void *);
	pipe_data_t data;
} stage_t;

typedef struct pipe_s {
	char *name;
	int options;
	stage_t stages[STAGE_MAX];
	int count;
	pipe_data_t data;
	int (*create) (void);
	int (*execute) (void);
	int (*destroy) (void);
} pipe_t;

pipe_t *get_pipe(void);

extern pipe_t *get(void);

#endif /* PIPE_H */
