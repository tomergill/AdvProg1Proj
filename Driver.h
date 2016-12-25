//
// Created by tomer on 12/1/16.
//

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include "BFS.h"
#include "Cab.h"

enum MartialStatus {
    S, M, D, W
};

/*
 * class driver he move the cab
 */
class Driver {
private:
    int id;
    int age;
    MartialStatus mstatus;
    int totalExperience;
    int totalPassengers;
    int totalSatisfaction;
    int km;
    AbstractCab *cab;
    BFS *bfs;
    queue<AbstractNode *> *course;
    AbstractNode *location;
public:
    Driver(int id, int age, MartialStatus mstatus, BFS *bfs, AbstractNode *node);

    ~Driver();

    void changeTaxi(AbstractCab *t);

    void addSatisfaction(int totalSatisfaction, int passengers);

    void addExperience(int experience);

    int getId();

    int getExperience();

    double getSatisfaction();

    AbstractCab *getTaxi();

    void setCourse(queue<AbstractNode *> *course);

    AbstractNode *getLocation();

    queue<AbstractNode *> *getCourse();

    AbstractNode *move();

    int getKm();

};


#endif //EX2_DRIVER_H
