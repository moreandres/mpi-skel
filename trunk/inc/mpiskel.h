/*
 * mki-skel - header interface
 *
 * Copyright 2009, Andres More <more.andres@gmail.com>
 *
 * This program is free software, you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 */

#ifndef MPISKEL_H
#define MPISKEL_H

/**
 * DOC: Introduction
 *
 * mpi-skel is a skeleton for MPI applications. This document implementes
 * the framework and defines the callbacks to be implemented.
 *
 */

/**
 * DOC: Warning
 *
 * If you are reading this as a document and not the header file itself, it
 * will be incomplete because not all documentation has been converted yet.
 */

typedef struct pipe_data_s *pipe_data_t;

/**
 * stage_t - application-specific callbacks from mpiskel
 *
 * This structure contains various callbacks that mpiskel uses to implement
 * applications.
 *
 * @name: name of the stage
 * @work: main stage callback
 * @options: stage options
 * @pre: pre stage callback
 * @post: post stage callback
 */

typedef struct stage_s {
	char *name;
	int (*work) (void *);
	int options;
	int (*pre) (void *);
	int (*post) (void *);
	pipe_data_t data;
} stage_t;

/**
 * pipe_t - application-specific callbacks from mpiskel
 *
 * This structure contains various callbacks that mpiskel uses to implement
 * applications.
 *
 * @name: name of the pipeline
 * @options: stage options
 * @stages: list of stages
 * @count: number of stages
 * @create: description
 * @execute: description
 * @destroy: description
 * @print: print contents as a one-liner
 */

#define STAGE_MAX 32

typedef struct pipe_s {
	char *name;
	int options;
	stage_t stages[STAGE_MAX];
	int (*create) (void);
	int (*execute) (void);
	int (*destroy) (void);
	int (*print) (void);
	pipe_data_t data;
} pipe_t;

pipe_t *get_pipe(void);

extern pipe_t *get(void);

#endif /* MPISKEL_H */
