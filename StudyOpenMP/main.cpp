#include <iostream>
#include <omp.h>
#include <fmt/core.h>
#include <vector>
#include <chrono>
#include <functional>
#include <fstream>
#include <fort.hpp>

namespace ch = std::chrono;
#define ELEMENTS 10000000
static std::vector<int> datos;


std::string crear_tabla(const std::vector<int> &freqs) {
    fort::utf8_table table;
    table << fort::header;
    table << "Valor";
    table << "Conteo";
    table << fort::endr;

    for (int index = 0; index < freqs.size(); index++) {
        table << index;
        table << freqs[index];
        table << fort::endr;
    }

    return table.to_string();
}


std::vector<int> read_file() {
    std::fstream fs("D:/PERSONAL-Jessi/Documents/UCE/10mo/Paralle/datos.txt", std::ios::in);
    std::string line;
    std::vector<int> ret;
    while (std::getline(fs, line)) {
        ret.push_back(std::stoi(line));
    }
    fs.close();
    return ret;
}


void calcular_tiempo(const std::string &msg, std::function<void(void)> fn) {
    fmt::println("-------------------------------");
    fmt::println("{}", msg);

    auto start = ch::high_resolution_clock::now();

    // cálculo
    fn();

    auto end = ch::high_resolution_clock::now();
    ch::duration<double, std::milli> tiempo = end - start;

    fmt::println("{}, tiempo={}ms", msg, tiempo.count());
}

int sumaSerial(std::vector<int> datos) {
    int suma = 0;
    for (int i = 0; i < datos.size(); ++i) {
        suma += datos[i];
    }
    return suma;
}

int sumaParalela(std::vector<int> datos) {
    int suma = 0;
#pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < datos.size(); ++i) {
        suma += datos[i];
    }
    return suma;
}

double promedioSerial(std::vector<int> datos) {
    int suma = sumaSerial(datos);
    return suma / datos.size();
}

double promedioParalello(std::vector<int> datos) {
    int suma_total = 0;

#pragma omp parallel default(none) shared(suma_total, datos)
    {
        int thread_id = omp_get_thread_num();
        int num_theads = omp_get_num_threads();

        int suma_parcial = 0;
        for (int i = thread_id; i < datos.size(); i += num_theads) {
            suma_parcial += datos[i];
        }
#pragma omp critical
        {
            suma_total = suma_total + suma_parcial;
        }
    }
    return suma_total / (double) datos.size();
}


std::vector<int> serialFrequency(std::vector<int> datos) {
    std::vector<int> frequencias(101);
    for (int i: datos) {
        frequencias[i]++;
    }
    return frequencias;
}


std::vector<int> ParallelFrequency(std::vector<int> datos) {
    std::vector<int> frequencias(101);

#pragma omp parallel default(none) shared(datos, frequencias)
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        std::vector<int> frequencias_local(101, 0);
        for (int i = thread_id; i < datos.size(); i += num_threads) {
            frequencias_local[datos[i]]++;
        }
#pragma omp critical
        for (int i = 0; i < frequencias.size(); ++i) {
            frequencias[i] += frequencias_local[i];
        }
    }

    return frequencias;
}


std::tuple<int, int> serialMaxMin(const std::vector<int> &datos) {
    int max = datos[0];
    int min = datos[0];
    for (int i: datos) {
        if (i > max) {
            max = i;
        }
        if (i < min) {
            min = i;
        }
    }

    return {max, min};
}


std::tuple<int, int> ParallelMaxMin(const std::vector<int> &datos) {
    int max = datos[0];
    int min = datos[0];
    int num_threads;
    long block_size;

#pragma omp parallel default(none) shared(datos, min, max, num_threads, block_size)
    {
#pragma omp master
        {
            num_threads = omp_get_num_threads();
            block_size = datos.size() / num_threads;
        }
#pragma omp barrier
        int thread_id = omp_get_thread_num();
        int start = thread_id * block_size;
        int end = (thread_id + 1) * block_size;
        if (thread_id == num_threads - 1) {
            end = datos.size();
        }

        int max_local = datos[start];
        int min_local = datos[start];
        for (int i = start; i < end; i++) {
            if (datos[i] > max_local) {
                max_local = datos[i];
            }
            if (datos[i] < min_local) {
                min_local = datos[i];
            }
        }
#pragma omp critical
        {
            if (max_local > max) {
                max = max_local;
            }
            if (min_local < min) {
                min = min_local;
            }
        }
    }
    return {max, min};
}

double funcion(double x) {
    return 4.0 / (1 + x * x);
}

//met del trapecio
double integralSerial(double a, double b, int n) {

    double h = (b - a) / (double) n; //step
    double suma = 0.5 * (funcion(a) + funcion(b));

    for (int i = a; i < n; ++i) {
        double x = a + i * h;
        suma += funcion(x);
    }
    return suma * h;
}

double integralParalel(double a, double b, int n) {
    double h = (b - a) / (double) n; //step
    double suma = 0.5 * (funcion(a) + funcion(b));
    int num_threads;
    int block_size;
#pragma omp parallel default(none) shared(h, n, suma, num_threads, block_size,a)
    {
        #pragma omp master
            {
                num_threads = omp_get_num_threads();
                block_size = n / num_threads;
            }
        #pragma omp barrier

        int thread_id = omp_get_thread_num();
        int start = block_size * thread_id;
        int end = (thread_id + 1) * block_size;
        if (end == num_threads - 1) {
            end = n;
        }
        double suma_parcial = 0;
        for (int i = start; i < end; ++i) {
            double x = a + i * h;
            suma_parcial += funcion(x);
        }

        #pragma omp critical
        {
            suma += suma_parcial;
        }
    }
    return suma*h;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    /*
#pragma omp parallel num_threads(5)
    {
    int thread_id=omp_get_thread_num();
    fmt::print("Hello  {} Of {}\n", thread_id,  omp_get_num_threads());
        fmt::print(" Jessi {}\n", thread_id);
    }
*/
    /*
    int n=20;
#pragma omp parallel for
    for (int i = 0; i <n ; ++i) {

        int thread_id=omp_get_thread_num();
        fmt::print("Hello hilo {} Of {} iteracion {}\n", thread_id,  omp_get_num_threads(),i );
       // fmt::print(" Jessi {}\n", thread_id);
    }*/

    //sumo los elementos de un array


    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    //inicializo con nun de elementos y con un valor por defecto
    std::vector<int> vector2(ELEMENTS, 1);
    /*
   int suma=0;
    calcular_tiempo("Serial Suma", [&](){suma= sumaSerial(vector2);});
    fmt::println("suma={}", suma);

    int sumaParal=0;
    calcular_tiempo("Paralela Suma", [&](){sumaParal= sumaParalela(vector2);});
    fmt::println("suma={}", sumaParal);
*/
    datos = read_file();
    /*
    fmt::println("datos: {}", datos.size());
    double promedio;
    calcular_tiempo("SerialPromedio", [&](){promedio= promedioSerial(datos);});
    fmt::println("prom={}", promedio);

    double promedioP;
    calcular_tiempo("ParaleloPromedio", [&](){promedioP= promedioParalello(datos);});
    fmt::println("prom={}", promedio);

*/
/*
    fmt::println("datos: {}", datos.size());
    std::vector<int> freq;
    calcular_tiempo("Serial", [&](){freq= serialFrequency(datos);});
    std::cout << crear_tabla(freq) << std::endl;

    std::vector<int> freqP;
    calcular_tiempo("Paralelo", [&](){freqP= ParallelFrequency(datos);});
    std::cout << crear_tabla(freqP) << std::endl;

*/
/*

    fmt::println("datos: {}", datos.size());
    std::tuple<int,int> max_min;
    calcular_tiempo("Serial", [&](){max_min= serialMaxMin(datos);});
    auto[max,min]=max_min;
    fmt::println("max_min={} {}", max,min);

    std::tuple<int,int> max_minP;
    calcular_tiempo("Paralelo", [&](){max_minP= ParallelMaxMin(datos);});
    auto[maxP,minP]=max_minP;
    fmt::println("max_min={} {}", maxP,minP);
*/

    double integral ;
    calcular_tiempo("Paralelo", [&](){integral= integralSerial(0, 1, ELEMENTS);});
    fmt::println("integral pi={}", integral);

    double integralP ;
    calcular_tiempo("Paralelo", [&](){integralP= integralParalel(0, 1, ELEMENTS);});
    fmt::println("integral pi={}", integralP);


    return 0;
}
