//
// Created by alon on 18/11/16.
//

#ifndef EX1_TIHNUT_MATRIX_H
#define EX1_TIHNUT_MATRIX_H

#include "Map.h"

using namespace std;
using namespace boost::archive;
using namespace boost::serialization;

/**
 * matrix that holds array of arrays.
 * can get the nodes of the array.
 */
class MatrixMap : public Map {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & boost::serialization::base_object<Map>(*this);
        ar & x;
        ar & y;
        ar & array;
    }

private:
    int x, y;
    Node array[10][10];

public:
    MatrixMap(int x1, int y1, vector<Point> *vec);

    MatrixMap();

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