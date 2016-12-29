/*
  //
  // Created by alon on 02/12/16.
  //
  
  #include <gtest/gtest.h>
  #include "../src/Cab.h"
  #include "../src/LuxuryCab.h"
  #include "../src/Node.h"
  
  */
/*
   * class that check luxurycab functions
   *//*

  class LuxuryCabTest : public ::testing::Test {
  protected:
      AbstractCab *cabLuxury;
      int cabId;
      int passedKm;
      CarManufactur type;
      CarColor color;
      double tarif;
      Point *point;
      queue<AbstractNode *> course;
      AbstractNode *node;
  
  */
/*
   * give the first values before every test
   *//*

      virtual void SetUp() {
          cabId = 1234;
          passedKm = 30;
          type = CarManufactur::H;
          color = CarColor::B;
          tarif = 80.0;
          cabLuxury = new LuxuryCab(cabId, type, color);
          Point point(1, 2);
          node = new Node(point);
      }
  
  */
/*
   * delete the values after every test
   *//*

      virtual void TearDown() {
          delete cabLuxury;
          delete node;
      }
  };
  
  */
/*
   * check move function
   *//*

  TEST_F(LuxuryCabTest, move) {
      this->course.push(node);
      this->course.push(node);
      EXPECT_TRUE(cabLuxury->move(&course)->operator==(*node));
  }
*/
