#ifndef MPI_H
#define MPI_H

typedef struct mpi_data_s *mpi_data_t;
typedef struct mpi_s {
	int rank;
	int size;
	char *name;
	int length;
	mpi_data_t data;
	int (*init) (int *argc, char **argv[]);
	int (*finalize) (void);
} mpi_t;

#include <mpi.h>

mpi_t *get_mpi(void);

#endif /* MPI_H */
