//
// Created by alon on 30/12/16.
//

#ifndef EX3_CLIENT_H
#define EX3_CLIENT_H

#include "src/Driver.h"
#include "src/Socket.h"

class client {
public:
    client(Driver *driver, Socket *socket, Trip* trip);

    client();

    void setCab();
    void sendDriver();
    void getDriver();
    virtual ~client();

private:
    Driver *driver;
    Socket *socket;
    AbstractCab* cab;
    Trip* trip;
};
#endif //EX3_CLIENT_H