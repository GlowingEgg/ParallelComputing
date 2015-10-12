#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int sum = 0;
pthread_mutex_t sum_lock;
int** matrix;

typedef struct 
{
	int rows;
	int cols;
	int p;
	int id;
}thread_arg;

void *threadSum(void *threadargs){
	thread_arg* my_args;
	my_args = (thread_arg*) threadargs;
	int my_rows = my_args->rows;
	int my_cols = my_args->cols;
	int my_p = my_args->p;
	int my_id = my_args->id;
	int elements = my_rows * my_cols;
	int local_sum, counter;
	for(counter = my_id; counter < elements; counter += my_p){
		local_sum += matrix[(counter / my_cols)][(counter % my_cols)];
	}
	pthread_mutex_lock(&sum_lock);
	sum += local_sum;
	pthread_mutex_unlock(&sum_lock);
	pthread_exit(NULL);
}
int main(){
	int row, col, p, rc, element;
 	printf("Number of rows: \n");
 	scanf("%d", &row);
 	printf("Number of columns: \n");
 	scanf("%d", &col);
 	printf("Number of threads: \n");
 	scanf("%d", &p);
 	pthread_t threads[p];
 	thread_arg args[p];
 	matrix = malloc(row * sizeof(int));
 	for(int x =0; x < row; x++){
 		matrix[x] = malloc(col * sizeof(int));
 	}
 	element = 1;
 	/* Fill the matrix with numbers */
 	for(int i = 0; i < row; i++){
 		for(int j = 0; j < col; j++){
 			matrix[i][j] = element;
 			element++;
 		}
 	}
 	pthread_mutex_init(&sum_lock, NULL);
 	for(int k = 0; k < p; k++){
 		args[k].rows = row;
 		args[k].cols = col;
 		args[k].p = p;
 		args[k].id = k;
 		rc = pthread_create(&threads[k], NULL, threadSum, (void*) &args[k]);
 		if(rc){
        	printf("ERROR; return code from pthread_create() is %d\n", rc);
         	exit(-1);
      	}
 	}
 	for(int q=0; q<p; q++){
 		pthread_join(threads[q], NULL);
 	}
 	pthread_mutex_lock(&sum_lock);
 	printf("sum: %d \n", sum);
 	pthread_mutex_unlock(&sum_lock);
 	pthread_mutex_destroy(&sum_lock);
 	pthread_exit(NULL);
}