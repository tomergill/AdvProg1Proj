//
// Created by tomer on 12/1/16.
//

#include "TaxiCenter.h"

/*
 * add passenger and create a trip for him
 */
void
TaxiCenter::answerCall(int id, Point *start, Point *end, double tarif, int pass,
                       int startTime) {
    int i;

    Trip *t = new Trip(id, start, end, tarif, map, startTime);
    t->setCourse();
    trips.push_back(t);
    for (i = 0; i < pass; i++) {
        //int start_x, start_y, end_x, end_y;

        AbstractNode *startn = map->getNode(start->getX(), start->getY()),
                *endn = map->getNode(end->getX(), end->getY());
        Passenger *p = new Passenger(startn, endn);
        t->addPassenger(p);
    }
    //Assign driver to trip
    t->setDriver(findClosestDriverToPoint(map->getNode(start->getX(),
                                                       start->getY())));
    //add a TripTimer for this trip.
    timers.push_front(new TripTimer(t));
}

/*
 * add driver to taxicenter
 */
void TaxiCenter::addDriver(int id, int age, MartialStatus mstatus) {
    Driver *d = new Driver(id, age, mstatus, bfs, map->getFirst());
    drivers.push_back(d);
}

void TaxiCenter::addDriver(Driver *driver) {
    drivers.push_back(driver);
}

/*
 * add taxi to taxicenter
 */
void TaxiCenter::addTaxi(AbstractCab *t) {
    cabs.push_back(t);
}

/*
 * Notifying all TimeListeners that time has passed.
 */
void TaxiCenter::timePassed(int time) {
    list<TimeListener *>::iterator tick;
    list<Trip *>::iterator it = trips.begin();
    Trip *temp = NULL;

    /*
     * checking if there are trips that need a driver, and assigning one if
     * possible.
     */
    for (it; it != trips.end(); it++)
    {
        if ((*it)->getDriver() == NULL)
        {
            assignADriverToTrip(*it);
        }
    }

    //notifying
    for (tick = timers.begin(); tick != timers.end(); tick++) {
        (*tick)->tock(time);
    }

    //deleting finished trips
    it = trips.begin();
    while (it != trips.end()) {
        if ((*it)->getDriver() != NULL && (*it)->getEnd()->operator==(*((*it)
                ->getDriver()->getLocation()))) {
            (*it)->finish();
            temp = *it;
            it = trips.erase(it);
            deletetriplistener(temp->getRideId());
            //delete temp;
        } else {
            it++;
        }
    }
}

/*
 * c-tor of taxi center
 */
TaxiCenter::TaxiCenter(Map *m) {
    this->map = m;
    bfs = new BFS();
    drivers = {};
    cabs = {};
    trips = {};
    timers = {};
}

/*
 * print locations of drivers
 */
void TaxiCenter::printDriverLocation(Driver *driver) {
    cout << *(driver->getLocation()) << "\n";
}

/*
 * print locations of drivers
 */
void TaxiCenter::printDriverLocation(int id) {
    printDriverLocation(getDriver(id));
}

/*
 * print all locations of drivers
 */
void TaxiCenter::printAllDriversLoactions() {
    list<Driver *>::iterator it = drivers.begin();
    for (it; it != drivers.end(); it++) {
        printDriverLocation(*it);
    }
}

/*
 * find driver that close to the point
 */
Driver *TaxiCenter::findClosestDriverToPoint(AbstractNode *p) {
    bool breaked;
    list<Driver *>::iterator it_d = drivers.begin();
    list<Trip *>::iterator it_t = trips.begin();

    for (it_d; it_d != drivers.end(); it_d++) { //going over drivers
        if ((*it_d)->getLocation()->operator==(*p)) { //if found driver in p
            breaked = false;

            /*Check if driver is already assigned to different trip:*/
            for (it_t = trips.begin(); it_t != trips.end(); it_t++) {
                if ((*it_t)->getDriver() != NULL
                    && (*it_t)->getDriver()->getId() == (*it_d)->getId()) {
                    breaked = true;
                    break;
                }
            }
            if (!breaked)
                return *it_d;
        }
    }
    return NULL;
}

/*
 * return number of drivers
 */
int TaxiCenter::getNumberOfDrivers() {
    return drivers.size();
}

/*
 * return number of cabs
 */
int TaxiCenter::getNumberOfCabs() {
    return cabs.size();
}

/*
 * return number of trips
 */
int TaxiCenter::getNumberOfTrips() {
    return trips.size();
}

/*
 * destructor of taxicenter
 */
TaxiCenter::~TaxiCenter() {
    //*Delete cabs*//
    while (!cabs.empty()) {
        AbstractCab *cab = cabs.front();
        cabs.pop_front();
        delete cab;
    }

    //Delete drivers//
    while (!drivers.empty()) {
        Driver *driver = drivers.front();
        drivers.pop_front();
        delete driver;
    }

    //Delete trips//
    while (!trips.empty()) {
        Trip *trip = trips.front();
        trips.pop_front();
        delete trip;
    }

    while (!timers.empty()) {
        TimeListener *timer = timers.front();
        timers.pop_front();
        delete timer;
    }
    delete map;
    delete bfs;
}

/*
 * add taxi to a driver
 */
void TaxiCenter::assignCabToDriver(int cabId, int driverId) {
    getDriver(driverId)->changeTaxi(getCab(cabId));
}

/*
 * get driver with this ip
 */
Driver *TaxiCenter::getDriver(int id) {
    list<Driver *>::iterator it = drivers.begin();
    for (it; it != drivers.end(); it++) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
}

/*
 * get cab with this id
 */
AbstractCab *TaxiCenter::getCab(int id) {
    list<AbstractCab *>::iterator it = cabs.begin();
    for (it; it != cabs.end(); it++) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
}

/*
 * get trip with this is
 */
Trip *TaxiCenter::getTrip(int id) {
    list<Trip *>::iterator it = trips.begin();
    for (it; it != trips.end(); it++) {
        if ((*it)->getRideId() == id) {
            return *it;
        }
    }
}

void TaxiCenter::deletetriplistener(int tripId) {
    list<TimeListener *>::iterator it = timers.begin();
    TripTimer *temp;

    while (it != timers.end()) {
        temp = dynamic_cast<TripTimer *> (*it);
        if (temp != NULL && tripId == temp->getTrip()->getRideId()) {
            it = timers.erase(it);
            delete temp;
        } else {
            it++;
        }
    }
}


AbstractNode *TaxiCenter::getFirst() {
    return this->map->getFirst();
}

list<Driver *> TaxiCenter::getDrivers() {
    return this->drivers;
}

list<Trip *> TaxiCenter::getTrips() {
    return this->trips;
}

void TaxiCenter::assignADriverToTrip(int tripId) {
    assignADriverToTrip(getTrip(tripId));
}

void TaxiCenter::assignADriverToTrip(Trip *t)
{
    Driver *d = findClosestDriverToPoint(t->getStart());
    t->setDriver(d);
}