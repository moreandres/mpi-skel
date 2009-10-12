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

#define MAX_STAGES 32

/**
 * struct mpiskel_ops - application-specific callbacks from mpiskel
 *
 * This structure contains various callbacks that mpiskel uses to implement
 * applications.
 *
 * @method: method description.
 */  

struct mpiskel_ops {
  int (*pre)(void);
  int (*stage[MAX_STAGES])(void);
  int stages;
  int (*post)(void);  
};

struct mpiskel 
{
  int id;
};

#endif /* MPISKEL_H */
