///*
////
//// Created by tomer on 12/3/16.
////
//
//#include <gtest/gtest.h>
//#include "../src/Trip.h"
//#include "../src/MatrixMap.h"
//#include "../src/LuxuryCab.h"
//
//TEST(test_trip, GetPassengersNum) {
//    Point p(1, 1);
//     vector<Point> *vec=new vector<Point>();
//    MatrixMap* m=new MatrixMap(1, 1, vec);
//    BFS *bfs = new BFS();
//    Driver d(0, 2, MartialStatus::S, bfs,m->getFirst());
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node1 = new Node(p1);
//    AbstractNode *node2 = new Node(p2);
//    Trip trip(0, p1, p2, 1.0, m);
//    Passenger* passenger=new Passenger(node1, node2);
//    trip.addPassenger(passenger);
//    EXPECT_EQ(1, trip.getPassengersNum());
//    delete vec;
//    delete bfs;
//    delete node1;
//    delete node2;
//    delete m;
//
//}
//
//TEST(test_trip, AddPassenger) {
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node1 = new Node(p1);
//    AbstractNode *node2 = new Node(p2);
//    Passenger *passenger=new Passenger(node1, node2);
//    Point p(1, 1);
//         vector<Point> *vec=new vector<Point>();
//    MatrixMap m(1, 1, vec);
//    BFS *bfs = new BFS();
//    Driver d(0, 2, MartialStatus::S, bfs,m.getFirst());
//    Trip trip(0, p1, p2, 1.0, &m);
//
//    trip.addPassenger(passenger);
//    EXPECT_EQ(1, trip.getPassengersNum());
//    delete bfs;
//    delete vec;
//    delete node1;
//    delete node2;
//}
//
//
//TEST(test_trip, MoveTripAndGetLocation) {
//    vector<Point> *vec=new vector<Point>();
//    MatrixMap *map = new MatrixMap(10, 10, vec);
//    BFS *bfs = new BFS();
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node2 = new Node(p2);
//    Cab cab(1234, CarManufactur::F, CarColor::B);
//    Driver d(0, 2, MartialStatus::S, bfs,map->getFirst());
//    d.changeTaxi(&cab);
//    Trip trip(0, p1, p2, 1.0, map);
//    trip.setCourse();
//    trip.setDriver(&d);
//     trip.move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node2));
//    EXPECT_TRUE(trip.getTotalMPassed() == 3);
//    delete bfs;
//    delete node2;
//    delete map;
//    delete vec;
//}
//
//TEST(test_trip, MoveDriverAndGetLocationAndKm) {
//    Point p(0, 1);
//         vector<Point> *vec=new vector<Point>();
//    MatrixMap *map = new MatrixMap(10, 10, vec);
//    BFS *bfs = new BFS();
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node = new Node(p);
//    AbstractNode *node1 = new Node(p1);
//    AbstractNode *node2 = new Node(p2);
//    Cab cab(1234, CarManufactur::F, CarColor::B);
//    Driver d(0, 2, MartialStatus::S, bfs,map->getFirst());
//    d.changeTaxi(&cab);
//    Trip trip(0, p1, p2, 1.0, map);
//    trip.setCourse();
//    trip.setDriver(&d);
//    trip.getDriver()->move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node1));
//    trip.getDriver()->move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node));
//    trip.getDriver()->move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node2));
//    EXPECT_TRUE(trip.getDriver()->getKm() == 3);
//    delete vec;
//    delete node;
//    delete node1;
//    delete node2;
//    delete bfs;
//    delete map;
//}
//
//TEST(test_trip,  MoveDriverAndGetLocationAndKmLuxury){
//    Point p(0, 1);
//    vector<Point> *vec=new vector<Point>();
//    MatrixMap *map = new MatrixMap(10, 10, vec);
//    BFS *bfs = new BFS();
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node = new Node(p);
//    AbstractNode *node1 = new Node(p1);
//    AbstractNode *node2 = new Node(p2);
//    LuxuryCab cab(1234, CarManufactur::F, CarColor::B);
//    Driver d(0, 2, MartialStatus::S, bfs,map->getFirst());
//    d.changeTaxi(&cab);
//    Trip trip(0, p1, p2, 1.0, map);
//    trip.setCourse();
//    trip.setDriver(&d);
//    trip.getDriver()->move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node));
//    trip.getDriver()->move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node2));
//    EXPECT_TRUE(trip.getDriver()->getKm() == 3);
//    delete bfs;
//    delete node1;
//    delete node2;
//    delete node;
//    delete map;
//    delete vec;
//}
//TEST(test_trip, MoveTripAndGetLocationLuxury) {
//    Point p(0, 1);
//    vector<Point> *vec=new vector<Point>();
//    MatrixMap *map = new MatrixMap(10, 10, vec);
//    BFS *bfs = new BFS();
//    Point *p1=new Point(0, 0), *p2=new Point(1, 1);
//    AbstractNode *node = new Node(p);
//    AbstractNode *node1 = new Node(p1);
//    AbstractNode *node2 = new Node(p2);
//    LuxuryCab cab(1234, CarManufactur::F, CarColor::B);
//    Driver d(0, 2, MartialStatus::S, bfs,map->getFirst());
//    d.changeTaxi(&cab);
//    Trip trip(0, p1, p2, 1.0, map);
//    trip.setCourse();
//    trip.setDriver(&d);
//    trip.move();
//    EXPECT_TRUE(trip.getDriver()->getLocation()->operator==(*node2));
//    EXPECT_TRUE(trip.getTotalMPassed() == 3);
//    delete bfs;
//    delete node1;
//    delete node2;
//    delete node;
//    delete map;
//    delete vec;
//}
//
//*/
