//
// Created by alon on 08/12/16.
//

#include "AbstractCab.h"
#include "CarManufactur.h"
#include "CarColor.h"

/*
 * c-tor of AbstractNode
 */
AbstractCab::AbstractCab(int id1, CarManufactur type1, CarColor color1) {
    this->cabId = id1;
    this->color = color1;
    this->type = type1;
}

/*
 * return ID of the cab
 */
int AbstractCab::getId() {
    return this->cabId;
}
AbstractCab::~AbstractCab() {

}
