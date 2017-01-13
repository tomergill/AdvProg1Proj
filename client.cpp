#include <iostream>
#include <stdio.h>
#include "src/MainFlow.h"
#include "src/Socket.h"
#include "src/Udp.h"
#include "client.h"
#include "src/Tcp.h"
/*#include "easyloggingpp-8.91/easylogging++.h"
_INITIALIZE_EASYLOGGINGPP*/

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;

/*
 * the main class of the client
 */
int main(int argc, char *argv[]) {
    client *client1 = new client(atoi(argv[2]));
    client1->sendDriver(); // send the driver
    client1->setCab(); // set the cab to the driver
    client1->getDriverAndTrip(); // get trips and drivers
    delete client1; //delete the client
    return 0;
}

/*
 * c-tor of client
 */
client::client(Driver *driver, Socket *socket) : driver(driver), socket(socket) {}

/*
 * c-tor of client
 */
client::client() {
    this->socket = new Tcp(0, 12345);
    this->driver = NULL;
    this->cab = NULL;
}

/*
 * c-tor of client
 */
client::client(int num) {
    this->socket = new Tcp(0, num);
    this->driver = NULL;
    this->cab = NULL;
}

/*
 * destrctor of client
 */
client::~client() {
    delete this->socket;
    //  delete this->driver->getTaxi();
    delete this->driver->getLocation();
    delete this->driver->getBFS();
    delete driver;
    //  delete trip;
    //delete cab;
}

/*
 * set the cab of the driver
 */
void client::setCab() {
    char buffer[4096];
    this->socket->reciveData(buffer, sizeof(buffer), this->socket->acceptDescriptorCommunicate());
    char *end = buffer + 4095;
    basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
    binary_iarchive ia(s2);
    ia >> this->cab;
    this->driver->setCab(this->cab);
    cout << "the client got his cab" << endl;
    delete this->driver->getTaxi();
}

/*
 * send the driver we create
 */
void client::sendDriver() {
    int input, driverId = 0, age = 0, experience = 0, cabId = 0;
    MartialStatus status = MartialStatus::S;
    char dummy = ',', mstatus;
    this->socket->initialize();
    int port = this->socket->acceptDescriptorCommunicate();
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
    this->socket->sendData(serial_str, port);
    //  delete bfs;
    //  delete node;
    // delete driver;
}

/*
 * get drivers and trips
 */
void client::getDriverAndTrip() {
    //  AbstractNode *node = NULL;
    while (true) {
/*        if (this->trip == NULL) { // we get new trip
            if (driver->getLocation() == NULL) {
                break;
            }
            int num = this->getMesseage();
            if (num == 9) {
                char buffer[4096];
                this->socket->reciveData(buffer, sizeof(buffer));
                char *end = buffer + 4095;
                basic_array_source<char> device(buffer, end);
                boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
                binary_iarchive ia(s2);
                ia >> this->trip;
                node = new Node(this->trip->getEndPoint());
            }
        } else if (this->driver->getLocation()->operator==(*node)) { // we finish the trip
            int num = this->getMesseage();
            if (num == 9) { // we need to get one more trip
                this->trip = NULL;
            }
            if (num == 7) { // we need to finish the program
                break;
            }
        } else {*/ // finish the program
        Driver *driver;
        char buffer[4096];
        this->socket->reciveData(buffer, sizeof(buffer), this->socket->acceptDescriptorCommunicate());
        char *end = buffer + 4095;
        basic_array_source<char> device(buffer, end);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
        binary_iarchive ia(s2);
        ia >> driver;
        cout << "the client got his current point" << endl;
        if (driver->getLocation() == NULL) {
            cout << "close client" << endl;
            cout << "client number:" << this->driver->getId() << endl;
            delete driver->getLocation();
            delete driver->getBFS();
            delete driver;
            break;
        }
        // delete this->driver->getTaxi();
        delete this->driver->getLocation();
        delete this->driver->getBFS();
        delete this->driver;
        this->driver = driver;
    }
    /*  }
      if (node != NULL) {
          delete node;
      }*/
}

/*
 * get message 7 or 9 to know if we finish the program
 */
int client::getMesseage() {
    int num = 0;
    /*  char buffer[4096];
      this->socket->reciveData(buffer, sizeof(buffer));
      char *end = buffer + 4095;
      basic_array_source<char> device(buffer, end);
      boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
      binary_iarchive ia(s2);
      ia >> num;*/
    return num;
}

/**
 * @param c char representing a MartialStatus
 * @return Martial status based on c.
 */
MartialStatus client::getStatusByChar(char c) {
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
