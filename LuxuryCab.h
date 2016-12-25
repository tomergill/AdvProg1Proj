//
// Created by alon on 01/12/16.
//

#ifndef TESTS_LUXURYCAB_H
#define TESTS_LUXURYCAB_H


#include <queue>
#include "Point.h"
#include "CarColor.h"
#include "CarManufactur.h"
#include "Cab.h"

/*
 * like cab but move faster and more expensive
 */
class LuxuryCab : public AbstractCab {
private:
  int km;
public:
    
    LuxuryCab(int id, CarManufactur type, CarColor color);

    AbstractNode *move(queue<AbstractNode*> *course);
    
    int getKm();
    
    ~LuxuryCab();
};

#endif //TESTS_LUXURYCAB_H
