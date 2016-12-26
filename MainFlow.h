//
// Created by alon on 02/12/16.
//

#ifndef TESTS_MAINFLOW_H
#define TESTS_MAINFLOW_H

#include "MapFactory.h"
#include "TaxiCenter.h"
#include <iostream>
#include "LuxuryCab.h"

/*
 * this class runs our game
 */
class MainFlow {
private:
    MapFactory *mapFactory;
    TaxiCenter *taxiCenter;
    int time;

    void flow();

    MartialStatus getStatusByChar(char c);

    CarManufactur getManuByChar(char c);

    CarColor getColorByChar(char c);

public:
    ~MainFlow();

    MainFlow(MapFactory *factory);

    void startFlow(string mapInput);
};

#endif //TESTS_MAINFLOW_H
