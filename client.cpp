#include <iostream>
#include <stdio.h>
#include "src/MainFlow.h"
#include "src/Socket.h"
#include "src/Udp.h"
#include "src/Socket.h"
#include "src/Udp.h"
#include "src/Node.h"
#include <stdexcept>


using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;
// A main class.
int main(int argc, char *argv[]) {
    Socket *udp = new Udp (0, 12345);
    //Udp udp(1, 12345);
    udp->initialize();

    char buffer[4096];
    // FactoryCab factoryCab;
    // Cab* gp2;
//    Driver *gp = new Driver(0,30,MaritalStatus::DIVORCED,1,0, new Node(Point(0,0),NULL));
    AbstractNode* gp = new Node(Point(0,0));
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    binary_oarchive oa(s);
    oa << gp;
    // cout << oa;
    s.flush();
    //string a = oa;
    //cout << serial_str << endl;

    udp->sendData(serial_str);


/*    Driver *gp2;
    basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    binary_iarchive ia(s2);
    ia >> gp2;
    // cout << oa;
    //s.flush();
    //string a = oa;
    cout << *gp2;*//*
    string serial_str;

    Node *gp2;
    basic_array_source<char> device((char*)serial_str.c_str(),(char*) serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    binary_iarchive ia(s2);
    ia >> gp2;

    cout << *gp2*/;

/*    MainFlow mainFlow;
    try {
        mainFlow.startGame();
    } catch (std::invalid_argument &err){
        cout << err.what();
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
}