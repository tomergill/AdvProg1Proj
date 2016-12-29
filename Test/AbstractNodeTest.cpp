/*
//
// Created by alon on 01/12/16.
//

#include "gtest/gtest.h"
#include "../src/AbstractNode.h"
#include "../src/Node.h"

using namespace std;

*/
/**
 * class that test the abstractNode class
 *//*

class AbstractNodeTest : public ::testing::Test {
protected:
    AbstractNode *abstractNode;
    AbstractNode *previous;
    Point p;
    Point p2;
    int distance;
    bool flag;

*/
/*
 * give the first values before every test
 *//*

    virtual void SetUp() {
        p = Point(3, 3);
        p2 = Point(2, 3);
        abstractNode = new Node(p);
        distance = 5;
        abstractNode->setDistance(distance);
        flag = true;
        abstractNode->setFlag(flag);
        previous = new Node(p2);
        abstractNode->setNode(previous);
    }

*/
/*
 * delete the values after every test
 *//*

    virtual void TearDown() {
        delete abstractNode;
        delete previous;
    }

};
*/
/*
 * check setDistance function
 *//*

TEST_F(AbstractNodeTest, setDistance) {
    abstractNode->setDistance(distance);
    EXPECT_EQ(abstractNode->getDistance(), distance);
}
*/
/*
 * check getDistance function
 *//*

TEST_F(AbstractNodeTest, getDistance) {
    EXPECT_EQ(abstractNode->getDistance(), distance);
}
*/
/*
 * check detFlag function
 *//*

TEST_F(AbstractNodeTest, setFlag) {
    abstractNode->setFlag(false);
    EXPECT_TRUE(!abstractNode->getFlag());
}
*/
/*
 * check getFlag function
 *//*

TEST_F(AbstractNodeTest, getFlag) {
    EXPECT_TRUE(abstractNode->getFlag());
}
*/
/*
 * check if the setPrevious function
 *//*

TEST_F(AbstractNodeTest, setPrevious) {
    abstractNode->setNode(previous);
    EXPECT_TRUE(abstractNode->getPrevious() == previous);
}
*/
/*
 * check if the getPrevious function
 *//*

TEST_F(AbstractNodeTest, getPrevious) {
    EXPECT_TRUE(abstractNode->getPrevious() == previous);
}
*/
/*
 * check Print function
 *//*

TEST_F(AbstractNodeTest, Print) {
    testing::internal::CaptureStdout();
    cout << *abstractNode;
    string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "(3,3)");
}*/
