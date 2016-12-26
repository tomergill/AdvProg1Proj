//
// Created by tomer on 12/1/16.
//

#include "Trip.h"

/*
 * c tor of trip
 */
Trip::Trip(int id, Point *start, Point *end, double tarif, Map *map) {
    this->rideId = id;
    this->start = start;
    this->end = end;
    this->tarif = tarif;
    this->driver = NULL;
    this->passengersNum = 0;
    this->passengersVec = {};
    this->totalMPassed = 0;
    this->map = map;
    this->bfs = new BFS();
}

/*
 * destructor of trip
 */
Trip::~Trip() {
    delete start;
    delete end;
    while (!passengersVec.empty()) {
        Passenger *p = passengersVec.back();
        passengersVec.pop_back();
        delete p;
    }
    delete bfs;
/*
while(!course.empty()){
AbstractNode* p2=course.front();
course.pop();
delete p2;
}*/
}

/*
 * add passenger to a trip
 */
void Trip::addPassenger(Passenger *p) {
    this->passengersVec.push_back(p);
    this->passengersNum += 1;
}

/*
 * move the trip one step
 */
void Trip::move() {
    while (!course.empty() && !this->driver->getLocation()->operator==(
            *(this->map->getNode(this->end->getX(), this->end->getY())))) {
        moveOneStep();
    }
}

/*
 * move the trip
 */
void Trip::moveOneStep() {
    if (!course.empty() && !this->driver->getLocation()->operator==(
            *(this->map->getNode(this->end->getX(), this->end->getY())))) {
        this->driver->move();
    }
}

/*
 * get the passenger num of the trip
 */
int Trip::getPassengersNum() {
    return this->passengersNum;
}

/*
 * id of trip
 */
int Trip::getRideId() const {
    return rideId;
}

/*
 * set id trip
 */
void Trip::setRideId(int rideId) {
    Trip::rideId = rideId;
}

/*
 * get tariff of trip
 */
double Trip::getTarif() {
    return this->tarif;
}

/*
 * get the course of trip
 */
queue<AbstractNode *> *Trip::getCourse() {
    return this->driver->getCourse();
}

/*
 * get the driver of the trip
 */
Driver *Trip::getDriver() {
    return this->driver;
}

/*
 * set the course of the trip
 */
void Trip::setCourse() {
    this->course = this->bfs->smallestRoad(
            this->map->getNode(this->start->getX(), this->start->getY()),
            this->map->getNode(this->end->getX(), this->end->getY()));
    this->map->newRoad();

}

/*
 * set the driver of the trip
 */
void Trip::setDriver(Driver *driver) {
    this->driver = driver;
    if (driver != NULL)
        this->driver->setCourse(&this->course);
}

/*
 * total num of km passed
 */
int Trip::getTotalMPassed() {
    return this->driver->getKm();
}

/*
 * set km paased
 */
void Trip::setTotalMPassed(int totalMPassed) {
    Trip::totalMPassed = totalMPassed;
}

/*
 * get start point of the trip
 */
AbstractNode *Trip::getStart() {
    return map->getNode(start->getX(), start->getY());
}

/*
 * get end point of the trip
 */
AbstractNode *Trip::getEnd() {
    return map->getNode(end->getX(), end->getY());
}

/**
 * Finishes the trip by giving the driver satisfaction ratings.
 */
void Trip::finish()
{
    int sum = 0, i;
    for (i = 0; i < passengersNum; i++)
        sum += passengersVec[i]->getRating();
    driver->addSatisfaction(sum, passengersNum);
}