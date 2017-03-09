/*
//
// Created by alon on 02/12/16.
//

#include <gtest/gtest.h>
#include "../src/Cab.h"
#include "../src/Node.h"

*/
/*
 * class that check the function of the cab class
 *//*

class CabTest : public ::testing::Test {
protected:
    Cab *cab;
    int cabId;
    int  passedKm;
    CarManufactur type;
    CarColor color;
    double tarif;
    Point point;
    AbstractNode *node;
    queue<AbstractNode *> course;

*/
/*
 * give the first values before every test
 *//*

    virtual void SetUp() {
        cabId = 1234;
        passedKm = 30;
        type = CarManufactur::H;
        color = CarColor::B;
        tarif = 80.3;
        cab = new Cab(cabId, type, color);
        point = Point(2, 2);
        node = new Node(point);
    }

*/
/*
 * delete the values after every test
 *//*

    virtual void TearDown() {
        delete cab;
        delete node;
    }
};

*/
/*
 * check the getPoint function
 *//*

TEST_F(CabTest, getPoint) {
    course.push(node);
    AbstractNode *node2 = cab->move(&course);
    EXPECT_TRUE(node2->operator==(*node));
}*/
