cmake_minimum_required(VERSION 3.10)

project(provizio-tdms-sample)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 6)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(libtdms)

# Create executable
add_executable(provizio-tdms-sample src/main.cpp)

target_link_libraries(provizio-tdms-sample PUBLIC libtdms)
