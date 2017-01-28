//
// Created by alon on 18/11/16.
//

#ifndef EX1_TIHNUT_GRID_H
#define EX1_TIHNUT_GRID_H
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include "Node.h"

/**
 * abstract class of data structers.
 */
class Map {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
    }

public:
    Map();

    virtual AbstractNode *getFirst()=0;

    virtual void newRoad()=0;

    virtual AbstractNode *getNode(int x, int y) =0;
    virtual AbstractNode *getNode(AbstractNode* node) =0;
    virtual ~Map() = 0;

//    virtual bool operator==(const Map &node2)=0;


};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Map)
#endif //EX1_TIHNUT_GRID_H
