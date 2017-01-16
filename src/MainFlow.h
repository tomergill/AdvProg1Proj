//
// Created by alon on 02/12/16.
//

#ifndef TESTS_MAINFLOW_H
#define TESTS_MAINFLOW_H

#include "MapFactory.h"
#include "TaxiCenter.h"
#include <iostream>
#include "LuxuryCab.h"
#include "Socket.h"

/*
 * this class runs our game
 */
class MainFlow {

private:
    MapFactory *mapFactory;
    TaxiCenter *taxiCenter;
    int time;
    Socket *socket;
    Trip *trip;
    Driver *driver;
    bool finishCalculate;
    int numberOfCase;

    void flow();

    MartialStatus getStatusByChar(char c);

    CarManufactur getManuByChar(char c);

    CarColor getColorByChar(char c);

public:
    ~MainFlow();

    MainFlow(MapFactory *factory);

    MainFlow(MapFactory *factory, int num);

    void startFlow(string mapInput);

    void addDriver(int num);

    void sendTrip(Trip *trip, int descriptor);

    void sendDriver(Driver *driver, int descriptor);

    void sendCab(AbstractCab *cab, int descriptor);

    void sendMessage(int num, int descriptor);

    static void *handelThread(void *mainFlow);

/*    void checkAllClientsGotPoint();

    void setAllClientsDidntGotPoint();*/
};

#endif //TESTS_MAINFLOW_H
