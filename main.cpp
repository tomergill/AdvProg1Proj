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
    MatrixFactory factory;
    MainFlow mainFlow(&factory, atoi(argv[1]));
    mainFlow.startFlow();
//    LINFO << "finish flow" << endl;
    return 0;
}
