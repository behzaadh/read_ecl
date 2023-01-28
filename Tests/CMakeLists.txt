### tests
project(TestREAD_ECL CXX C)

# source
SET(TestREAD_ECL_SOURCES
    main.cpp
)

if (BUILD_PY_LIBS)
    # test executable
    add_executable(TestREAD_ECL ${TestREAD_ECL_SOURCES} main.py)

    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)

    configure_file(main.py ${PARENT_DIR} COPYONLY)

    find_package(PythonInterp 3.0 REQUIRED)

    add_custom_target(run_pyscript
      COMMAND ${PYTHON_EXECUTABLE} ${PARENT_DIR}/main.py > ${CMAKE_CURRENT_BINARY_DIR}/output.txt
      DEPENDS ${PARENT_DIR}/main.py
      COMMENT "Running script test"
      WORKING_DIRECTORY ${PARENT_DIR}
    )
    add_dependencies(TestREAD_ECL run_pyscript)
else()
    # test executable
    add_executable(TestREAD_ECL ${TestREAD_ECL_SOURCES})
endif()

# add created library
target_link_libraries(TestREAD_ECL READ_ECL)

# test compile and run
add_test(TestCompileAndRun TestREAD_ECL)
