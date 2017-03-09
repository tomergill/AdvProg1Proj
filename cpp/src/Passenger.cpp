//
// Created by tomer on 11/30/16.
//

#include <stdlib.h>
#include "Passenger.h"

/**
 * c-tor of passenger
 */
Passenger::Passenger(AbstractNode *src, AbstractNode *dest) {
    this->source = src;
    this->destination = dest;
}

/**
 * return a rank about the driver
 * */
int Passenger::getRating() {
    return rand() % 5 + 1;
}

/**
 * return the end point of the passenger
 */
AbstractNode *Passenger::getDestination() {
    return this->destination;
}

/**
 * return the start point of the passenger
 */
AbstractNode *Passenger::getSource() {
    return this->source;
}

Passenger::Passenger() {}

