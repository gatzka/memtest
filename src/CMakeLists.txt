cmake_minimum_required(VERSION 3.11)
project(memtest VERSION 1.0.0 LANGUAGES C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake/)
include(ClangFormat)

add_library(${PROJECT_NAME}
  memtest.c
  memtest.h
)

AddClangFormat(${PROJECT_NAME})
