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

class AbstractCab {
private:
    int cabId;
    double passedKm;
    CarManufactur type;
    CarColor color;
public:
    AbstractCab(){}
    
    virtual ~AbstractCab()=0;
    AbstractCab(int id1, CarManufactur type1, CarColor color1);

    virtual int getId();

    virtual AbstractNode *move(queue<AbstractNode*> *course)=0;
    
    virtual  int getKm()=0;
};

#endif //EX3_TIHNUT_ABSTRACTTEXI_H
