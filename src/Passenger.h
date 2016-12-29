//
// Created by tomer on 11/30/16.
//

#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include "Point.h"
#include "AbstractNode.h"
using namespace std;
using namespace boost::archive;
using namespace boost::serialization;
/**
 * passenger class- who use the cab
 */
class Passenger {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & source;
        ar & destination;

    }
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
