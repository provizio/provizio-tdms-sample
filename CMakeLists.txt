cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

project(provizio-tdms-sample)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 6)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# libtdms
add_subdirectory(libtdms)

# Provizio Core Radar API
# Include support for ExternalProject_Add
set(PROVIZIO_RADAR_CORE_API_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/provizio_radar_api_core_build")
set(PROVIZIO_RADAR_CORE_API_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/provizio_radar_api_core")
set(PROVIZIO_RADAR_CORE_API_PREFIX "${CMAKE_CURRENT_BINARY_DIR}")
set(PROVIZIO_RADAR_CORE_API_GITHUB_PROJECT "provizio/provizio_radar_api_core") # Or your own fork
set(PROVIZIO_RADAR_CORE_API_GITHUB_BRANCH "master") # Or a specific tag you'd like to use
set(PROVIZIO_RADAR_CORE_API_INSTALL_DIR "${PROVIZIO_RADAR_CORE_API_BINARY_DIR}/install")
ExternalProject_Add(libprovizio_radar_api_core
  GIT_REPOSITORY "https://github.com/${PROVIZIO_RADAR_CORE_API_GITHUB_PROJECT}.git" # or "git@github.com:${PROVIZIO_RADAR_CORE_API_GITHUB_PROJECT}.git" for ssh access, or your custom repo
  GIT_TAG "${PROVIZIO_RADAR_CORE_API_GITHUB_BRANCH}"
  PREFIX "${PROVIZIO_RADAR_CORE_API_PREFIX}"
  SOURCE_DIR "${PROVIZIO_RADAR_CORE_API_SOURCE_DIR}"
  BINARY_DIR "${PROVIZIO_RADAR_CORE_API_BINARY_DIR}"
  CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}" "-DCMAKE_INSTALL_PREFIX=${PROVIZIO_RADAR_CORE_API_INSTALL_DIR}" "-DENABLE_CHECK_FORMAT=OFF" "-DBUILD_TESTING=OFF"
)

# Create target executable
add_executable(provizio-tdms-sample src/main.cpp)
target_include_directories(provizio-tdms-sample PUBLIC ${PROJECT_BINARY_DIR})
target_link_libraries(provizio-tdms-sample PUBLIC libtdms)

add_dependencies(provizio-tdms-sample libprovizio_radar_api_core)
target_include_directories(provizio-tdms-sample SYSTEM PUBLIC "${PROVIZIO_RADAR_CORE_API_INSTALL_DIR}/include")

if("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.13.0")
  target_link_directories(provizio-tdms-sample PUBLIC "${PROVIZIO_RADAR_CORE_API_INSTALL_DIR}/lib")
else()
  link_directories("${PROVIZIO_RADAR_CORE_API_INSTALL_DIR}/lib")
endif("${CMAKE_VERSION}" VERSION_GREATER_EQUAL "3.13.0")

target_link_libraries(provizio-tdms-sample PUBLIC provizio_radar_api_core)
