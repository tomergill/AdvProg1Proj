//
// Created by tomer on 12/1/16.
//

#include "Driver.h"

Driver::Driver(int id, int age, MartialStatus mstatus, BFS *bfs, AbstractNode *startNode) {
    this->id = id;
    this->age = age;
    this->mstatus = mstatus;
    this->bfs = bfs;
    this->location = startNode;
    this->totalPassengers = 0;
    this->totalSatisfaction = 0;
    this->km = 0;
    this->cab = NULL;
    this->totalExperience = 0;
}

Driver::~Driver() {
}

void Driver::changeTaxi(AbstractCab *t) {
    this->cab = t;
}

void Driver::addSatisfaction(int totalSatisfaction, int passengers) {
    this->totalSatisfaction += totalSatisfaction * passengers;
    this->totalPassengers += passengers;
}

void Driver::addExperience(int experience) {
    this->totalExperience += experience;
}

int Driver::getId() {
    return this->id;
}

int Driver::getKm() {
    return this->cab->getKm();
}

int Driver::getExperience() {
    return this->totalExperience;
}

double Driver::getSatisfaction() {
    return (double) this->totalSatisfaction / this->totalPassengers;
}

AbstractCab *Driver::getTaxi() {
    return this->cab;
}

AbstractNode *Driver::getLocation() {
    return this->location;
}

/*queue<AbstractNode *> *Driver::getCourse() {
    return this->course;
}*/

AbstractNode *Driver::move(queue<AbstractNode *> *queue1) {
    return this->location = this->cab->move(queue1);
}

/*void Driver::setCourse(queue<AbstractNode *> *queue1) {
    this->course = queue1;
    this->location = this->course->front();
}*/

Driver::Driver() {}

void Driver::setLocation() {
    this->location = NULL;
}

void Driver::setCab(AbstractCab *cab) {
    this->cab = cab;
}

