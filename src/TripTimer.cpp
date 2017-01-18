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
void TripTimer::tock(int time) {
    if (this->trip->getDriver() != NULL) {
        this->trip->getDriver()->setClientGotPoint(true);
    }
    if (time > trip->getStartTime()) {
        cout << "move trip " << trip->getRideId() << endl;
        trip->moveOneStep();
    }
}

/**
 * @return The Trip pointer.
 */
Trip *TripTimer::getTrip() {
    return trip;
}

int TripTimer::getStartTime() {
    return trip->getStartTime();
}