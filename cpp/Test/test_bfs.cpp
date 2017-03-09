/*
//
// Created by tomer on 12/3/16.
//

#include <gtest/gtest.h>
#include "../src/BFS.h"
#include "../src/MatrixMap.h"

TEST(test_bfs, SmallestRoad) {
    vector<Point> *vec=new vector<Point>();
    MatrixMap *matrix = new MatrixMap(10, 10, vec);
    Point p(3, 3), start(0, 0), end(2, 2), p1(0, 1), p2(0, 2), p3(1, 2);
    BFS *bfs = new BFS();
    AbstractNode *nodeStart = new Node(start);
    AbstractNode *nodeEnd = new Node(end);
    AbstractNode *nodeP1 = new Node(p1);
    AbstractNode *nodeP2 = new Node(p2);
    AbstractNode *nodeP3 = new Node(p3);
    nodeStart->setObstacle(false);
    nodeEnd->setObstacle(false);
    nodeP1->setObstacle(false);
    nodeP2->setObstacle(false);
    nodeP3->setObstacle(false);
    queue<AbstractNode *> q = bfs->smallestRoad(matrix->getNode(start), matrix->getNode(end));
    EXPECT_TRUE(q.front()->operator==(*nodeStart));
    q.pop();
    EXPECT_TRUE(q.front()->operator==(*nodeP1));
    q.pop();
    EXPECT_TRUE(q.front()->operator==(*nodeP2));
    q.pop();
    EXPECT_TRUE(q.front()->operator==(*nodeP3));
    q.pop();
    EXPECT_TRUE(q.front()->operator==(*nodeEnd));
    q.pop();
    delete bfs;
    delete nodeEnd;
    delete nodeP1;
    delete nodeP2;
    delete nodeStart;
    delete nodeP3;
    delete vec;
    delete matrix;
}
*/
