#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	int global_sum;
	int sum;
	int p;
	int id;
	int cyclical_sum(int, int, int[], int);
	int a[] = {1,2,3,4,5,6,7,8,9,10};
	int size = sizeof(a)/sizeof(a[0]);
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	sum = cyclical_sum(id, p, a, size);
	MPI_Reduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Finalize();
	if(id == 0){
		printf("Full Sum: %d\n", global_sum);
		fflush(stdout);
	}	
}
int cyclical_sum(int id, int p, int a[], int size){
	int local_sum = 0;
	for(int i = id; i < size; i += p){
		local_sum += a[i];
	}
	printf("Processor %d: %d\n", id, local_sum);
	fflush(stdout);
	return local_sum;
}