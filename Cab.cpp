//
// Created by alon on 01/12/16.
//

#include "Cab.h"

using namespace std;

/**
 * c-tor of cab.
 */
Cab::Cab(int id1, CarManufactur type1, CarColor color1) :
        AbstractCab(id1, type1, color1) {
}

/*
 * return the next point of the cab.
 */
AbstractNode *Cab::move(queue<AbstractNode *> *course) {
    AbstractNode *node;
    node = (*course).front();
    this->passedKm+=1;
    course->pop();
    return node;
}