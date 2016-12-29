//
// Created by tomer on 12/25/16.
//

#ifndef PROJECT_TIME_LISTENER_H
#define PROJECT_TIME_LISTENER_H

/**
 * Class implementing the listener/observer design pattern, specifiecly about
 * time handling.
 */
class TimeListener {
public:
    /**
     * Function that indicates that time has passed.
     */
    virtual void tock(int time) = 0;

    virtual ~TimeListener();
};


#endif //PROJECT_TIME_LISTENER_H
