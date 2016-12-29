//
// Created by alon on 16/11/16.
//

#ifndef EX1_TIHNUT_GENERLNODE_H
#define EX1_TIHNUT_GENERLNODE_H

#include <vector>
#include "Point.h"
#include "AbstractNode.h"
#include <boost/serialization/vector.hpp>
#include <boost/serialization/queue.hpp>

using namespace std;
using namespace std;
using namespace boost::archive;
using namespace boost::serialization;
/**
 * this is the node of the matrix.
 * can print himself and can get his neighbours and his point.
 */
class Node : public AbstractNode {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & p;
        ar & arr;
        ar & obstacle;
        ar & boost::serialization::base_object<AbstractNode>(*this);

    }
private:
    Point p;
    vector<AbstractNode *> arr;
    bool obstacle;
protected:
    ostream &print(ostream &os) const;

public:

    Node(Point p);

    Node();

    Point getPoint();

    vector<AbstractNode *> getNeighbours();

    void addNeighbours(AbstractNode *node);

    bool operator==(const AbstractNode &node2);

    friend ostream &operator<<(ostream &os, const AbstractNode &node);

    bool isObstacle();

    void setObstacle(bool flag);
    
    ~Node();

};

#endif //EX1_TIHNUT_GENERLNODE_H
