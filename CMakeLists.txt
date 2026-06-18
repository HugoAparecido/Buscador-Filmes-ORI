cmake_minimum_required(VERSION 3.16)
project(BuscadorFilmes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(BuscadorFilmes 
    arvore_b_plus.cpp 
    indice_invertido.cpp
)

target_link_libraries(BuscadorFilmes PRIVATE Qt6::Widgets)

add_executable(TesteQt main_qt.cpp)
target_link_libraries(TesteQt PRIVATE Qt6::Widgets)