//
// Created by tomer on 12/1/16.
//

#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H


#include "Driver.h"
#include "Trip.h"
#include "Map.h"
#include "BFS.h"
#include "TimeListener.h"
#include "TripTimer.h"
#include <list>
#include <iostream>
#include <thread_db.h>
#include "ThreadPool.h"

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
    list<TimeListener *> timers;
    thread_t thread;
    ThreadPool *threadpool;

    void deletetriplistener(int tripId);

public:
    Driver *findClosestDriverToPoint(AbstractNode *p);

    void answerCall(int id, Point *start, Point *end, double tarif, int pass,
                    int startTime);

    void addDriver(int id, int age, MartialStatus mstatus);

    void addDriver(Driver *d);

    void waitForThread();

    void addTaxi(AbstractCab *t);

    AbstractNode *getFirst();

    void timePassed(int time);

    TaxiCenter(Map *m);

    void pushDriver(Driver *driver);

    void printDriverLocation(Driver *driver);

    void printDriverLocation(int id);

    void printAllDriversLoactions();

    int getNumberOfDrivers();

    int getNumberOfCabs();

    int getNumberOfTrips();

    void createTread(Trip *trip);

    void assignCabToDriver(int cabId, int driverId);

    Driver *getDriver(int id);

    AbstractCab *getCab(int id);

    Trip *getTrip(int id);

    ~TaxiCenter();

    list<Driver *> getDrivers();

    BFS *getBFS();

    list<Trip *> getTrips();

    void assignADriverToTrip(int tripId);

    void assignADriverToTrip(Trip *t);

    AbstractNode *getNode(int x, int y);

    Map* getMap();

    bool isFreeCabId(int id);

    bool isFreeTripId(int id);

    void deleteFirstDriver();

    void addTrip(Trip *d);

//    static void *setCourse(void *course);
//
//    void addingJob(TaxiCenter* trip);

    void addingJob(Trip* trip);

    void setDrivers(const list<Driver *> &drivers);

    const list<AbstractCab *> &getCabs() const;

    void setCabs(const list<AbstractCab *> &cabs);

    void setTrips(const list<Trip *> &trips);

    Map *getMap() const;

    void setMap(Map *map);

    BFS *getBfs() const;

    void setBfs(BFS *bfs);

    const list<TimeListener *> &getTimers() const;

    void setTimers(const list<TimeListener *> &timers);

    thread_t getThread() const;

    void setThread(thread_t thread);

    ThreadPool *getThreadpool() const;

    void setThreadpool(ThreadPool *threadpool);

    void deleteTrip(int id);

//    void setNumberOfTrips(int numberOfTrips);
//
//    Trip *getCurrentTrip() const;
//
//    void setCurrentTrip(Trip *currentTrip);
};


#endif //EX2_TAXICENTER_H