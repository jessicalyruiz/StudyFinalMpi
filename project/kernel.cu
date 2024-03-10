#include <cuda_runtime.h>

__global__ void histograma_kernel(int* d_arr, int* d_res, int n, int grupos, int min, int intervalo) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < n) {
        int indice = (d_arr[tid] - min) / intervalo;

        if (indice < grupos) {
            atomicAdd(&d_res[indice], 1);
        } else {
            atomicAdd(&d_res[indice - 1], 1);
        }
    }
}

extern "C" void invoke_histograma_cuda(int* d_arr, int* d_res, int n, int grupos, int min, int intervalo) {
    int block_size = 256;
    int grid_size = (n + block_size - 1) / block_size;

    histograma_kernel<<<grid_size, block_size>>>(d_arr, d_res, n, grupos, min, intervalo);
}