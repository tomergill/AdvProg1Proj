//
//// Created by tomer on 12/3/16.
////
//
//#include <gtest/gtest.h>
//#include "../src/Point.h"
//
//TEST(test_point, GetX) {
//    Point point(1, 0);
//    Point point1;
//    Point point2(&point);
//
//    EXPECT_EQ(point.getX(), 1);
//    EXPECT_EQ(point1.getX(), 0);
//    EXPECT_EQ(point2.getX(), 1);
//}
//
//TEST(test_point, GetY) {
//    Point point(0, 1);
//    Point point1;
//    Point point2(&point);
//
//    EXPECT_EQ(point.getY(), 1);
//    EXPECT_EQ(point1.getY(), 0);
//    EXPECT_EQ(point2.getY(), 1);
//}
//
//
//TEST(test_point, EqualsTo) {
//    Point p1(1, 1), p2(1, 1), p3(2, 2);
//
//    EXPECT_TRUE(p1 == p2);
//    EXPECT_FALSE(p1 == p3);
//}
//
//TEST(test_point, CopyConstructor) {
//    Point *p1 = new Point(5, 5);
//    Point *p2 = new Point(p1);
//
//    EXPECT_TRUE(p1->operator==(p2));
//    delete p1;
//    delete p2;
//}