cmake_minimum_required(VERSION 3.6)
project(ex3)
set(g++ -std=c++0x main.cpp BFS.cpp -lboost_serialization -o client)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
include_directories(${Boost_INCLUDE_DIR})

#[[add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)]]

set(SOURCE_FILES src/TimeListener.cpp  src/TimeListener.h src/TripTimer.cpp src/TripTimer.h src/AbstractNode.cpp src/Udp.cpp src/Udp.h src/TripTimer.cpp src/TripTimer.h src/Socket.cpp src/Socket.h src/AbstractNode.h src/AbstractCab.cpp src/AbstractCab.h src/Algorithm.h src/BFS.cpp src/BFS.h src/Cab.cpp src/Cab.h src/CarColor.h src/CarColor.h src/CarManufactur.h src/Driver.h src/Driver.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.cpp src/MainFlow.h src/Map.h src/MapFactory.h src/Node.cpp src/MatrixFactory.cpp src/MatrixFactory.h src/MatrixMap.cpp src/MatrixMap.h src/Node.h src/Passenger.cpp src/Passenger.h src/Point.cpp src/Point.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h Test/AbstractNodeTest.cpp Test/CabTest.cpp Test/gtest.cpp Test/LuxuryCabTest.cpp Test/MatrixFactoryTest.cpp Test/MatrixTest.cpp Test/NodeTest.cpp Test/test_point.cpp Test/test_texicenter.cpp Test/test_trip.cpp Test/test_passenger.cpp Test/test_bfs.cpp Test/test_driver.cpp Test/gtest.cpp src/Algorithm.cpp src/MapFactory.cpp src/Map.cpp)
#add_executable(EX2 ${SOURCE_FILES} Test/AbstractNodeTest.cpp Test/CabTest.cpp Test/LuxuryCabTest.cpp Test/MatrixFactoryTest.cpp Test/MatrixTest.cpp Test/NodeTest.cpp Test/test_point.cpp Test/test_texicenter.cpp Test/test_trip.cpp Test/test_passenger.cpp Test/test_bfs.cpp Test/test_driver.cpp Test/gtest.cpp )
add_executable(server ${SOURCE_FILES} main.cpp src/TimeListener.cpp  src/TimeListener.h src/TripTimer.cpp src/TripTimer.h src/AbstractNode.cpp src/Udp.cpp src/Udp.h src/TripTimer.cpp src/TripTimer.h src/Socket.cpp src/Socket.h src/AbstractNode.h src/AbstractCab.cpp src/AbstractCab.h src/Algorithm.h src/BFS.cpp src/BFS.h src/Cab.cpp src/Cab.h src/CarColor.h src/CarColor.h src/CarManufactur.h src/Driver.h src/Driver.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.cpp src/MainFlow.h src/Map.h src/MapFactory.h src/Node.cpp src/MatrixFactory.cpp src/MatrixFactory.h src/MatrixMap.cpp src/MatrixMap.h src/Node.h src/Passenger.cpp src/Passenger.h src/Point.cpp src/Point.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h  src/Algorithm.cpp src/MapFactory.cpp src/Map.cpp)
add_executable(client ${SOURCE_FILES} client.cpp src/TimeListener.cpp  src/TimeListener.h src/TripTimer.cpp src/TripTimer.h src/AbstractNode.cpp src/Udp.cpp src/Udp.h src/TripTimer.cpp src/TripTimer.h src/Socket.cpp src/Socket.h src/AbstractNode.h src/AbstractCab.cpp src/AbstractCab.h src/Algorithm.h src/BFS.cpp src/BFS.h src/Cab.cpp src/Cab.h src/CarColor.h src/CarColor.h src/CarManufactur.h src/Driver.h src/Driver.cpp src/LuxuryCab.h src/LuxuryCab.cpp src/MainFlow.cpp src/MainFlow.h src/Map.h src/MapFactory.h src/Node.cpp src/MatrixFactory.cpp src/MatrixFactory.h src/MatrixMap.cpp src/MatrixMap.h src/Node.h src/Passenger.cpp src/Passenger.h src/Point.cpp src/Point.h src/TaxiCenter.cpp src/TaxiCenter.h src/Trip.cpp src/Trip.h  src/Algorithm.cpp src/MapFactory.cpp src/Map.cpp client.h)

#target_link_libraries(EX2 gtest gtest_main)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
#target_link_libraries(EX2 ${Boost_LIBRARIES})


