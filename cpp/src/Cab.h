//
// Created by alon on 01/12/16.
//

#ifndef TESTS_CAB_H
#define TESTS_CAB_H


#include <queue>
#include "CarManufactur.h"
#include "CarColor.h"
#include "Point.h"
#include "AbstractNode.h"
#include "AbstractCab.h"


using namespace std;
using namespace boost::archive;
using namespace boost::serialization;

/*
 * Cab class with him we can to move like node in the Map
 */
class Cab : public AbstractCab {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<AbstractCab>(*this);
        ar & cabId;
        ar & type;
        ar & color;
    }

private:

public:
    Cab();

    Cab(int id, CarManufactur type, CarColor color);

    AbstractNode *move(queue<AbstractNode *> *course);

    ~Cab();
};

#endif //TESTS_CAB_H
