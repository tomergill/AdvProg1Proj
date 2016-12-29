#include <iostream>
#include <stdio.h>
#include "src/MainFlow.h"
#include <stdexcept>
#include "src/Udp.h"
#include <unistd.h>

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;
// A main class.
int main(int argc, char *argv[]) {


    std::cout << "Hello, from server" << std::endl;

    Socket *udp = new Udp(1, 12345);
    //Udp udp(1, 12345);
    udp->initialize();

    char buffer[4096];
    AbstractNode *gp2;
    // FactoryCab factoryCab;
    // Cab* gp2;
    udp->reciveData(buffer, sizeof(buffer));
    char *end = buffer + 4095;
    basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    binary_iarchive ia(s2);
    ia >> gp2;
    // cout << oa;
    //s.flush();
    //string a = oa;
    //int x = gp2->getPoint().getX();
    //cout << x;
    cout << *gp2;
    //cout << buffer << endl;
    udp->sendData("sup?");

    // support more than one client?
    return 0;
}
//    Grid *map = new Matrix(5,5);
//    Driver *gp = new Driver(0,30,MaritalStatus::DIVORCED,1,0, map->getSourceElement(0, 0));
//
//    //AbstractNode *gp =  map->getSourceElement(0, 0);
//    string serial_str;
//    back_insert_device<std::string> inserter(serial_str);
//    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
//    binary_oarchive oa(s);
//    oa << gp;
//   // cout << oa;
//    s.flush();
//    //string a = oa;
//    cout << serial_str << endl;
//
//    Driver *gp2;
//    basic_array_source<char> device(serial_str.c_str(), serial_str.size());
//    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
//    binary_iarchive ia(s2);
//    ia >> gp2;
//    // cout << oa;
//    //s.flush();
//    //string a = oa;
//    int x = gp2->getId();
//    cout << x;
//    // cout << *gp2;


//    MainFlow mainFlow;
//    try {
//        mainFlow.startGame();
//    } catch (std::invalid_argument &err){
//        cout << err.what();
//    }
//
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();

//// original main
/*
int main() {
    int obsNum, i;
    string matrixInput, obstacle;
    MatrixFactory factory;
    MainFlow mainFlow(&factory);

    getline(cin, matrixInput); //matrix size
    cin >> obsNum; //number of obstacles
    for (i = 0; i < obsNum; ++i) { //receiving obstacles
        cin >> obstacle;
        matrixInput += "|" + obstacle;
    }
    mainFlow.startFlow(matrixInput);
    return 0;
}*/
