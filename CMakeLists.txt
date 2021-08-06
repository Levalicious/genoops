cmake_minimum_required(VERSION 3.19)
project(goops C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-march=native -mavx2 -O3 -flto")

add_executable(goops main.c goops.h types.h time.h time.c rns.h rns.c rng.h rng.c imath.h imath.c ginstrs.h gdefs.h)

target_link_libraries(goops -lpthread -lgmp -lm)