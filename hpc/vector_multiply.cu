#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

__global__ void add(int* A, int* B, int* C, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size) {
        C[tid] = A[tid] + B[tid];
    }
}

__global__ void multiply(int* A, int* B, int* C, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < size) {
        C[tid] = A[tid] * B[tid];
    }
}

// Original initialize function
/*
void initialize(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 10;
    }
}
*/

// New function to initialize vectors with random elements
void initializeRandom(int* vector, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        vector[i] = rand() % 100; // Generating random numbers between 0 to 99
    }
}

void print(int* vector, int size) {
    for (int i = 0; i < size; i++) {
        cout << vector[i] << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cout << "Enter the size of the vectors: ";
    cin >> N;

    int* A, * B, * C, * D;

    int vectorSize = N;
    size_t vectorBytes = vectorSize * sizeof(int);

    A = new int[vectorSize];
    B = new int[vectorSize];
    C = new int[vectorSize];
    D = new int[vectorSize];

    // Use the new function to initialize vectors with random elements
    initializeRandom(A, vectorSize);
    initializeRandom(B, vectorSize);

    cout << "Vector A: ";
    print(A, N);
    cout << "Vector B: ";
    print(B, N);

    int* X, * Y, * Z;
    cudaMalloc(&X, vectorBytes);
    cudaMalloc(&Y, vectorBytes);
    cudaMalloc(&Z, vectorBytes);

    cudaMemcpy(X, A, vectorBytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, vectorBytes, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    // Perform addition on GPU
    add<<<blocksPerGrid, threadsPerBlock>>>(X, Y, Z, N);

    // Perform multiplication on GPU
    multiply<<<blocksPerGrid, threadsPerBlock>>>(X, Y, Z, N);

    cudaMemcpy(C, Z, vectorBytes, cudaMemcpyDeviceToHost);

    cout << "Addition: ";
    print(C, N);

    // Clean up
    delete[] A;
    delete[] B;
    delete[] C;
    delete[] D;

    cudaFree(X);
    cudaFree(Y);
    cudaFree(Z);

    return 0;
}



// how to run: 
// open terminal - 

// run this: 
// nvcc code.cu -o code

// then this: 
// ./code

// NOTE - save the .cu file in the home directory only (file manager open karne par jo open hota hai wahi pe save karna .cu file kahi bhi mat save kro)