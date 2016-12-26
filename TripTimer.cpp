//
// Created by tomer on 12/25/16.
//

#include "TripTimer.h"

/**
 * Constructor.
 * @param t Pointer to a Trip to be moved in the "tock" function.
 */
TripTimer::TripTimer(Trip *t) {
    trip = t;
}

/**
 * Destructor.
 */
TripTimer::~TripTimer() {}

/**
 * Called when time has passed, and moves the trip one step.
 */
void TripTimer::tock() {
    trip->moveOneStep();
}

/**
 * @return The Trip pointer.
 */
Trip * TripTimer::getTrip()
{
    return trip;
}