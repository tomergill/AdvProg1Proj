#include <iostream>
#include "MainFlow.h"
#include "MatrixFactory.h"

using namespace std;

/**
 * Main function.
 * @return Exit status.
 */
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
}