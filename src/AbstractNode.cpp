//
// Created by alon on 17/11/16.
//

#include "AbstractNode.h"
#include "Node.h"

/**
 * c-tor of abstract node.
 * @return.
 */
AbstractNode::AbstractNode() {

}
AbstractNode::~AbstractNode(){}
/**
 * set the distance for abstract node.
 * @param x the distance.
 */
void AbstractNode::setDistance(int x) {
    distance = x;
}

/**
 * get the distance of the abstract node.
 * @return the distance.
 */
int AbstractNode::getDistance() {
    return distance;
}

/**
 * if we pass over thid node we will remember it.
 * we will not pass this node again.
 * @param flag1 true or false.
 */
void AbstractNode::setFlag(bool flag1) {
    flag = flag1;
}

/**
 * check if we pass this abstract node or not.
 * @return true or false.
 */
bool AbstractNode::getFlag() {
    return flag;
}

/**
 * get the father of the abstract node.
 * @return abstract node.
 */
AbstractNode *AbstractNode::getPrevious() {
    return previousNode;
}

/**
 * set the father abstract node of this abstract node.
 * @param b the father node.
 */
void AbstractNode::setNode(AbstractNode *b) {
    previousNode = b;
}

/**
 * print the abstract node.
 * @param os.
 * @param node.
 * @return.
 */
ostream &operator<<(ostream &os, const AbstractNode &node) {
    return node.print(os);
}



