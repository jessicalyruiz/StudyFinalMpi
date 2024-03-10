//
// Created by Jessirena on 21/02/2024.
//
#include <vector>
#include <chrono>
#include <random>
#include <fmt/core.h>
#include <windows.h>
#include <functional>

#include <cuda_runtime.h>

#define SIZE 1000000000

namespace ch=std::chrono;


COORD coord = {0,0};



extern "C" void invoke_histograma_cuda(int* d_arr, int* d_res, int n, int grupos, int intervalo);

void calcular_tiempo(const std::string& msg, std::function<void(void)> fn) {
    fmt::println("-------------------------------");
    fmt::println("{}", msg);

    auto start = ch::high_resolution_clock::now();

    fn();

    auto end = ch::high_resolution_clock::now();
    ch::duration<double, std::milli> tiempo = end - start;

    fmt::println("{}, tiempo={}ms", msg, tiempo.count() );
}

std::vector<int> histograma_serial(int *arr, int n, int grupos) {


    std::vector<int> res(grupos,0);
    int intervalo = std::ceil((double) 256 /grupos);
    //int intervalo = (max - min)/grupos;
    fmt::println("intervalo: {}", intervalo);

    for (int i = 0; i < n; i++) {
        int indice = arr[i]/ intervalo;

        if (indice < grupos) {
            res[indice]++;
        }else{
            res[indice-1]++;
        }

    }

    return  res;
}

//v1
//std::vector<int> histograma_omp(int *arr, int n, int grupos) {
//
//    std::vector<int> res(grupos,0);
//
//    int intervalo = std::ceil((double) 256 /grupos);
//    fmt::println("intervalo: {}", intervalo);
//
//#pragma omp parallel default(none) shared(arr, n, res, grupos, intervalo)
//    {
//        std::vector<int> tmp(grupos, 0);
//
//#pragma omp for
//        for (int i = 0; i < n; i++) {
//            int indice = arr[i]/intervalo;
//
//            if (indice < grupos) {
//                tmp[indice]++;
//            }else{
//                tmp[indice-1]++;
//            }
//        }
//
//#pragma omp critical
//        {
//            for (int i = 0; i < res.size(); ++i) {
//                res[i] += tmp[i];
//            }
//        };
//    };
//
//    return  res;
//}

//v2

std::vector<int> histograma_omp(int *arr, int n, int grupos) {


    std::vector<int> res(grupos, 0);
    int intervalo = std::ceil((double) 256 /grupos);

    // Mostrar información de intervalo, mínimo y máximo
    fmt::print("intervalo: {}\n", intervalo);

    // Calcular histograma en paralelo
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int indice = arr[i] / intervalo;

        if (indice < grupos) {
#pragma omp atomic
            res[indice]++;
        } else {
#pragma omp atomic
            res[indice - 1]++;
        }
    }

    return res;
}

void imprimir(int* arr, int n){
    int suma = 0;
    for (int i = 0; i < n; ++i) {
        suma+= arr[i];
        fmt::println("Grupo {}: {} ",i,arr[i]);
    }
    fmt::println("Total {}",suma);
}

std::vector<int> histograma_cuda(int *arr, int n, int grupos) {


    std::vector<int> res(grupos, 0);
    int intervalo = std::ceil((double) 256 /grupos);

    fmt::println("intervalo: {}", intervalo);

    int* d_arr;
    int* d_res;

    cudaMalloc(&d_arr, n * sizeof(int));
    cudaMalloc(&d_res, grupos * sizeof(int));

    cudaMemcpy(d_arr, arr, n * sizeof(int), cudaMemcpyHostToDevice);

    invoke_histograma_cuda(d_arr, d_res, n, grupos, intervalo);

    //host
    cudaMemcpy(res.data(), d_res, grupos * sizeof(int), cudaMemcpyDeviceToHost);

    //liberar (si no se hace parece que es más rapido)
    cudaFree(d_arr);
    cudaFree(d_res);

    return res;
}

int main(){

    std::vector<int> datos(SIZE);


    for (int i = 0; i < SIZE; ++i) {
        datos[i] = (rand() % 256);
    }

    std::vector<int> res_serial;

    calcular_tiempo("Calculo Serial", [&datos, &res_serial](){
        res_serial = histograma_serial(datos.data(), SIZE, 7);
    });

    imprimir(res_serial.data(), res_serial.size());

    std::vector<int> res_paralelo;

    calcular_tiempo("Calculo OpenMp", [&datos, &res_paralelo](){
        res_paralelo = histograma_omp(datos.data(), SIZE, 7);
    });

    imprimir(res_paralelo.data(), res_paralelo.size());

    std::vector<int> res_cuda;

    calcular_tiempo("Calculo CUDA", [&datos, &res_cuda]() {
        res_cuda = histograma_cuda(datos.data(), SIZE, 7);
    });

    imprimir(res_cuda.data(), res_cuda.size());

    return 0;
}