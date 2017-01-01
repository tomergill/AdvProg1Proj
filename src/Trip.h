//
// Created by tomer on 12/1/16.
//

#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Point.h"
#include "Driver.h"
#include "Passenger.h"
#include <boost/serialization/vector.hpp>
//#include <boost/serialization/queue.hpp>
#include <boost/serialization/deque.hpp>

/*
 * represent the trip and who is the driver and his taxo and passengers
 */
class Trip {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & rideId;
        ar & start;
        ar & end;
        //ar & map;
        ar & time;
    }

private:
    int rideId;
    int totalMPassed;
    Point *start, *end;
    int passengersNum;
    vector<Passenger *> passengersVec;
    double tarif;
    Driver *driver;
    Map *map;
    BFS *bfs;
    queue<AbstractNode *> course;
    int time;

public:
    Trip(int id, Point *start, Point *end, double tarif, Map *map,
         int startTime);

    Trip();

    ~Trip();

    void addPassenger(Passenger *p);

    void move();

    int getPassengersNum();

    int getRideId() const;

    void setRideId(int rideId);

    double getTarif();

    void setCourse();

    void moveOneStep();

    //queue<AbstractNode *> *getCourse();

    Driver *getDriver();

    void setDriver(Driver *driver);

    int getTotalMPassed();

    void setTotalMPassed(int totalMPassed);

    AbstractNode *getStart();

    AbstractNode *getEnd();

    void finish();

    int getStartTime();

    Point getEndPoint();
};


#endif //EX2_TRIP_H
