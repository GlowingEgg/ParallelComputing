#include <stdio.h>
#include <stdlib.h>

__global__ void matrixAdd(int *A, int *B, int *C, int size){
        int row = blockIdx.y;
        int col = threadIdx.x;
        C[(row * size) + col] = A[(row * size) + col] + B[(row * size) + col];
}

int main(int argc, char **argv){
        int size, totalSize;
        int* matrixA = 0;
        int* matrixB = 0;
        int* matrixC = 0;
        printf("Matrix size: ");
        scanf("%d", &size);
        totalSize = size * size;
        dim3 blockDim(size, 1);
        dim3 gridDim(1, size);
        int * local = (int*) malloc(totalSize * sizeof(int));
        cudaMalloc((void**) &matrixA, sizeof(int) * totalSize);
        cudaMalloc((void**) &matrixB, sizeof(int) * totalSize);
        cudaMalloc((void**) &matrixC, sizeof(int) * totalSize);
        for(int i = 0; i < totalSize; i++){
                local[i] = rand() % 100;
        }
    cudaMemcpy(matrixA, local, sizeof(int) * totalSize, cudaMemcpyHostToDevice);
        cudaMemcpy(matrixB, local, sizeof(int) * totalSize, cudaMemcpyHostToDevice);
        matrixAdd<<<gridDim, blockDim>>>(matrixA, matrixB, matrixC, size);
        cudaThreadSynchronize();
        cudaMemcpy(local, matrixC, sizeof(int) * totalSize, cudaMemcpyDeviceToHost);
        for(int i = 0; i < totalSize; i++){
                if(i % size == 0){
                        printf("\n%d ", local[i]);
                }
                else{
                        printf("%d ", local[i]);
                }
        }
    printf("\n");
}
