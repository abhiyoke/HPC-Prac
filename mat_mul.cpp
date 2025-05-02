#include<iostream>
#include<cuda_runtime.h>

using namespace std;

__global__ matmul(int* A, int* B, int* C, int n){
	int r=blockIdx.y * blockDim.y + threadIdx.y;
	int c=blockIdx.x * blockDim.x + threadIdx.x;
	if(r<n && c<n){
		int p=0;
		for(int k=0;k<n;k++){
			p+=A[r*N+k]*B[k*N+c];
		}
		C[r*N+c]=p;
	}
	
}

int main(){
	int n=512;
	int size=n*n*sizeof(int);
	
	int *A,*B,*C;
	int *Dev_A,*Dev_B,*Dev_C;
	
	cudaMallocHost(&A,size);
	cudaMallocHost(&B,size);
	cudaMallocHost(&C,size);
	
	cudaMalloc(&Dev_A,size);
	cudaMalloc(&Dev_B,size);
        cudaMalloc(&Dev_C,size);
        
        for(int i=0;i<n;i++){
        	for(int j=0;j<n;j++){
        		A[i*n+j]=i*n+j;
        		B[i*n+j]=j*n+i;
        	}
        }
        
        cudaEvent_t start,stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);
        cudaEventRecord(start);
        
        cudaMemcpy(Dev_A,A,size,cudaMemcpyHostToDevice);
        cudaMemcpy(Dev_B,B,size,cudaMemcpyHostToDevice);
        
        dim3 dimBlock(16,15);
        dim3 dimGrid(n/dimBlock.x,n/dimBlock.y);
        
        matmul<<<dimGrid,dimBlock>>>(Dev_A,Dev_B,Dev_C,n);
        
        cudaMemcpy(Dev_C,C,size,cudaMemcpyDeviceToHost);
        
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        int ms=0;
        cudaEventElapsedTime(&ms,start,stop);
        for(int i=0;i<n;i++){
        	for(int j=0;j<n;j++){
        		cout<<C[i*n+j]<<" ";
        	}
        	cout<<endl;
        }
        cout<<"Time taken: "<<ms/1000;
        


return 0;
}

