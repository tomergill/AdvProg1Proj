//
// Created by alon on 18/11/16.
//

#include "MatrixMap.h"

/**
 * c-tor of matrix.
 * @param x1.
 * @param y1.
 * @param limit1.
 * @return.
 */
MatrixMap::MatrixMap(int x1, int y1, vector<Point> *vec) {
    x = x1;
    y = y1;
    // create the matrix of the matrix class.
    for (int i = 0; i < x1; i++) {
        for (int j = 0; j < y1; j++) {
            array[i][j] = Node(Point(i, j));
            array[i][j].setDistance(-1);
            array[i][j].setFlag(false);
            array[i][j].setObstacle(false);
        }
    }
    //add the neighbours for every node.
    for (int i = 0; i < x1; i++) {
        for (int j = 0; j < y1; j++) {
            Node node = array[i][j];
            // if left neighbour.
            if (leftNeighbour(array[i][j].getPoint())) {
                array[i][j].addNeighbours(getNode(node.getPoint().getX() - 1, node.getPoint().getY()));
            } else {
                array[i][j].addNeighbours(NULL);
            }
            // if up neighbour.
            if (upNeighbour(array[i][j].getPoint())) {
                array[i][j].addNeighbours(getNode(node.getPoint().getX(), node.getPoint().getY() + 1));
            } else {
                array[i][j].addNeighbours(NULL);
            }
            // if right neighbour.
            if (rightNeighbour(array[i][j].getPoint())) {
                array[i][j].addNeighbours(getNode(node.getPoint().getX() + 1, node.getPoint().getY()));
            } else {
                array[i][j].addNeighbours(NULL);
            }
            // if down neighbour.
            if (downNeighbour(array[i][j].getPoint())) {
                array[i][j].addNeighbours(getNode(node.getPoint().getX(), node.getPoint().getY() - 1));
            } else {
                array[i][j].addNeighbours(NULL);
            }
        }
    }

    /*sets the obstacles' flags*/
    if(!vec->empty()){
    vector<Point>::iterator it = vec->begin();
    for (it; it != vec->end(); it++)
    {
        array[it->getX()][it->getY()].setObstacle(true);
    }
}}

MatrixMap::MatrixMap() {}

/**
 * check if the node have a left neighbour.
 * @param p.
 * @return true or false.
 */
bool MatrixMap::leftNeighbour(Point p) {
    return (p.getX() > 0);
}

/**
 * check if the node have a right neighbour.
 * @param p.
 * @return true or false.
 */
bool MatrixMap::rightNeighbour(Point p) {
    return (p.getX() < x - 1);
}

/**
 * check if the node have a up neighbour.
 * @param p.
 * @return true or false.
 */
bool MatrixMap::upNeighbour(Point p) {
    return (p.getY() < y - 1);
}

/**
 * check if the node have a down neighbour.
 * @param p.
 * @return true or false.
 */
bool MatrixMap::downNeighbour(Point p) {
    return (p.getY() > 0);
}

/**
 * get the first node of the matrix.
 * @return the node.
 */
AbstractNode *MatrixMap::getFirst() {
    return &(array[0][0]);
}

/**
 * return the node in this index.
 * @param x.
 * @param y.
 * @return node.
 */
AbstractNode *MatrixMap::getNode(int x, int y) {
    return &(array[x][y]);
}

/*
 * return a node
 */
AbstractNode *MatrixMap::getNode(Point p) {
    return getNode(p.getX(), p.getY());
}

///**
//* function that checks of 2 matrix are equal.
//* @param node2.
//* @return true or false.
//*/
//bool MatrixMap::operator==(const Map &matrix2) {
//    int i, j;
//
//    if (x != ((MatrixMap &)matrix2).x || y != ((MatrixMap &)matrix2).y)
//        return false;
//    for (i = 0; i < x; i++)
//        for (j = i; j < y; j++)
//            if (array[i][j].getFlag() != matrix2.getNode(i, j)->getFlag())
//                return false;
//    return true;
//}

void MatrixMap::newRoad() {
    for (int i = 0; i < this->x; i++) {
        for (int j = 0; j < this->y; j++) {
            array[i][j].setDistance(-1);
            array[i][j].setFlag(false);
        }
    }
}

MatrixMap::~MatrixMap(){}

BOOST_CLASS_EXPORT(MatrixMap)
