cmake_minimum_required (VERSION 3.10)

project(READ_ECL)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(READ_ECL_SOURCES
  src/read_ecl.cpp
  src/read_ecl.h
)


# setup include directories
include_directories("${PROJECT_SOURCE_DIR}/src")

# dll/shared objects
OPTION(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
SET(LIB_TYPE STATIC)
if (BUILD_SHARED_LIBS)
  SET(LIB_TYPE SHARED)
endif()
add_library(READ_ECL ${LIB_TYPE} ${READ_ECL_SOURCES})

SET(READ_ECL_Headers
${PROJECT_SOURCE_DIR}/src/read_ecl.h
)

# tests
enable_testing()

# subdirs
add_subdirectory("${CMAKE_SOURCE_DIR}/Examples")
add_subdirectory("${CMAKE_SOURCE_DIR}/Tests")

target_compile_definitions(READ_ECL PRIVATE READ_ECL_LIBRARY)
