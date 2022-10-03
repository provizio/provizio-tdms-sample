cmake_minimum_required(VERSION 3.10)

project (TDMSREADER)
set (TDMSREADER_VERSION_MAJOR 0)
set (TDMSREADER_VERSION_MINOR 5)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(libtdms)
add_subdirectory(tdmsreader)
