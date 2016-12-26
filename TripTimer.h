//
// Created by tomer on 12/25/16.
//

#ifndef PROJECT_TRIPTIMER_H
#define PROJECT_TRIPTIMER_H

#include "TimeListener.h"
#include "Trip.h"

class TripTimer : public TimeListener {
private:
    Trip *trip;
public:
    virtual void tock(int time);

    TripTimer(Trip *t);

    ~TripTimer();

    Trip *getTrip();
};


#endif //PROJECT_TRIPTIMER_H
