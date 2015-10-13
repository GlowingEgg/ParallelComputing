#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int p;
	int id;
	void whatever_function(int);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	whatever_function(id);
	MPI_Finalize();
}
void whatever_function(int id){
	printf("Processor %d!!!\n", id);
	fflush(stdout);
}