#include <iostream>
#include <cuda_runtime.h>

using namespace std;

__global__ void vect_add(int *A, int *B, int *C, int n)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < n)
    {
        C[i] = A[i] + B[i];
    }
}

int main()
{
    int n = 1000000;
    int size = n * sizeof(int);

    int *A, *B, *C;
    int *Dev_A, *Dev_B, *Dev_C;

    cudaMallocHost(&A, size);
    cudaMallocHost(&B, size);
    cudaMallocHost(&C, size);

    for (int i = 0; i < n; i++)
    {
        A[i] = i;
        B[i] = i * 2;
    }

    cudaMalloc(&Dev_A, size);
    cudaMalloc(&Dev_B, size);
    cudaMalloc(&Dev_C, size);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    cudaMemcpy(Dev_A, A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(Dev_B, B, size, cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlock = (n + blockSize - 1) / blockSize;

    vect_add<<<numBlock, blockSize>>>(Dev_A, Dev_B, Dev_C, n);

    cudaMemcpy(C, Dev_C, size, cudaMemcpyDeviceToHost);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);
    for (int i = 0; i < 10; i++)
        cout << C[i] << " ";
    cout << endl;
    cout << "Time Taken: " << ms / 1000 << endl;

    cudaFree(Dev_A);
    cudaFree(Dev_B);
    cudaFree(Dev_C);
    cudaFreeHost(A);
    cudaFreeHost(B);
    cudaFreeHost(C);

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    return 0;
}