cmake_minimum_required(VERSION 3.11)
project(memtest VERSION 1.0.0 LANGUAGES C)

add_library(${PROJECT_NAME}
  memtest.c
  memtest.h
)

