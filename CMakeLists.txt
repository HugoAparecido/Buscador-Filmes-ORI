cmake_minimum_required(VERSION 3.16)
project(BuscadorFilmesGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(BuscadorFilmesGUI 
    main_qt.cpp
    arvore_b_plus.cpp 
    indice_invertido.cpp
)

target_link_libraries(BuscadorFilmesGUI PRIVATE Qt6::Widgets)
add_executable(BuscadorFilmesT
    main.cpp
    arvore_b_plus.cpp   
    indice_invertido.cpp
    terminal.cpp
)