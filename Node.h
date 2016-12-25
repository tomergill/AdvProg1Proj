//
// Created by alon on 16/11/16.
//

#ifndef EX1_TIHNUT_GENERLNODE_H
#define EX1_TIHNUT_GENERLNODE_H

#include <vector>
#include "Point.h"
#include "AbstractNode.h"

using namespace std;

/**
 * this is the node of the matrix.
 * can print himself and can get his neighbours and his point.
 */
class Node : public AbstractNode {
private:
    Point p;
    vector<AbstractNode *> arr;
    bool obstacle;
protected:
    ostream &print(ostream &os) const;

public:
    Node();

    Node(Point p);

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
