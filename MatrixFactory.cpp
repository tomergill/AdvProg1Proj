//
// Created by alon on 02/12/16.
//

#include <cstring>
#include <stdlib.h>
#include "MatrixFactory.h"
#include "MatrixMap.h"

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
    int rowNum, colNum;
    vector <Point> *vec = new vector<Point>();
    char *x, *y;

    /*Parsing the Map's size*/
    rowNum = atoi(&temp[0]);
    temp = strtok(NULL, " ,|");
    colNum = atoi(&temp[0]);

    /*Parsing obstacles if there are any*/
    do {
        x = strtok(NULL, " ,|");
        y = strtok(NULL, " ,|");
        if (x == NULL || y == NULL)
            break;
        vec->push_back(Point(atoi(x), atoi(y)));

    } while (true);

    Map *map = new MatrixMap(rowNum, colNum, vec);
    delete vec;
    return map;
}
