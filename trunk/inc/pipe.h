#ifndef PIPE_H
#define PIPE_H

typedef struct pipe_data_s *pipe_data_t;
typedef struct pipe_s {
	pipe_data_t data;
	int (*create) (void);
	int (*destroy) (void);
} pipe_t;

pipe_t *get_pipe(void);

#endif /* PIPE_H */
