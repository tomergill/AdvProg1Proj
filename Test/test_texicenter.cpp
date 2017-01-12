////
//// Created by tomer on 12/4/16.
////
//
//#include <gtest/gtest.h>
//#include "../src/TaxiCenter.h"
//#include "../src/MatrixMap.h"
//
//TEST (TaxiCenter, addDriver) {
//    vector<Point> *vec=new vector<Point>();
//    MatrixMap *m=new MatrixMap(1, 1, vec);
//    TaxiCenter *t=new TaxiCenter(m);
//    delete vec;
//    delete t;
//}
//
//TEST (TaxiCenter, addTaxi) {
//     vector<Point> *vec=new vector<Point>();
//    MatrixMap *m=new MatrixMap(2, 2, vec);
//    TaxiCenter t(m);
//    Cab *c=new Cab(1, CarManufactur::H, CarColor::G);
//    t.addTaxi(c);
//    EXPECT_EQ(t.getNumberOfCabs(), 1);
//    delete vec;
//}
