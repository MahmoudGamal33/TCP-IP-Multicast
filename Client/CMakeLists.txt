cmake_minimum_required(VERSION 3.0.0)
project(clientApp VERSION 0.1.0)

include(CTest)
enable_testing()

add_test("RUNNING_TEST" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}" "239.255.0.1" "3001" "Failure")

add_executable(clientApp main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} )
set(CMAKE_CXX_FLAGS " -pthread") 

include(CPack)
