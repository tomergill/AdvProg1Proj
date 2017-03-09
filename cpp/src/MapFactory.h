//
// Created by alon on 02/12/16.
//

#ifndef TESTS_MAPFACTORY_H
#define TESTS_MAPFACTORY_H

#include "Map.h"

/*
 * create map relative the input
 */
class MapFactory {
public:
    virtual Map *buildMap(string s)=0;
    
    virtual ~MapFactory()=0;
};

#endif //TESTS_MAPFACTORY_H
