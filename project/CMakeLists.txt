cmake_minimum_required(VERSION 3.26)
project(project CUDA)

enable_language(CXX CUDA)
set(CMAKE_CUDA_STANDARD 17)

add_executable(project kernel.cu
        main.cpp
        main2.cpp)

set_target_properties(project PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
find_package(SFML)
find_package(fmt)
target_link_libraries(project fmt::fmt sfml::sfml
                    ${CUDART_LIBRARY})

target_link_directories(project PRIVATE ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES}
)