//
// Created by alon on 07/12/16.
//

#ifndef EX3_TIHNUT_ALGORITHM_H
#define EX3_TIHNUT_ALGORITHM_H

#include <queue>
#include "AbstractNode.h"

class Algorithm {
public:
virtual ~Algorithm()=0;
    virtual queue<AbstractNode *> smallestRoad(AbstractNode *node, AbstractNode *finish)=0;

};

#endif //EX3_TIHNUT_ALGORITHM_H
