//
// Created by tomer on 12/25/16.
//

#ifndef PROJECT_TRIPTIMER_H
#define PROJECT_TRIPTIMER_H

#include "TimeListener.h"
#include "Trip.h"

/**
 * Class that moves a trip when time has passed.
 */
class TripTimer : public TimeListener {
private:
    Trip *trip;
public:
    virtual void tock(int time);

    TripTimer(Trip *t);

    ~TripTimer();

    Trip *getTrip();

    int getStartTime();
};


#endif //PROJECT_TRIPTIMER_H
