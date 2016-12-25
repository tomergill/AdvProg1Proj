//
// Created by tomer on 12/1/16.
//

#include "Driver.h"

/*
 * c-tor of driver
 */
Driver::Driver(int id, int age, MartialStatus mstatus, BFS *bfs, AbstractNode *startNode) {
    this->id = id;
    this->age = age;
    this->mstatus = mstatus;
    this->bfs = bfs;
    this->location = startNode;
    this->totalPassengers = 0;
    this->totalSatisfaction = 0;
    this->km = 0;
}

Driver::~Driver() {
}

/*
 * change the taxi of the driver
 */
void Driver::changeTaxi(AbstractCab *t) {
    this->cab = t;
}

/*
 * add satifaction to the driver
 */
void Driver::addSatisfaction(int totalSatisfaction, int passengers) {
    this->totalSatisfaction += totalSatisfaction * passengers;
    this->totalPassengers += passengers;
}

/*
 * add experiance to the driver
 */
void Driver::addExperience(int experience) {
    this->totalExperience += experience;
}

/*
 * get id of driver
 */
int Driver::getId() {
    return this->id;
}

/*
 * get the km the taxi of driver passed
 */
int Driver::getKm() {
    return this->cab->getKm();
}

/*
 * get Experiance of the driver
 */
int Driver::getExperience() {
    return this->totalExperience;
}

/*
 * get satifaction of driver
 */
double Driver::getSatisfaction() {
    return (double) this->totalSatisfaction / this->totalPassengers;
}

AbstractCab *Driver::getTaxi() {
    return this->cab;
}

/*
 * get location of driver
 */
AbstractNode *Driver::getLocation() {
    return this->location;
}

/*
 * get the road of driver
 */
queue<AbstractNode *> *Driver::getCourse() {
    return this->course;
}

/*
 * moce driver with his cab
 */
AbstractNode *Driver::move() {
    this->location = this->cab->move(this->course);
}

/*
 * set the course of driver
 */
void Driver::setCourse(queue<AbstractNode *> *queue1) {
    this->course = queue1;
    this->location = this->course->front();
}

