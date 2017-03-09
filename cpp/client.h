//
// Created by alon on 30/12/16.
//

#ifndef EX3_CLIENT_H
#define EX3_CLIENT_H

#include "src/Driver.h"
#include "src/Socket.h"

class client {
public:
    client(Driver *driver, Socket *socket);

    client();

    client(int port);

    void setCab();

    int sendDriver();

    void getDriverAndTrip();

    virtual ~client();

    int getMesseage();


private:
    Driver *driver;
    Socket *socket;
    AbstractCab *cab;

    MartialStatus getStatusByChar(char c);
};

#endif //EX3_CLIENT_H
