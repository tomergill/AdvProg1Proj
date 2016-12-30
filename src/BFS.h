//
// Created by tomer on 12/1/16.
//

#ifndef EX2_BFS_H
#define EX2_BFS_H

#include <queue>
#include "Point.h"
#include "AbstractNode.h"
#include "Map.h"
#include "Algorithm.h"

using namespace std;

class BFS : public Algorithm {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Algorithm>(*this);

    }
public:
    ~BFS();
    BFS();
    queue<AbstractNode *> smallestRoad(AbstractNode *node, AbstractNode *finish);

};


#endif //EX2_BFS_H
