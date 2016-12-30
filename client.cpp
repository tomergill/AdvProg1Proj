#include <iostream>
#include <stdio.h>
#include "src/MainFlow.h"
#include "src/Socket.h"
#include "src/Udp.h"
#include "src/Socket.h"
#include "src/Udp.h"
#include "src/Node.h"
#include <stdexcept>
#include "client.h"

MartialStatus getStatusByChar(char mstatus);

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;

// A main class.

int main(int argc, char *argv[]) {
    client *client1 = new client();
    client1->sendDriver();
    client1->setCab();
    client1->getDriver();
   // delete client1;
    return 0;
}

MartialStatus getStatusByChar(char c) {
    switch (c) {
        case 'S':
            return MartialStatus::S;
        case 'M':
            return MartialStatus::M;
        case 'W':
            return MartialStatus::W;
        case 'D':
            return MartialStatus::D;
        default:
            return MartialStatus::S;
    }
}


/**
 * @param c char representing a CarManufactorer
 * @return The CarManufactur value of c.
 */

CarManufactur getManuByChar(char c) {
    switch (c) {
        case 'S':
            return CarManufactur::S;
        case 'H':
            return CarManufactur::H;
        case 'F':
            return CarManufactur::F;
        case 'T':
            return CarManufactur::T;
        default:
            return CarManufactur::S;
    }
}


/**
 * @param c char representing a CarColor
 * @return The CarColor value of c.
 */

CarColor getColorByChar(char c) {
    switch (c) {
        case 'R':
            return CarColor::R;
        case 'B':
            return CarColor::B;
        case 'W':
            return CarColor::W;
        case 'G':
            return CarColor::G;
        default:
            return CarColor::P;
    }
}


client::client(Driver *driver, Socket *socket) : driver(driver), socket(socket) {}

client::~client() {
    delete socket;
    delete driver;
}

void client::setCab() {
    char buffer[4096];
    this->socket->reciveData(buffer, sizeof(buffer));
    char *end = buffer + 4095;
    basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
    binary_iarchive ia(s2);
    ia >> this->cab;
    this->driver->setCab(this->cab);
}

void client::sendDriver() {
    int input, driverId = 0, age = 0, experience = 0, cabId = 0, start_x = 0,
            start_y = 0, end_x = 0, end_y = 0, pass_num = 0, rideId = 0,
            taxi_type = 1, time1 = 0;
    MartialStatus status = MartialStatus::S;
    double tariff = 0.0;
    CarColor color = CarColor::R;
    CarManufactur manufactur = CarManufactur::F;
    char dummy = ',', mstatus, cColor, manu;
    //Udp udp(1, 12345);
    this->socket->initialize();
    // FactoryCab factoryCab;
    // Cab* gp2;
    //   Driver *gp = new Driver(0,30,MaritalStatus::DIVORCED,1,0, new Node(Point(0,0),NULL));
    // AbstractNode* gp = new Node(Point(0,0));
    cin >> driverId >> dummy >> age >> dummy >> mstatus >> dummy
        >> experience >> dummy >> cabId;
    status = getStatusByChar(mstatus);
    BFS *bfs = new BFS();
    AbstractNode *node = new Node(Point(0, 0));
    Driver *driver = new Driver(driverId, age, status, bfs, node);
    this->driver = driver;
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << driver;
    s.flush();
    this->socket->sendData(serial_str);
}

void client::getDriver() {
    while (true) {
        Driver *driver;
        // FactoryCab factoryCab;
        // Cab* gp2;
        char buffer[4096];
        this->socket->reciveData(buffer, sizeof(buffer));
        char *end = buffer + 4095;
        basic_array_source<char> device(buffer, end);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
        binary_iarchive ia(s2);
        ia >> driver;
        if (driver->getLocation() == NULL) {
            break;
        }
        this->driver = driver;
    }
}

client::client() {
    this->socket = new Udp(0, 12345);
    this->driver = NULL;
    this->cab = NULL;
}
