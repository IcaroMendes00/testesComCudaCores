/*****************************************************

Codigo de exemplo de teste com Cuda Cores
Date: 12/08/2023 

******************************************************/


#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

#define vectorA {1,2,5,5,6,7,9,1,4,4,3,5,8,7,4,5,8,7,4,5,8}
#define vectorB {7,8,4,5,7,8,7,4,4,4,5,8,5,8,5,8,8,5,5,5,4}

__global__ void vectorAdd(int *a, int* b, int* c)
{
    int i = threadIdx.x;
    c[i] = a[i] + b[i];

    return ;
}

int main()
{

    int a[] = vectorA;
    int b[] = vectorB;
    int c[sizeof (a) / sizeof(int)] = {0};

    for (int i = 0; i < sizeof(c)/sizeof(int); i++)
    {
        c[i] = a[i] + b[i];
    }

    // cria ponteiros dentro da gpu
    int* cudaA = 0;
    int* cudaB = 0;
    int* cudaC = 0;

    // aloca memoria na gpu
    cudaMalloc(&cudaA, sizeof(a));
    cudaMalloc(&cudaB, sizeof(b));
    cudaMalloc(&cudaC, sizeof(c));

    // copia os vetores dentro da gpu
    cudaMemcpy(cudaA, a, sizeof(a), cudaMemcpyHostToDevice);
    cudaMemcpy(cudaB, b, sizeof(b), cudaMemcpyHostToDevice);


    //vectorAdd <<< GRID_SIZE, BLOCK_SIZE
    vectorAdd <<< 1, sizeof(a) / sizeof(int) >>> (cudaA, cudaB, cudaC);
    //aqui a cpu diz a gpu, rode essa funcao vectroAdd em um cuda kernel
    //em um grid de (1) bloco e o bloco tem as threads (sizeof(a) / sizeof(int))
    //e os chame (>>>) com esses parametros (cudaA, cudaB, cudaC)

    cudaMemcpy(c, cudaaC, sizeof(c), cudaMemcpyDeviceToHost);

    return;
    
}
