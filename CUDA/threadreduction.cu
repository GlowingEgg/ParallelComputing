#include <stdio.h>
#include <stdlib.h>

__global__ void arrayReduce(int *A, int *sum, int size){
        int thread = threadIdx.x;
        sum += A[thread];
}

int main(int argc, char **argv){
        int size;
        int* deviceArray = 0;
        int* sum = 0;
        int* localSum = (int*) malloc(4);
        printf("Array Size: ");
        scanf("%d", &size);
        int* local = (int*) malloc(size * sizeof(int));
        cudaMalloc((void**) &deviceArray, sizeof(int) * size);
        cudaMalloc((void**) &sum, 4);
        for(int i = 0; i < size; i++){
                local[i] = rand() % 100;
        }
    cudaMemcpy(deviceArray, local, size * sizeof(int), cudaMemcpyHostToDevice);
        dim3 dimBlock(size,1);
        arrayReduce<<<1,dimBlock>>>(deviceArray, sum, size);
        cudaThreadSynchronize();
        cudaMemcpy(localSum, sum, sizeof(int), cudaMemcpyDeviceToHost);
        printf("\nSum: %d\n", *localSum);
}

