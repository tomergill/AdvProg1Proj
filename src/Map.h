//
// Created by alon on 18/11/16.
//

#ifndef EX1_TIHNUT_GRID_H
#define EX1_TIHNUT_GRID_H

#include "Node.h"

/**
 * abstract class of data structers.
 */
class Map {
public:
    virtual AbstractNode *getFirst()=0;

    virtual void newRoad()=0;

    virtual AbstractNode *getNode(int x, int y) =0;
    
    virtual ~Map()=0;

//    virtual bool operator==(const Map &node2)=0;


};

#endif //EX1_TIHNUT_GRID_H
