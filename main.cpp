#include <iostream>
#include <stdio.h>
#include "src/MainFlow.h"
#include <stdexcept>
#include "src/Udp.h"
#include "src/MatrixFactory.h"
#include <unistd.h>
//#include "easylogging++.h"

//_INITIALIZE_EASYLOGGINGPP

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;

/*
 * the main class of the server
 */
int main(int argc, char *argv[]) {
    int obsNum, i;
    string matrixInput, obstacle;
    MatrixFactory factory;
    MainFlow mainFlow(&factory, atoi(argv[1]));

    getline(cin, matrixInput); //matrix size
    cin >> obsNum; //number of obstacles
    for (i = 0; i < obsNum; ++i) { //receiving obstacles
        cin >> obstacle;
        matrixInput += "|" + obstacle;
    }
    mainFlow.startFlow(matrixInput);
//    LINFO << "finish flow" << endl;
    return 0;
}
