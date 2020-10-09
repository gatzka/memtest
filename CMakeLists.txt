cmake_minimum_required(VERSION 3.11)

include(FetchContent)
FetchContent_Declare(GatzkaToolchainFiles
  GIT_REPOSITORY https://github.com/gatzka/cmake-toolchain-files.git
  SOURCE_DIR ${CMAKE_BINARY_DIR}/toolchains
)
FetchContent_GetProperties(GatzkaToolchainFiles)
if(NOT GatzkaToolchainFiles_POPULATED)
  FetchContent_Populate(GatzkaToolchainFiles)
endif()

project(memtest-all LANGUAGES C)

add_subdirectory(src)

