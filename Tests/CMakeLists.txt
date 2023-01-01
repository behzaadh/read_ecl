### tests
project(TestREAD_ECL CXX C)

# source
SET(TestREAD_ECL_SOURCES
    main.cpp
)

# test executable
add_executable(TestREAD_ECL ${TestREAD_ECL_SOURCES})

message("EEEEEEE:" ${CMAKE_CURRENT_BINARY_DIR})

# add created library
target_link_libraries(TestREAD_ECL READ_ECL)

# test compile and run
add_test(TestCompileAndRun TestREAD_ECL)

