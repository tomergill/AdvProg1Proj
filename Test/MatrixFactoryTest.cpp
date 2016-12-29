/*
//
// Created by alon on 02/12/16.
//

#include <gtest/gtest.h>
#include "../src/Map.h"
#include "../src/MatrixMap.h"
#include "../src/MatrixFactory.h"

*/
/*
 * class that checks matrixFactory functions
 *//*

class MatrixFactoryTest : public testing::Test {
protected:
    Map *grid;
    Map *grid2;
    MatrixFactory *matrixFactory;

*/
/*
 * give the first values before every test
 *//*

    virtual void SetUp() {
        grid = new MatrixMap(10, 10, {});
        matrixFactory = new MatrixFactory();
        grid2=NULL;
    }

*/
/*
 * delete the values after every test
 *//*

    virtual void TearDown() {
        delete matrixFactory;
        delete grid;
    }
};

//*/
/*
// * check the function build map
// *//*

//TEST_F(MatrixFactoryTest, buildMap) {
//    grid2 = matrixFactory->buildMap("10 10");
//    EXPECT_TRUE(grid->operator==(const grid2));
//}


*/
