//
// Created by tomer on 12/1/16.
//
#include <list>

#include "TaxiCenter.h"
#include "ThreadPool.h"
#include <pthread.h>
pthread_mutex_t LockGood1 = PTHREAD_MUTEX_INITIALIZER;
//#include "../easylogging++.h"


/*
 * add passenger and create a trip for him
 */
void TaxiCenter::answerCall(int id, Point *start, Point *end, double tarif, int pass,
                       int startTime) {
    int i;

    Trip *t = new Trip(id, start, end, tarif, map, startTime);
    //this->createTread(t);
//    this->setCurrentTrip(t);
    this->addingJob(t);
    trips.push_back(t);
    for (i = 0; i < pass; i++) {
        //int start_x, start_y, end_x, end_y;

        AbstractNode *startn = map->getNode(start->getX(), start->getY()),
                *endn = map->getNode(end->getX(), end->getY());
        Passenger *p = new Passenger(startn, endn);
        t->addPassenger(p);
    }
    //Assign driver to trip
    /*t->setDriver(findClosestDriverToPoint(map->getNode(start->getX(),
                                                       start->getY())));*/
    //add a TripTimer for this trip.
    timers.push_front(new TripTimer(t));
}

/*
 * add driver to taxicenter
 */
void TaxiCenter::addDriver(int id, int age, MartialStatus mstatus) {
    Driver *d = new Driver(id, age, mstatus, bfs, map->getFirst(), 0);
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
    bool valid = true;

    // notifying. If a trip timer hasn't got a drive, one is assigned to it
    // and no movement is made.
    for (tick = timers.begin(); tick != timers.end(); tick++) {
        if (time >= (*tick)->getStartTime()) {
            TripTimer *temp1 = dynamic_cast<TripTimer *> (*tick);
            if (temp1 != NULL)
            {
                if (temp1->getTrip()->getDriver() == NULL)
                {
                    valid = true;
                    while (true)
                    {
                        if (temp1->getTrip()->isIsFinishBFS())
                        {
                            if (temp1->getTrip()->isIsValidEndPoint() == 1)
                            {
                                deletetriplistener(temp1->getTrip()
                                                           ->getRideId());
                                deleteTrip(temp1->getTrip()->getRideId());
                                tick = timers.begin();
                                valid = false;
                            }
                            break;
                        }
                    }
                    if (valid)
                        assignADriverToTrip(temp1->getTrip());
                }
                else if(time > (*tick)->getStartTime())
                    (*tick)->tock(time);
            } else {
                (*tick)->tock(time);
            }
        }
    }

    //deleting finished trips
    it = trips.begin();
    while (it != trips.end()) {
        if ((*it)->getDriver() != NULL && (*it)->getEnd()->operator==(*((*it)
                ->getDriver()->getLocation()))) {
//            LINFO << "delete Trip:  " << (*it)->getRideId() << endl;
            (*it)->finish();
            temp = *it;
            it = trips.erase(it);
            deletetriplistener(temp->getRideId());
            delete temp;
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
    this->thread = NULL;
    this->threadpool = new ThreadPool(5);
}

/*
 * print locations of drivers
 */
void TaxiCenter::printDriverLocation(Driver *driver) {
    if (driver != NULL) {
        cout << *(driver->getLocation()) << "\n";
    } else {
        cout << "-1" << endl;
    }
}

void TaxiCenter::deleteTrip(int id)
{
    list<Trip *>::iterator it = trips.begin();
    Trip *temp;

    while (it != trips.end()) {
        temp = *it;
        //temp = dynamic_cast<TripTimer *> (*it);
        if (id == (*it)->getRideId()) {
            it = trips.erase(it);
            delete temp;
        } else {
            it++;
        }
    }
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
//        LINFO << (*it_d)->getId() << endl;
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
    delete this->threadpool;
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
    return NULL;
}

/*
 * get cab with this id
 */
AbstractCab *TaxiCenter::getCab(int id) {
    list<AbstractCab *>::iterator it = cabs.begin();
    for (it; it != cabs.end(); it++) {
//        LINFO << "CAB ID:" << (*it)->getId() << endl;
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

/**
 * Deletes the TripTimer related to the specified trip.
 * @param tripId id of the trip.
 */
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

/**
 * @return The first node of the map.
 */
AbstractNode *TaxiCenter::getFirst() {
    return this->map->getFirst();
}

/**
 * @return the list of drivers
 */
list<Driver *> TaxiCenter::getDrivers() {
    return this->drivers;
}

/**
 * @return the list of trips
 */
list<Trip *> TaxiCenter::getTrips() {
    return this->trips;
}

/**
 * Assigns a driver to teh specified trip.
 * @param tripId id of the trip.
 */
void TaxiCenter::assignADriverToTrip(int tripId) {
    assignADriverToTrip(getTrip(tripId));
}

/**
 * Assigns a driver to the specified trip.
 * @param t pointer to trip.
 */
void TaxiCenter::assignADriverToTrip(Trip *t) {
    Driver *d = findClosestDriverToPoint(t->getStart());
    if (d != NULL) {
//        LINFO << t->getRideId() << "    ID OF TRIP " << endl;
//        LINFO << d->getId() << "   ID OF DRIVER" << endl;
    }
    // LINFO << ";;;;" << endl;
    t->setDriver(d);
}

/**
 * @param x x-value of point
 * @param y y-value of point
 * @return returns the (x,y) node
 */
AbstractNode *TaxiCenter::getNode(int x, int y) {
    return this->map->getNode(x, y);
}

/**
 * @return the BFS.
 */
BFS *TaxiCenter::getBFS() {
    return this->bfs;
}

//void TaxiCenter::createTread(Trip *trip) {
//    trip->createPthread();
//}

void TaxiCenter::deleteFirstDriver() {
    this->drivers.pop_front();
}

//void TaxiCenter::waitForThread() {
//    Trip *arr[this->trips.size()];
//    int i = 0;
//    int size = this->trips.size();
//    while (i < size) {
//        arr[i] = this->trips.front();
//        this->trips.pop_front();
//        i++;
//    }
//    i = 0;
//    while (i < size) {
//        arr[i]->Join();
//        this->trips.push_back(arr[i]);
//        i++;
//    }
//}

void TaxiCenter::pushDriver(Driver *driver) {
    this->drivers.push_back(driver);
}

Map* TaxiCenter::getMap()
{
    return map;
}

bool TaxiCenter::isFreeCabId(int id) {
    list<AbstractCab *>::iterator it;

    for (it = cabs.begin(); it != cabs.end(); it++)
    {
        if ((*it)->getId() == id)
            return false;
    }
    return true;
}

bool TaxiCenter::isFreeTripId(int id) {
    list<Trip *>::iterator it;

    for (it = trips.begin(); it != trips.end(); it++)
    {
        if ((*it)->getRideId() == id)
            return false;
    }
    return true;
}

//void TaxiCenter::addingJob(TaxiCenter *trip) {
//    Job *job = new Job(trip->setCourse, (void *) trip);
//    this->threadpool->addJob(job);
//}

void TaxiCenter::addingJob(Trip *trip) {
    Job *job = new Job(trip->setCourse, (void *) trip);
    this->threadpool->addJob(job);
}

void TaxiCenter::setDrivers(const list<Driver *> &drivers) {
    TaxiCenter::drivers = drivers;
}

const list<AbstractCab *> &TaxiCenter::getCabs() const {
    return cabs;
}

void TaxiCenter::setCabs(const list<AbstractCab *> &cabs) {
    TaxiCenter::cabs = cabs;
}

void TaxiCenter::setTrips(const list<Trip *> &trips) {
    TaxiCenter::trips = trips;
}

Map *TaxiCenter::getMap() const {
    return map;
}

void TaxiCenter::setMap(Map *map) {
    TaxiCenter::map = map;
}

BFS *TaxiCenter::getBfs() const {
    return bfs;
}

void TaxiCenter::setBfs(BFS *bfs) {
    TaxiCenter::bfs = bfs;
}

const list<TimeListener *> &TaxiCenter::getTimers() const {
    return timers;
}

void TaxiCenter::setTimers(const list<TimeListener *> &timers) {
    TaxiCenter::timers = timers;
}

thread_t TaxiCenter::getThread() const {
    return thread;
}

void TaxiCenter::setThread(thread_t thread) {
    TaxiCenter::thread = thread;
}

ThreadPool *TaxiCenter::getThreadpool() const {
    return threadpool;
}

void TaxiCenter::setThreadpool(ThreadPool *threadpool) {
    TaxiCenter::threadpool = threadpool;
}

//void TaxiCenter::setNumberOfTrips(int numberOfTrips) {
//    TaxiCenter::numberOfTrips = numberOfTrips;
//}


//void *TaxiCenter::setCourse(void *trip2) {
//    TaxiCenter *taxiCenter = (TaxiCenter *) trip2;
//    Trip *trip = taxiCenter->getCurrentTrip();
//    cout << "before lock" << endl;
//    pthread_mutex_lock(&LockGood1);
//
//    queue<AbstractNode *> course = trip->getBfs()->smallestRoad(trip->getMap()->getNode(trip->getXStartPoint(),
//                                                                                        trip->getYStartPoint()),
//                                                                trip->getMap()->getNode(trip->getXEndPoint(),
//                                                                                        trip->getYEndPoint()));
//    if (course.empty()) {
//        cout << "the course is not good" << endl;
//        trip->setIsValidEndPoint(1);
//    } else {
//        cout << "the course is good" << endl;
////    cout << "finish do pthread" << endl;
//        trip->setIsValidEndPoint(2);
//        trip->settingCourse(course);
//    }
//    trip->getMap()->newRoad();
//    trip->setIsFinishBFS(true);
//
//    if (trip->isIsValidEndPoint() == 1) {
//        pthread_mutex_unlock(&LockGood1);
//        return NULL;
//    }
//    taxiCenter->addTrip(trip);
//    pthread_mutex_unlock(&LockGood1);
//    return NULL;
//}

//Trip *TaxiCenter::getCurrentTrip() const {
//    return currentTrip;
//}
//
//void TaxiCenter::setCurrentTrip(Trip *currentTrip) {
//    TaxiCenter::currentTrip = currentTrip;
//}

void TaxiCenter::addTrip(Trip *d) {
    this->trips.push_back(d);

}