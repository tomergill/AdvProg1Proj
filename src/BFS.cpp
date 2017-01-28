//
// Created by tomer on 12/1/16.
//

#include <stack>
#include "BFS.h"

/**
 * Constructor.
 */
BFS::BFS() {
}

/**
 * @param node start
 * @param finish finish
 * @return queue with points that are the shortest route from start to finish
 */
queue<AbstractNode *> BFS::smallestRoad(AbstractNode *node, AbstractNode *finish) {
    queue<AbstractNode *> queue;
    node->setDistance(0);
    node->setFlag(true);
    if (!node->isObstacle()) {
        queue.push(node);
        // while we have abstract nodes in the queue.
        while (!queue.empty()) {
            node = queue.front();
            // if we found the finish point we will print all points.
            if (node == finish) {
                std::stack<AbstractNode *> stack;
                while (node->getDistance() != 0) {
                    stack.push(node);
                    node = node->getPrevious();
                }
                stack.push(node);
                std::queue<AbstractNode *> q;
                while (!stack.empty()) {
                    node = stack.top();
                    stack.pop();
                    q.push(node);
                }
                return q;
            }
            queue.pop();
            vector<AbstractNode *> arr = node->getNeighbours();
            // add the corect neighbours to the queue.
            for (int i = 0; i < 4; i++) {
                if (arr[i] != NULL && !arr[i]->isObstacle()) {
                    if (!(arr[i]->getFlag())) {
                        if (arr[i]->getDistance() == -1) {
                            arr[i]->setFlag(true);
                            arr[i]->setDistance(node->getDistance() + 1);
                            arr[i]->setNode(node);
                            queue.push(arr[i]);
                        }
                    }
                }
            }
        }
    }
}

/**
 * Destructor
 */
BFS::~BFS(){

}