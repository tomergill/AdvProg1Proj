/*
//
// Created by tomer on 12/3/16.
//

#include <gtest/gtest.h>
#include "../src/Driver.h"
#include "../src/MatrixMap.h"
#include "../src/Trip.h"

TEST(test_driver, ChangeTaxi) {
    Cab t(1234, CarManufactur::F, CarColor::B),
            c(6789, CarManufactur::H, CarColor::R);
    Point p(1, 1);
     vector<Point> *vec=new vector<Point>();
    MatrixMap m(1, 1, vec);
    BFS *bfs = new BFS();
    Driver driver(0, 0, MartialStatus::D, bfs,m.getFirst());
    driver.changeTaxi(&t);
    ASSERT_FALSE(driver.getTaxi() == NULL);
    EXPECT_EQ(t.getId(), driver.getTaxi()->getId());
    driver.changeTaxi(&c);
    EXPECT_EQ(c.getId(), driver.getTaxi()->getId());
    EXPECT_NE(t.getId(), driver.getTaxi()->getId());
    delete bfs;
    delete vec;
}

TEST(test_driver, addSatisfaction) {
    Point p(1, 1);
     vector<Point> *vec=new vector<Point>();
    MatrixMap m(1, 1, vec);
    BFS *bfs = new BFS();
    Driver driver(0, 0, MartialStatus::W, bfs,m.getFirst());
    driver.addSatisfaction(5, 1);
    EXPECT_EQ(5, driver.getSatisfaction());
    driver.addSatisfaction(4, 2);
    EXPECT_EQ(13.0/3, driver.getSatisfaction());
    delete bfs;
    delete vec;
}

TEST(test_driver, AddExperience) {
    Point p(1, 1);
     vector<Point> *vec=new vector<Point>();
    MatrixMap m(1, 1, vec);
    BFS *bfs = new BFS();
    Driver driver(0, 0, MartialStatus::W, bfs,m.getFirst());
    EXPECT_EQ(0, driver.getExperience());
    driver.addExperience(3);
    EXPECT_EQ(3, driver.getExperience());
    driver.addExperience(3);
    EXPECT_EQ(6, driver.getExperience());
    delete vec;
    delete bfs;
}

TEST(test_driver, GetId) {
    Point p(1, 1);
     vector<Point> *vec=new vector<Point>();
    MatrixMap m(1, 1, vec);
    BFS *bfs = new BFS();
    Driver driver(0, 0, MartialStatus::W, bfs,m.getFirst());
    EXPECT_EQ(0, driver.getId());
    delete vec;
    delete bfs;
}
*/
