//
// Created by tomer on 12/1/16.
//
#include <boost/serialization/vector.hpp>
#include <boost/serialization/deque.hpp>

#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H

#include "BFS.h"
#include "Cab.h"

enum MartialStatus {
    S, M, D, W
};

using namespace std;
using namespace boost::archive;
using namespace boost::serialization;
class Driver {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & id;
        ar & age;
        ar & mstatus;
        ar & totalExperience;
        ar & totalPassengers;
        ar & totalSatisfaction;
        ar & km;
        ar & cab;
        ar & bfs;
        ar & location;
    }
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
    AbstractNode *location;
public:
    Driver(int id, int age, MartialStatus mstatus, BFS *bfs, AbstractNode* node);

    Driver();

    ~Driver();

    void changeTaxi(AbstractCab *t);

    void addSatisfaction(int totalSatisfaction, int passengers);

    void addExperience(int experience);

    int getId();

    int getExperience();

    double getSatisfaction();

    AbstractCab *getTaxi();

    //void setCourse(queue<AbstractNode *> *course);

    AbstractNode *getLocation();

    //queue<AbstractNode *> *getCourse();

    AbstractNode *move(queue<AbstractNode *> *queue1);

    int getKm() ;
    void setLocation();
    void setCab(AbstractCab* cab);
};


#endif //EX2_DRIVER_H
