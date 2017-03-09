all: server.out client.out 

server.out: main.o AbstractNode.o MapFactory.o MatrixFactory.o TimeListener.o TripTimer.o TaxiCenter.o Algorithm.o Map.o MainFlow.o BFS.o AbstractCab.o Point.o Passenger.o Node.o LuxuryCab.o MatrixMap.o Udp.o Driver.o Cab.o Trip.o Socket.o Tcp.o Job.o ThreadPool.o
	g++ -std=c++0x -pthread main.o AbstractNode.o MapFactory.o MatrixFactory.o TimeListener.o TripTimer.o TaxiCenter.o Algorithm.o Map.o MainFlow.o BFS.o AbstractCab.o Point.o Passenger.o Node.o LuxuryCab.o MatrixMap.o Tcp.o Udp.o Driver.o Cab.o Trip.o Socket.o Job.o ThreadPool.o -lboost_serialization -lboost_regex -I. -o server.out

client.out: client.o AbstractNode.o MapFactory.o MatrixFactory.o TimeListener.o TripTimer.o TaxiCenter.o Algorithm.o Map.o MainFlow.o BFS.o AbstractCab.o Point.o Passenger.o Node.o LuxuryCab.o MatrixMap.o Udp.o Driver.o Cab.o Trip.o Socket.o Tcp.o Job.o ThreadPool.o
	g++ -std=c++0x -pthread client.o AbstractNode.o MapFactory.o MatrixFactory.o TimeListener.o TripTimer.o TaxiCenter.o Algorithm.o Map.o MainFlow.o BFS.o AbstractCab.o Point.o Passenger.o Node.o LuxuryCab.o MatrixMap.o Udp.o Driver.o Cab.o Tcp.o Trip.o Socket.o Job.o ThreadPool.o -lboost_serialization -lboost_regex -I. -o client.out

Job.o: src/Job.cpp src/Job.h
	g++ -std=c++0x -pthread -c src/Job.cpp

ThreadPool.o: src/ThreadPool.cpp src/ThreadPool.h
	g++ -std=c++0x -pthread -c src/ThreadPool.cpp

MapFactory.o: src/MapFactory.cpp src/MapFactory.h
	g++ -std=c++0x -pthread -c src/MapFactory.cpp

MatrixFactory.o: src/MatrixFactory.cpp src/MatrixFactory.h
	g++ -std=c++0x -pthread -c src/MatrixFactory.cpp

TimeListener.o: src/TimeListener.cpp src/TimeListener.h
	g++ -std=c++0x -pthread -c src/TimeListener.cpp

TripTimer.o: src/TripTimer.cpp src/TripTimer.h
	g++ -std=c++0x -pthread -c src/TripTimer.cpp

client.o: client.cpp client.h
	g++ -std=c++0x -pthread -c client.cpp

main.o: main.cpp
	g++ -std=c++0x -pthread -c main.cpp

Socket.o: src/Socket.cpp src/Socket.h
	g++ -std=c++0x -pthread -c src/Socket.cpp

Tcp.o: src/Tcp.cpp src/Tcp.h src/Socket.h src/Socket.cpp
	g++ -std=c++0x -pthread -c src/Tcp.cpp src/Socket.cpp

Udp.o: src/Udp.cpp src/Udp.h src/Socket.h src/Socket.cpp
	g++ -std=c++0x -pthread -c src/Udp.cpp src/Socket.cpp

AbstractNode.o: src/AbstractNode.cpp src/AbstractNode.h
	g++ -std=c++0x -pthread -c src/AbstractNode.cpp

BFS.o: src/BFS.cpp src/BFS.h src/AbstractNode.h
	g++ -std=c++0x -pthread -c src/BFS.cpp

Cab.o: src/Cab.cpp src/Cab.h
	g++ -std=c++0x -pthread -c src/Cab.cpp

Driver.o: src/Driver.cpp src/Driver.h
	g++ -std=c++0x -pthread -c src/Driver.cpp

LuxuryCab.o: src/LuxuryCab.cpp src/LuxuryCab.h
	g++ -std=c++0x -pthread -c src/LuxuryCab.cpp

MainFlow.o: src/MainFlow.cpp src/MainFlow.h
	g++ -std=c++0x -pthread -c src/MainFlow.cpp

Map.o: src/Map.cpp src/Map.h
	g++ -std=c++0x -pthread -c src/Map.cpp

MatrixMap.o: src/MatrixMap.cpp src/MatrixMap.h
	g++ -std=c++0x -pthread -c src/MatrixMap.cpp

Node.o: src/Node.cpp src/Node.h
	g++ -std=c++0x -pthread -c src/Node.cpp

Passenger.o: src/Passenger.cpp src/Passenger.h
	g++ -std=c++0x -pthread -c src/Passenger.cpp

Point.o: src/Point.cpp src/Point.h
	g++ -std=c++0x -pthread -c src/Point.cpp

Algorithm.o: src/Algorithm.cpp src/Algorithm.h
	g++ -std=c++0x -pthread -c src/Algorithm.cpp

AbstractCab.o: src/AbstractCab.cpp src/AbstractCab.h
	g++ -std=c++0x -pthread -c src/AbstractCab.cpp

TaxiCenter.o: src/TaxiCenter.cpp src/TaxiCenter.h
	g++ -std=c++0x -pthread -c src/TaxiCenter.cpp

Trip.o: src/Trip.cpp src/Trip.h
	g++ -std=c++0x -pthread -c src/Trip.cpp

clean:
	rm -f *.o a.out

