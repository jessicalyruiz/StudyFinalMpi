#include <iostream>
#include <mpi.h>
#include <random>
#include <chrono>
#include <functional>
#include <stdio.h>
#include <cstdio>

#define WIDTH 720
#define HEIGHT 480

#include <chrono>

namespace ch = std::chrono;

void calcular_tiempo(const std::string &msg, std::function<void(void)> fn)
{
    std::printf("-------------------------------");
    std::printf("%s\n", msg.c_str());

    auto start = ch::high_resolution_clock::now();

    // cálculo
    fn();

    auto end = ch::high_resolution_clock::now();
    ch::duration<double, std::milli> tiempo = end - start;

    std::printf("%s, tiempo=%fms \n", msg.c_str(), tiempo.count());
}

std::vector<int> generar_imagen()
{
    std::vector<int> imagen(WIDTH * HEIGHT * 4);

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);

    for (int i = 0; i < WIDTH * HEIGHT * 4; ++i)
    {
        imagen[i] = dist(gen);
    }
    return imagen;
}

int main(int argc, char **argv)
{

    MPI_Init(&argc, &argv);

    int rank, nprocs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // ID
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs); // NUM DE PROCESOS (total)

    int block_size;   // num de elementos q procesa cada rank
    int padding;      // real_size - num_elements
    int num_elements; // Total de elementos que vamos a procesar
    int real_size;    // num elementos total + los q sobran o falten

    std::vector<int> imagen, imagen_local, imagen_res;

    if (rank == 0)
    {
        // leer datos
        imagen = generar_imagen();

        num_elements = imagen.size();
        real_size = std::ceil((double)num_elements / nprocs) * nprocs;
        imagen_res.resize(real_size);
        padding = real_size - num_elements;
        block_size = real_size / nprocs;
        //*****envio datos a los ranks
        MPI_Bcast(&block_size, 1, MPI_INT, 0, MPI_COMM_WORLD); //(puntero del dato q quiero enviar, numero de elementos a enviar, tipo de datos, id rank raiz, comunicator)
        std::printf("Enviando blocksize %d\n", block_size);
        // envio el padding al ultimo rank
        MPI_Send(&padding, 1, MPI_INT, nprocs - 1, 0, MPI_COMM_WORLD); //(puntero del dato q quiero enviar, numero de elementos a enviar, tipo de datos, rank destino, tag , comunicator)
    }
    else
    {
        // recibo
        MPI_Bcast(&block_size, 1, MPI_INT, 0, MPI_COMM_WORLD); // Que recibimos
        std::printf("Recibiendo blocksize %d\n", block_size);

        // recibo padding en el ultimo rank
        if (rank == nprocs - 1)
        {
            MPI_Recv(&padding, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); ///(puntero donde recivo los datos, numero de elementos a recibir, tipo de datos, rank origen, tag , comunicator, MPI_STATUS_IGNORE )
        }
    }

    //*********proceso los datos

    imagen_local.resize(block_size);
    // distribuyo los datos
    MPI_Scatter(imagen.data(), block_size, MPI_INT, imagen_local.data(), block_size, MPI_INT, 0, MPI_COMM_WORLD); //(datos enviar desde rank root, num elementos a enviar, tipo, puntero donde recibo datos, num elementos q recibe c/proceso,tipo, id rank q envia, communicador)

    int block_size_tmp = rank == nprocs - 1 ? block_size - padding : block_size; // verifico q el ultimo no exceda

    //*****
    for (int i = 0; i < block_size_tmp; i++)
    {
        if (i % 4 == 0)
        {
            imagen_local[i] = 0;
        }
    }
    //**

    // recopilo los datos
    MPI_Gather(imagen_local.data(), block_size, MPI_INT, imagen_res.data(), block_size, MPI_INT, 0, MPI_COMM_WORLD); //(lo q se envia desde c/rank,num datos a enviar desde c/rank, tipo, puntero almacena datos recibidos, num datos recibidos, tipo, id rank root, communicador )
    imagen_res.resize(num_elements);                                                                                 // elimino los q sobren

    //*****imprimo

    if (rank == 0)
    {
        if (imagen_res.size() >= 20)
        {
            for (int i = 0; i < 20; i++)
            {
                std::printf("%d, ", imagen_res[i]);
            }
        }
        else
        {
            std::printf("imagen_res no tiene suficientes elementos.\n");
        }
    }

    MPI_Finalize();

    return 0;
}
