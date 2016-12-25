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
public:
    ~BFS();
    BFS();
    queue<AbstractNode *> smallestRoad(AbstractNode *node, AbstractNode *finish);

};


#endif //EX2_BFS_H
