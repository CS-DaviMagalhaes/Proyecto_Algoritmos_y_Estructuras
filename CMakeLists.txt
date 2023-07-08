cmake_minimum_required(VERSION 3.25)
project(Proyecto_Algoritmos_y_Estructuras)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto_Algoritmos_y_Estructuras
        Block.h
        BlockChain.h
        double.h
        heap.h
        heapMon.h
        list.h
        main.cpp
        menu.h
        node.h
        retiro.h
        SHA256.h)
