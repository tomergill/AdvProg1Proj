//
// Created by tomer on 12/25/16.
//

#ifndef PROJECT_TIME_LISTENER_H
#define PROJECT_TIME_LISTENER_H

/**
 * Class implementing the listener/observer design pattern, specifiecly about
 * time handling.
 */
class timeListener {
public:
    virtual void tock() = 0;
};


#endif //PROJECT_TIME_LISTENER_H
