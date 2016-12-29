//
// Created by alon on 01/12/16.
//

#ifndef TESTS_LUXURYCAB_H
#define TESTS_LUXURYCAB_H
using namespace std;


#include "CarManufactur.h"
#include "CarColor.h"
#include "Point.h"
#include "AbstractNode.h"
#include "AbstractCab.h"

/*
 * like cab but move faster and more expensive
 */
class LuxuryCab : public AbstractCab {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<AbstractCab>(*this);

    }

public:
    
    LuxuryCab(int id, CarManufactur type, CarColor color);

    AbstractNode *move(queue<AbstractNode*> *course);
    
    ~LuxuryCab();
};

#endif //TESTS_LUXURYCAB_H
