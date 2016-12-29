//
// Created by alon on 16/11/16.
//
#include <iostream>
#include "Point.h"
#include "Node.h"
#include <boost/serialization/export.hpp>

using namespace std;

/**
 * Constructor.
 */
Node::Node()
{
    p = Point(0,0);
    arr = {};
    obstacle = false;
}

/**
 * c-tor of the node.
 * @param p1.
 * @return nothing.
 */
Node::Node(Point p1) {
    p = p1;
    arr = {};
    obstacle = false;
}

/**
 * get the point of the node.
 * @return point.
 */
Point Node::getPoint() {
    return p;
}

/**
 * add neighbour to the node.
 * @param node.
 * @param i the index in the vector.
 */
void Node::addNeighbours(AbstractNode *node) {
    arr.push_back(node);
}

/**
 * the neighboursof the node.
 * @return the neighbours.
 */
vector<AbstractNode *> Node::getNeighbours() {
    return arr;
}

/**
 * function that checks of 2 nodes are equal.
 * @param node2.
 * @return true or false.
 */
bool Node::operator==(const AbstractNode &node2) {
    return p == ((Node &) node2).getPoint();
}

/**
 * print the node.
 * @param os.
 * @return.
 */
ostream &Node::print(ostream &os) const {
    return os << p;
}

/*
 * set node as obstacle
 */
void Node::setObstacle(bool flag) {
    obstacle = flag;
}

/*
 * return if the node is obstacle
 */
bool Node::isObstacle() {
    return obstacle;
}

Node::~Node(){}

BOOST_CLASS_EXPORT(AbstractNode)