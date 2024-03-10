#include <iostream>
#include <omp.h>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

#define WIDTH 720
#define HEIGHT 480

std::vector<int> generar_imagen(){
    std::vector<int> imagen(WIDTH*HEIGHT*4);
    for (int i = 0; i < WIDTH*HEIGHT*4; ++i) {
        imagen[i]=255;
    }
    return imagen;

}


int main() {
    //1.- generar vector o leer datos
    auto v=generar_imagen();

    int thread_num;
    int block_size;
    int num_elements=WIDTH*HEIGHT*4;
    std::vector<int> v_resp(num_elements);
    //paso esta info a cada hilo
#pragma omp parallel default(none) shared(thread_num, block_size,num_elements, v_resp,v)
    {
#pragma omp master
        {

            thread_num = omp_get_num_threads();

            block_size = std::ceil((double) num_elements / thread_num);
        }

        int thread_id = omp_get_thread_num();
        //proceso los datos
        // division manual
        int start = thread_id * block_size;
        int end = (thread_id == thread_num - 1) ? num_elements : (thread_id + 1) * block_size;

        for (int i = start; i < end; ++i) {
            if (i % 4 == 0) {
                v_resp[i] = 0;
            } else {
                v_resp[i] = v[i];
            }
        }
        //uno los datos


        //imprimo los datos
#pragma omp for
        for (int i = 0; i < WIDTH * HEIGHT * 4; ++i) {
            fmt::print("{}", v_resp);
        }
    }



    //ventana
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    //creo textura
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    // Convertir los datos de la imagen a sf::Uint8 y asegurarse de que estén en el formato correcto
    std::vector<sf::Uint8> imageData(v_resp.begin(), v_resp.end());

    // Actualizar la textura con los datos de la imagen
    texture.update(imageData.data());

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sprite.setTexture(texture);

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }











    return 0;
}
