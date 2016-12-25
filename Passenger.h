//
// Created by tomer on 11/30/16.
//

#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include "Point.h"
#include "AbstractNode.h"

/**
 * passenger class- who use the cab
 */
class Passenger {
private:
    AbstractNode *source;
    AbstractNode *destination;
public:
    int getRating();

    AbstractNode *getSource();

    AbstractNode *getDestination();

    Passenger(AbstractNode *src, AbstractNode *dest);

};


#endif //EX2_PASSENGER_H
