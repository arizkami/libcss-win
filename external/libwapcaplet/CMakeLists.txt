cmake_minimum_required(VERSION 3.10)
project(libwapcaplet C)

include_directories(include)

add_library(wapcaplet src/libwapcaplet.c)

if(MSVC)
    target_compile_definitions(wapcaplet PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_definitions(wapcaplet PUBLIC restrict=__restrict)
endif()

install(TARGETS wapcaplet DESTINATION lib)
install(DIRECTORY include/libwapcaplet DESTINATION include)
