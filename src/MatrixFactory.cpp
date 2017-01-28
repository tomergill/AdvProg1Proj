//
// Created by alon on 02/12/16.
//

#include <cstring>
#include <stdlib.h>
#include "MatrixFactory.h"
#include "MatrixMap.h"
#include "MainFlow.h"

/*
 * c-tor of matrix factory
 */
MatrixFactory::MatrixFactory() {

}

MatrixFactory::~MatrixFactory() {
}

/*
 * return a matrix map
 */
Map *MatrixFactory::buildMap(string s) {
    string temp = strtok(&s[0], " ,|");
    int rowNum, colNum, X, Y;
    vector<Point> *vec = new vector<Point>();
    char *x, *y;

    /*Parsing the Map's size*/
    try {
        if (!MainFlow::isStringAnInteger(&temp[0])) {
//            cout << "wrong row number" << endl;
            throw exception();
        }
        rowNum = atoi(&temp[0]);
        temp = strtok(NULL, " ,|");
        if (!MainFlow::isStringAnInteger(&temp[0])) {
//            cout << "wrong column number" << endl;
            throw exception();
        }
        colNum = atoi(&temp[0]);

//        cout << "aaa" << endl;

        if (rowNum < 1 || colNum < 1) {
//            cout << "wrong matrix sizes" << endl;
            throw exception();
        }

        /*Parsing obstacles if there are any*/
        do {
            x = strtok(NULL, " ,|");
            y = strtok(NULL, " ,|");
            if (x == NULL || y == NULL)
                break;
            if (!MainFlow::isStringAnInteger(x)
                && !MainFlow::isStringAnInteger(y)) {
//                cout << "obstacle not integer" << endl;
                throw exception();
            }
            X = atoi(x);
            Y = atoi(y);
            if (X < 0 || Y < 0 || (X == 0 && Y == 0)
                || X >= rowNum || Y >= colNum) {
//                cout << "problem with obstacle's cordinates" << endl;
                throw exception();
            }
            vec->push_back(Point(X, Y));

        } while (true);
    } catch (exception e) {
//        delete e;
        delete vec;
        return NULL;
    }

    Map *map = new MatrixMap(rowNum, colNum, vec);
    delete vec;
    return map;
}
