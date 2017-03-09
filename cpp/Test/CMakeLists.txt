cmake_minimum_required(VERSION 3.3)

project(ex3)


include(CTest)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
set(test_SRCS gtest.cpp CabTest.cpp AbstractNodeTest.cpp LuxuryCabTest.cpp MatrixTest.cpp MatrixFactoryTest.cpp NodeTest.cpp test_bfs.cpp test_driver.cpp test_passenger.cpp test_point.cpp test_texicenter.cpp test_trip.cpp gtest.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock core)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.