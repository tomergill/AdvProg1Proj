//
// Created by alon on 17/11/16.
//

#ifndef EX1_TIHNUT_NEIGHBOURS_H
#define EX1_TIHNUT_NEIGHBOURS_H

#include <iostream>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
using namespace boost::archive;
using namespace boost::serialization;
/**
 * abstract node for every data structers.
 * we can move and do the BFS algorithm with this node.
 */
class AbstractNode {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & flag;
        ar & distance;
        ar & previousNode;

    }

private:
    AbstractNode *previousNode;
    bool flag;
    int distance;
protected:
    virtual ostream &print(ostream &os) const =0;

public:
    AbstractNode();

    virtual ~AbstractNode() = 0;

    virtual void setFlag(bool flag);

    virtual AbstractNode *getPrevious();

    virtual bool getFlag();

    virtual void setDistance(int x);

    virtual int getDistance();

    virtual void setNode(AbstractNode *neighbours1);

    virtual void addNeighbours(AbstractNode *node)=0;

    virtual bool operator==(const AbstractNode &node2)=0;

    virtual vector<AbstractNode *> getNeighbours()=0;

    friend ostream &operator<<(ostream &os, const AbstractNode &node);

    virtual bool isObstacle()=0;

    virtual void setObstacle(bool flag)=0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractNode)
#endif //EX1_TIHNUT_NEIGHBOURS_H
