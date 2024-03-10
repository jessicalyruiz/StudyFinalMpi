cmake_minimum_required(VERSION 3.26)
project(StudyOpenMP)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-fopenmp")

add_executable(StudyOpenMP main.cpp)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.1.1
)
FetchContent_MakeAvailable(fmt)
target_link_libraries(StudyOpenMP fmt::fmt libfort::fort)


FetchContent_Declare(
        fort
        GIT_REPOSITORY https://github.com/seleznevae/libfort.git
        GIT_TAG v0.4.2
)

FetchContent_MakeAvailable(fort)