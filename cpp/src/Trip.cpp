//
// Created by tomer on 12/1/16.
//
#include <pthread.h>
#include "Trip.h"
#include <iostream>

pthread_mutex_t LockGood = PTHREAD_MUTEX_INITIALIZER;

/*
 * c tor of trip
 */
Trip::Trip(int id, Point *start, Point *end, double tarif, Map *map,
           int startTime) {
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
    this->time = startTime;
    this->isValidEndPoint = 0;
    this->isFinishBFS = false;
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
    if (!course.empty() && driver != NULL) {
        if (!this->driver->getLocation()->operator==(
                *(this->map->getNode(this->end->getX(), this->end->getY())))) {
            this->driver->move(&this->course);
        }
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
 * get the driver of the trip
 */
Driver *Trip::getDriver() {
    return this->driver;
}

/*
 * set the course of the trip
 */
void *Trip::setCourse(void *trip2) {
    Trip *trip = (Trip *) trip2;
    pthread_mutex_lock(&LockGood);

    queue<AbstractNode *> course = trip->getBfs()->smallestRoad(trip->getMap()->getNode(trip->start->getX(),
                                                                                        trip->start->getY()),
                                                                trip->getMap()->getNode(trip->end->getX(),
                                                                                        trip->end->getY()));
   // cout << course.size() << endl;
    if (course.empty()) {
        //cout << "Trip #" << trip->rideId << " is not good" << endl;
        trip->setIsValidEndPoint(1);
    } else {
        trip->setIsValidEndPoint(2);
        trip->settingCourse(course);
    }
    trip->getMap()->newRoad();
    trip->setIsFinishBFS(true);
    pthread_mutex_unlock(&LockGood);
    return NULL;
}

/*
 * set the driver of the trip
 */
void Trip::setDriver(Driver *driver) {
    this->driver = driver;
    if (this->driver != NULL)
        this->driver->setLastPoint(this->getEnd());
/*    if (driver != NULL)
        this->driver->setCourse(&this->course);*/
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
void Trip::finish() {
    int sum = 0, i;
    for (i = 0; i < passengersNum; i++)
        sum += passengersVec[i]->getRating();
    driver->addSatisfaction(sum, passengersNum);
}

int Trip::getStartTime() {
    return time;
}

Trip::Trip() {}

Point Trip::getEndPoint() {
    return *(this->end);
}

/*
pthread_t *Trip::getPthread() {
    return pthread;
}
*/

BFS *Trip::getBfs() {
    return bfs;
}

const vector<Passenger *> &Trip::getPassengersVec() {
    return passengersVec;
}

Map *Trip::getMap() {
    return map;
}

const queue<AbstractNode *> &Trip::getCourse() {
    return course;
}

int Trip::getTime() {
    return time;
}

void Trip::settingCourse(queue<AbstractNode *> course) {
    this->course = course;
}

/*bool Trip::isFinish() const {
    return finishh;
}*/

void Trip::setStart(Point *start) {
    Trip::start = start;
}

void Trip::setEnd(Point *end) {
    Trip::end = end;
}

void Trip::setPassengersNum(int passengersNum) {
    Trip::passengersNum = passengersNum;
}

void Trip::setPassengersVec(const vector<Passenger *> &passengersVec) {
    Trip::passengersVec = passengersVec;
}

void Trip::setTarif(double tarif) {
    Trip::tarif = tarif;
}

void Trip::setMap(Map *map) {
    Trip::map = map;
}

void Trip::setBfs(BFS *bfs) {
    Trip::bfs = bfs;
}

void Trip::setCourse(const queue<AbstractNode *> &course) {
    Trip::course = course;
}

void Trip::setTime(int time) {
    Trip::time = time;
}

int Trip::isIsValidEndPoint() const {
    return isValidEndPoint;
}

void Trip::setIsValidEndPoint(int isValidEndPoint) {
    Trip::isValidEndPoint = isValidEndPoint;
}

bool Trip::isIsFinishBFS() const {
    return isFinishBFS;
}

void Trip::setIsFinishBFS(bool isFinishBFS) {
    Trip::isFinishBFS = isFinishBFS;
}

int Trip::getXStartPoint() {
    return this->start->getX();
}

int Trip::getYStartPoint() {
    return this->start->getY();
}

int Trip::getXEndPoint() {
    return this->end->getX();
}

int Trip::getYEndPoint() {
    return this->end->getY();
}