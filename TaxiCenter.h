//
// Created by tomer on 12/1/16.
//

#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H


#include "Driver.h"
#include "Trip.h"
#include "Map.h"
#include "BFS.h"
#include <list>
#include <iostream>

using namespace std;

/**
 * Class representing a taxi center, which holds information about all the
 * drivers, cabs, current trips and  a map of the city.
 */
class TaxiCenter {
private:
    list<Driver *> drivers;
    list<AbstractCab *> cabs;
    list<Trip *> trips;
    Map *map;
    BFS *bfs;

    Driver *findClosestDriverToPoint(AbstractNode *p);

public:
    void answerCall(int id, Point *start, Point *end, double tarif, int pass);

    void addDriver(int id, int age, MartialStatus mstatus);

    void addTaxi(AbstractCab *t);

    void moveAllTrips();

    TaxiCenter(Map *m);

    void printDriverLocation(Driver *driver);

    void printDriverLocation(int id);

    void printAllDriversLoactions();

    int getNumberOfDrivers();

    int getNumberOfCabs();

    int getNumberOfTrips();

    void assignCabToDriver(int cabId, int driverId);

    Driver *getDriver(int id);

    AbstractCab *getCab(int id);

    Trip *getTrip(int id);

    ~TaxiCenter();
};


#endif //EX2_TAXICENTER_H