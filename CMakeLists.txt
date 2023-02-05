cmake_minimum_required (VERSION 3.10)

project(READ_ECL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(READ_ECL_SOURCES
  src/read_ecl.cpp
  src/read_ecl.h
  src/read_ecl_C.cpp
  src/read_ecl_C.h
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
OPTION(BUILD_PY_LIBS "Build python Libraries" OFF)

if (BUILD_PY_LIBS)
    add_subdirectory("${PROJECT_SOURCE_DIR}/3rdParty/pybind11/")
# The python module must have the same name as the directory defined in CMake (read_ecl4py)
# https://stackoverflow.com/questions/50832434/python-and-c-pybind11-python-extension-module-import-error
    pybind11_add_module(
        read_ecl4py
        "${CMAKE_SOURCE_DIR}/Src/read_ecl.py.cpp"
    )
# Specifies sources to use when building a target and/or its dependents
    target_sources(read_ecl4py PRIVATE
        ${READ_ECL_SOURCES}
    )
    target_link_libraries(
        read_ecl4py
        LINK_PRIVATE pybind11::embed
    )

endif()


#OPTION(BUILD_MATLAB_API "Build MATLAB Data API" OFF)

#if (BUILD_MATLAB_API)
#    if(WIN32)
#        set(Matlab_INCLUDE_DIRS "C:/Program Files/MATLAB/R2022b/extern/include")
#        set(Matlab_LIBRARIES "C:/Program Files/MATLAB/R2022b/extern/lib/win64/microsoft")
#        set(Matlab_USE_STATIC_LIBS ON)
#    endif()
##    list(APPEND your_target_SOURCES "extra.cpp")
#    find_package(Matlab REQUIRED)
#    include_directories(${Matlab_INCLUDE_DIRS})
#    target_link_libraries(${CMAKE_PROJECT_NAME} ${Matlab_LIBRARIES})

#endif()


target_compile_definitions(READ_ECL PRIVATE READ_ECL_LIBRARY)
