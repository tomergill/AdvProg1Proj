//
// Created by alon on 07/12/16.
//

#ifndef EX3_TIHNUT_ABSTRACTTEXI_H
#define EX3_TIHNUT_ABSTRACTTEXI_H

#include <queue>
#include "Point.h"
#include "CarManufactur.h"
#include "CarColor.h"
#include "AbstractNode.h"
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
using namespace boost::archive;
using namespace boost::serialization;

class AbstractCab {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & cabId;
        ar & passedKm;
        ar & type;
        ar & color;
    }
protected:
    int cabId;
    int passedKm;
    CarManufactur type;
    CarColor color;
public:
    AbstractCab(){}
    AbstractCab(int id1, CarManufactur type1, CarColor color1);

    virtual int getId();

    virtual AbstractNode *move(queue<AbstractNode*> *course)=0;
    
    virtual int getKm();
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractCab)
#endif //EX3_TIHNUT_ABSTRACTTEXI_H
