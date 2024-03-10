cmake_minimum_required(VERSION 3.26)
project(FinalStudyMpi)

set(CMAKE_CXX_STANDARD 17)
#habilitar el soporte para OpenMP
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

#find_package(fmt)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1
)
FetchContent_MakeAvailable(fmt)

add_executable(FinalS main.cpp)
target_link_libraries(FinalS fmt::fmt)

find_package(SFML)
target_link_libraries(FinalS sfml::sfml)

add_executable(correcionPrueba
        correcionPrueba.cpp)
target_link_libraries(correcionPrueba sfml::sfml fmt::fmt)


