#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;
using namespace boost::archive;
using namespace boost::serialization;

//
// Created by alon on 15/11/16.
//
#include <iostream>

#ifndef EX1_TIHNUT_POINT_H
#define EX1_TIHNUT_POINT_H


/**
 * class Point have a cordinations and functions of Point.
 */
class Point {
   friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
        {
            ar & x;
            ar & y;
        }
private:
    int x;
    int y;

public:

    //Point(int x=0, int y=0);
    Point(int x, int y);
    Point(Point *p1);

    Point();

    int getX() const;

    int getY() const;

    bool operator==(const Point &point2);

    friend ostream &operator<<(std::ostream &os, const Point &p);
};

#endif //EX1_TIHNUT_POINT_H
