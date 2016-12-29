//
// Created by alon on 02/12/16.
//

#ifndef TESTS_MATRIXFACTORY_H
#define TESTS_MATRIXFACTORY_H


#include "MapFactory.h"

/*
 * creates matrix with the correct input
 */
class MatrixFactory : public MapFactory {
public:
    MatrixFactory();
    ~MatrixFactory();
    Map *buildMap(string s);
};

#endif //TESTS_MATRIXFACTORY_H
