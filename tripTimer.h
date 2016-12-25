//
// Created by tomer on 12/25/16.
//

#ifndef PROJECT_TRIPTIMER_H
#define PROJECT_TRIPTIMER_H

#include "TimeListener.h"

class tripTimer : public timeListener {
private:
    Trip *trip;
public:
    virtual void tock();
    tripTimer(Trip *t);
    ~tripTimer();
};


#endif //PROJECT_TRIPTIMER_H
