//
// Created by alon on 01/12/16.
//

#ifndef TESTS_LUXURYCAB_H
#define TESTS_LUXURYCAB_H


#include <queue>
#include "Point.h"
#include "AbstractCab.h"

/*
 * like cab but move faster and more expensive
 */
class LuxuryCab : public AbstractCab {
private:
public:
    
    LuxuryCab(int id, CarManufactur type, CarColor color);

    AbstractNode *move(queue<AbstractNode*> *course);
    
    ~LuxuryCab();
};

#endif //TESTS_LUXURYCAB_H
