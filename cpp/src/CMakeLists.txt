set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(core_SRCS Algorithm.h Algorithm.cpp AbstractCab.cpp AbstractCab.h
        AbstractNode.cpp AbstractNode.h BFS.cpp BFS.h MatrixMap.cpp
        MatrixMap.h MapFactory.cpp MapFactory.h MatrixFactory.cpp
        MatrixFactory.h Node.cpp Node.h Point.cpp Point.h Driver.cpp Driver.h
        Cab.cpp Cab.h Map.h Map.cpp Passenger.cpp Passenger.h TaxiCenter.cpp
        TaxiCenter.h LuxuryCab.cpp LuxuryCab.h Trip.cpp TaxiCenter.cpp Trip.h
        MainFlow.cpp MainFlow.h TimeListener.h TimeListener.cpp TripTimer.h
        CarColor.h CarManufactur.h TripTimer.cpp)

#add_library(core ${core_SRCS})
add_executable(AP1_EXE ${core_SRCS})

#target_link_libraries(exe core)

