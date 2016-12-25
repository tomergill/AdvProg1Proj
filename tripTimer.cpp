//
// Created by tomer on 12/25/16.
//

#include "tripTimer.h"

/**
 * Constructor.
 * @param t Pointer to a Trip to be moved in the "tock" function.
 */
tripTimer::tripTimer(Trip *t) {
    trip = t;
}

/**
 * Destructor.
 */
tripTimer::~timeListener() {}

/**
 * Called when time has passed, and moves the trip one step.
 */
void tripTimer::tock() {
    trip->moveOneStep();
}