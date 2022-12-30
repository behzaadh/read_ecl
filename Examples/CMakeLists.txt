### tests
project(EaxmpleREAD_ECL CXX C)


# copy the original file to the executable path
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/2D.S0001"
   "${CMAKE_CURRENT_BINARY_DIR}/2D.S0001" COPYONLY)

message("Examples:" ${CMAKE_CURRENT_BINARY_DIR})


