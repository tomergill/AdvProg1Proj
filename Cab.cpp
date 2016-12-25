//
// Created by alon on 01/12/16.
//

#include "Cab.h"
#include "AbstractNode.h"

using namespace std;

/**
 * c-tor of cab.
 */
Cab::Cab(int id1, CarManufactur type1, CarColor color1) :
        AbstractCab(id1, type1, color1) {
        this->km=0;

}

/*
 * return the next point of the cab.
 */
AbstractNode *Cab::move(queue<AbstractNode *> *course) {
    AbstractNode *node;
    node = (*course).front();
    this->km+=1;
    course->pop();
    return node;
}

/*
* return km passed
*/
int Cab::getKm(){
return this->km;
}

Cab::~Cab(){}
