/*
//
// Created by alon on 02/12/16.
//

#include <gtest/gtest.h>
#include "../src/Map.h"
#include "../src/MatrixMap.h"

*/
/*
 * class that checks matrix functions
 *//*

class MatrixTest : public ::testing::Test {
protected:
    MatrixMap *matrix;
    Node array[10][10];
    Point limit;
    int x;
    int y;
    Point right;
    Point *p;
    Node node;
    Point *first;
    Point f;
    Node *node2;
    AbstractNode *rightNode;
    Node First;
    vector<Point> *vec;

*/
/*
 * give the first values before every test
 *//*

    virtual void SetUp() {
        x = 5;
        y = 5;
        right = Point(2, 1);
        limit = Point(3, 3);
        p = new Point(1, 1);
        f = Point(0, 0);
        first = &f;
         vec=new vector<Point>();
        matrix = new MatrixMap(4, 4, vec);
        node = Node(Point(1, 1));
        node2 = &node;
        rightNode = matrix->getNode(right.getX(), right.getY());
        First = Node(first);
    }

*/
/*
 * delete the values after every test
 *//*

    virtual void TearDown() {
        delete p;
        delete matrix;
        delete vec;
 }
};

*/
/*
 * check rightNeighbour function
 *//*

TEST_F(MatrixTest, rightNeighbour) {
    ASSERT_TRUE(matrix->rightNeighbour(Point(1, 1)));
    EXPECT_FALSE(matrix->rightNeighbour(Point(4, 4)));
}

*/
/*
 * check leftNeighbour function
 *//*

TEST_F(MatrixTest, leftNeighbour) {
    ASSERT_TRUE(matrix->leftNeighbour(Point(1, 1)));
    EXPECT_FALSE(matrix->leftNeighbour(Point(0, 0)));

}

*/
/*
 * check upNeighbour function
 *//*

TEST_F(MatrixTest, UpNeighbour) {
    ASSERT_TRUE(matrix->upNeighbour(Point(1, 1)));
    EXPECT_FALSE(matrix->upNeighbour(Point(3, 4)));
}

*/
/*
 * check downNeighbour function
 *//*

TEST_F(MatrixTest, downNeighbour) {
    ASSERT_TRUE(matrix->downNeighbour(Point(1, 1)));
    EXPECT_FALSE(matrix->downNeighbour(Point(0, 0)));
}

*/
/*
 * check getNOde function
 *//*

TEST_F(MatrixTest, getNode) {
    EXPECT_TRUE(matrix->getNode(1, 1)->operator==(*node2));
}

*/
/*
 * check getFirst function
 *//*

TEST_F(MatrixTest, getFirst) {
    EXPECT_TRUE(matrix->getFirst()->operator==(First));
}
TEST_F(MatrixTest, getNeighbour){
EXPECT_TRUE(matrix->getNode(0,0)->getNeighbours()[2]->operator==(*matrix->getNode(1,0)));
EXPECT_TRUE(matrix->getNode(0,0)->getNeighbours()[1]->operator==(*matrix->getNode(0,1)));
}*/
