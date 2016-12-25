//
// Created by alon on 01/12/16.
//

#include "LuxuryCab.h"

/*
 * c-tor of luxury cab
 */
LuxuryCab::LuxuryCab(int id1, CarManufactur type1, CarColor color1) :
        AbstractCab(id1, type1, color1) {
        this->km=0;
}

/*
 * return the next station of the cab
 */
AbstractNode *LuxuryCab::move(queue<AbstractNode *> *course) {
    AbstractNode *node;
    node = (*course).front();
    this->km+=1;
    (*course).pop();
    if ((*course).front() != NULL) {
        node = (*course).front();
        this->km+=1;
        (*course).pop();
    } 
    return node;
}
/*
* return km passed
*/
int LuxuryCab::getKm(){
  return this->km;
}

LuxuryCab::~LuxuryCab(){}