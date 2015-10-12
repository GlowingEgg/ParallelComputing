#include<stdio.h>
#include<stdlib.h>

typedef struct
{
  int *p;
  int size;
}chunk;

chunk breakIntoChunks(int row, int col, int p, int id){
	int i;
	int j = 0;
	int elements = row * col;
	int partitionSize = elements/p+1;
	int *partition = (int *)malloc(partitionSize * sizeof(int));
	for(i = id; i < elements; i += p){
		partition[j] = ((i / col) * 10) + (i % col);
		j++;
	}
	chunk mychunk;
    mychunk.p = partition;
    mychunk.size = j + 1;
   
    return mychunk;
}

void display(chunk *myChunk) {
  
  int counter;
  
  for(counter = 0; counter<myChunk->size; counter++) {
     printf("%d  ", myChunk->p[counter]);
  }
  printf("\n");
}
 int main(){
 	int row;
 	int col;
 	int p;
 	int id;
 	printf("Number of rows: \n");
 	scanf("%d", &row);
 	printf("Number of columns: \n");
 	scanf("%d", &col);
 	printf("Number of partitions \n");
 	scanf("%d", &p);
 	printf("Partition id: \n");
 	scanf("%d", &id);
 	chunk myChunk = breakIntoChunks(row, col, p, id);
 	display(&myChunk);
 }