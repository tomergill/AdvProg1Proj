//
// Created by alon on 01/12/16.
//
#include "LuxuryCab.h"

/*
 * c-tor of luxury cab
 */
LuxuryCab::LuxuryCab(int id1, CarManufactur type1, CarColor color1) :
        AbstractCab(id1, type1, color1) {
}

/*
 * return the next station of the cab
 */
AbstractNode *LuxuryCab::move(queue<AbstractNode *> *course) {
    AbstractNode *node;
    node = (*course).front();
    this->passedKm += 1;
    (*course).pop();
    if ((*course).front() != NULL) {
        node = (*course).front();
        this->passedKm += 1;
        (*course).pop();
    }
    if (!course->empty()) {
        return course->front();
    } else {
        return node;
    }
}

LuxuryCab::~LuxuryCab() {}

LuxuryCab::LuxuryCab() {}

BOOST_CLASS_EXPORT(LuxuryCab)