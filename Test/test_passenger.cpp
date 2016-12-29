/*
//
// Created by tomer on 12/3/16.
//

#include "../src/Passenger.h"
#include "../src/Node.h"
#include <gtest/gtest.h>

TEST(test_passenger, GetRating) {
    Point p1(0, 0), p2(1, 1);
    AbstractNode *node1 = new Node(p1);
    AbstractNode *node2 = new Node(p2);
    Passenger passenger(node1, node2);
    int rating = passenger.getRating();

    ASSERT_GE(rating, 1);
    ASSERT_LE(rating, 5);
    delete node1;
    delete node2;
}

TEST(test_passenger, GetSource) {
    Point p1(0, 0), p2(1, 1);
    AbstractNode *node1 = new Node(p1);
    AbstractNode *node2 = new Node(p2);
    Passenger passenger(node1, node2);

    EXPECT_TRUE(passenger.getSource()->operator==(*node1));
    delete node1;
    delete node2;
}

TEST(test_passenger, GetDestination) {
    Point p1(0, 0), p2(1, 1);
    AbstractNode *node1 = new Node(p1);
    AbstractNode *node2 = new Node(p2);
    Passenger passenger(node1, node2);
    EXPECT_TRUE(passenger.getDestination()->operator==(*node2));
    delete node1;
    delete node2;
}
*/
