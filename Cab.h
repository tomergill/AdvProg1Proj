//
// Created by alon on 01/12/16.
//

#ifndef TESTS_CAB_H
#define TESTS_CAB_H


#include <queue>
#include "CarManufactur.h"
#include "CarColor.h"
#include "Point.h"
#include "AbstractNode.h"
#include "AbstractCab.h"

/*
 * Cab class with him we can to move like node in the Map
 */
class Cab : public AbstractCab {
private:
int km;

public:
    Cab(int id, CarManufactur type, CarColor color);

    AbstractNode *move(queue<AbstractNode *> *course);
    
       int getKm();
       ~Cab();
};

#endif //TESTS_CAB_H
