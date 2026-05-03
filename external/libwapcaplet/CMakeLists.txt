cmake_minimum_required(VERSION 3.10)
project(libwapcaplet C)

add_library(wapcaplet src/libwapcaplet.c)

target_include_directories(wapcaplet PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(MSVC)
    # restrict=__restrict must stay PRIVATE: PUBLIC would leak into C++ consumers
    # and break MSVC headers (__declspec(__restrict) becomes invalid).
    target_compile_definitions(wapcaplet PRIVATE
        _CRT_SECURE_NO_WARNINGS
        restrict=__restrict)
endif()

install(TARGETS wapcaplet DESTINATION lib)
install(DIRECTORY include/libwapcaplet DESTINATION include)
