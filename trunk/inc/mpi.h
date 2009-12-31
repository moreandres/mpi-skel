#ifndef MPI_H
#define MPI_H

typedef struct mpi_s {
	int rank;
	int size;
	char *name;
	int length;
	int (*create) (int *argc, char **argv[]);
	int (*destroy) (void);
} mpi_t;

#include "/usr/lib/openmpi/1.3.2-gcc/include/mpi.h"

mpi_t *get_mpi(void);

#endif /* MPI_H */
