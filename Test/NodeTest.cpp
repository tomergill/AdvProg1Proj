/**//*
//
// Created by alon on 01/12/16.
//
#include "../src/Node.h"
#include "gtest/gtest.h"
#include "../src/MatrixMap.h"

using namespace std;

*/
/*
 * check the functions of node class
 *//*

class NodeTest : public ::testing::Test {
protected:
    Point p1;
    Point p3;
    Point p;
    Point p2;
    Node *node2;
    Node node3;
    AbstractNode *node;
    AbstractNode *neighbourLeft;
    AbstractNode *neighbourRight;
    AbstractNode *neighbourUp;
    AbstractNode *neighbourDown;
    MatrixMap *matrix;
    vector<Point> *vec;

*/
/*
 * give the first values before every test
 *//*

    virtual void SetUp() {
        p3 = Point(2, 3);
        p =Point(2, 3);
        p2 =  Point(2, 3);
        p1 = Point(4, 4);
        node3 = Node(Point(2, 3));
        node2 = new Node(p1);
        node = new Node(p1);
        vec=new vector<Point>();
        neighbourLeft = new Node(Point(3, 4));
        neighbourRight = new Node(Point(5, 4));
        neighbourUp = new Node(Point(4, 5));
        neighbourDown = new Node(Point(4, 3));
        matrix = new MatrixMap(10, 10, vec);
    }

*/
/*
 * delete the values after every test
 *//*

    virtual void TearDown() {
        delete node2;
        node->getNeighbours().clear();
        delete node;
        delete neighbourLeft;
        delete neighbourRight;
        delete neighbourUp;
        delete neighbourDown;
        delete vec;
        delete matrix;
    }
};

// tests for Point
*/
/*
 * check getx function
 *//*

TEST_F(NodeTest, GetX) {
    EXPECT_EQ(2, p.getX());
}

*/
/*
 * check gety function
 *//*

TEST_F(NodeTest, GetY) {
    EXPECT_EQ(3, p.getY());
}

*/
/*
 * check operatr print of point
 *//*

TEST_F(NodeTest, operatorPrint) {
    testing::internal::CaptureStdout();
    cout << p3;
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(2,3)");
}

*/
/*
 * check operator equals of point
 *//*

TEST_F(NodeTest, operatorEquals) {
    EXPECT_TRUE(p.operator==(p2));
}
// finish tests on Point


// tests for Node
*/
/*
 * check getPoint functoin
 *//*

TEST_F(NodeTest, getPoint) {
    ASSERT_EQ(node2->getPoint().getY(), p1.getY());
    EXPECT_EQ(node2->getPoint().getX(), p1.getX());
}


*/
/*
 * check operator equals
 *//*

TEST_F(NodeTest, Equals) {
    EXPECT_TRUE(node->operator==(*node2));
}

*/
/*
 * check operator print
 *//*

TEST_F(NodeTest, Print) {
    testing::internal::CaptureStdout();
    cout << node3;
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(2,3)");
}

*/
/*
 * check addNeighbour function
 *//*

TEST_F(NodeTest, addNeighbour) {
    node->addNeighbours(this->matrix->getNode(5,4));
    EXPECT_TRUE(node->getNeighbours()[0]->operator==(*neighbourRight));
}

*/
/*
 * check getNeighbour function
 *//*

TEST_F(NodeTest, getNeighbours) {
    node->addNeighbours(this->matrix->getNode(3,4));
    node->addNeighbours(this->matrix->getNode(4,5));
    node->addNeighbours(this->matrix->getNode(5,4));
    node->addNeighbours(this->matrix->getNode(4,3));

    ASSERT_TRUE(neighbourLeft->operator==(*node->getNeighbours()[0]));
    ASSERT_TRUE(neighbourUp->operator==(*node->getNeighbours()[1]));
    ASSERT_TRUE(neighbourRight->operator==(*node->getNeighbours()[2]));
    ASSERT_TRUE(neighbourDown->operator==(*node->getNeighbours()[3]));
}



*/
