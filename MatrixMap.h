//
// Created by alon on 18/11/16.
//

#ifndef EX1_TIHNUT_MATRIX_H
#define EX1_TIHNUT_MATRIX_H

#include "Map.h"

/**
 * matrix that holds array of arrays.
 * can get the nodes of the array.
 */
class MatrixMap : public Map {
private:
    int x, y;
    Node array[10][10];

public:
    MatrixMap(int x1, int y1, vector<Point> *vec);

    AbstractNode *getFirst();

    AbstractNode *getNode(int x, int y);

    AbstractNode *getNode(Point p);

    void newRoad();

    bool leftNeighbour(Point p);

    bool rightNeighbour(Point p);

    bool upNeighbour(Point p);

    bool downNeighbour(Point p);
    
    ~MatrixMap();

//    bool operator==(const Map &matrix2);

};

#endif //EX1_TIHNUT_MATRIX_H