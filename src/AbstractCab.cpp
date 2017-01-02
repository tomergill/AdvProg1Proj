//
// Created by alon on 08/12/16.
//

#include "AbstractCab.h"

/*
 * c-tor of AbstractNode
 */
AbstractCab::AbstractCab(int id1, CarManufactur type1, CarColor color1) {
    this->cabId = id1;
    this->color = color1;
    this->type = type1;
    this->passedKm = 0;
}

/**
 * Destructor.
 */
AbstractCab::~AbstractCab() {

}

/*
 * return ID of the cab
 */
int AbstractCab::getId() {
    return this->cabId;
}

/**
 * @return how much km has passed
 */
int AbstractCab::getKm() {
    return passedKm;
}

