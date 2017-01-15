#include "MainFlow.h"
#include "Udp.h"
#include "Tcp.h"
/*#include "easyloggingpp-8.91/easylogging++.h"
_INITIALIZE_EASYLOGGINGPP*/
using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_t pthread1;
pthread_t pthread2;
int numberOfDrivers = 0;
int numberOf9Server = 0;

/*
 * c-tor of main flow
 */
MainFlow::MainFlow(MapFactory *factory) {
    mapFactory = factory;
    taxiCenter = NULL;
    time = 0;
    this->socket = new Tcp(1, 12345);
    this->trip = NULL;
    this->numberOfCase = -1;
    this->socket->initialize();
    this->finishCalculate = false;

}

/*
 * c-tor of main flow
 */
MainFlow::MainFlow(MapFactory *factory, int port) {
    mapFactory = factory;
    taxiCenter = NULL;
    time = 0;
    this->socket = new Tcp(1, port);
    this->trip = NULL;
    for (int i = 0; i < 999999; i++) {
        this->ports[i] = -1;
    }
    this->numberOfCase = -1;
    this->socket->initialize();
    this->finishCalculate = false;

}

/*
 * start the taxi center
 */
void MainFlow::startFlow(string mapInput) {
    taxiCenter = new TaxiCenter(mapFactory->buildMap(mapInput));
    flow();
}

MainFlow::~MainFlow() {
    delete taxiCenter;
    if (socket != NULL)
        delete socket;
}

/*
 * run the program
 */
void MainFlow::flow() {
    int input, driverId = 0, age = 0, experience = 0, cabId = 0, start_x = 0,
            start_y = 0, end_x = 0, end_y = 0, pass_num = 0, rideId = 0,
            taxi_type = 1, time1 = 0, numOfDrivers = 0;
    MartialStatus status = MartialStatus::S;
    double tariff = 0.0;
    CarColor color = CarColor::R;
    CarManufactur manufactur = CarManufactur::F;
    char dummy = ',', mstatus, cColor, manu;

    cin >> input;
    while (input != 7) {
        switch (input) {
            case 1: //New Driver
                this->numberOfCase = 1;
                cin >> numOfDrivers;
                this->addDriver(numOfDrivers);
                break;

            case 2: //New Trip
                this->numberOfCase = 2;
                cin >> rideId >> dummy >> start_x >> dummy >> start_y >> dummy
                    >> end_x >> dummy >> end_y >> dummy >> pass_num >> dummy
                    >> tariff >> dummy >> time1;
                taxiCenter->answerCall(rideId, new Point(start_x, start_y),
                                       new Point(end_x, end_y), tariff,
                                       pass_num, time1);
                break;
            case 3: //New Cab
                this->numberOfCase = 3;
                cin >> cabId >> dummy >> taxi_type >> dummy >> manu >> dummy
                    >> cColor;
                manufactur = getManuByChar(manu);
                color = getColorByChar(cColor);
                if (taxi_type == 1)
                    taxiCenter->addTaxi(new Cab(cabId, manufactur, color));
                else
                    taxiCenter->addTaxi(new LuxuryCab(cabId, manufactur,
                                                      color));
                break;
            case 4: //Print driver's location
                this->numberOfCase = 4;
                cin >> driverId;
                taxiCenter->printDriverLocation(driverId);
                break;
            case 9: //move trips
                while (true) {
                    if (numberOfDrivers >= numOfDrivers) {
                        break;
                    }
                }
                /* for (int i = 0; i < 2; i++) {
                     pthread_join(this->threads[i], NULL);
                     cout << "joining:" <<i<<endl;
                 }*/
                if (!this->finishCalculate) {
                    this->taxiCenter->waitForThread();
                    this->finishCalculate = true;
                }
                time++;
                if (this->trip == NULL) {
                    this->trip = this->taxiCenter->getTrips().front();
                    taxiCenter->assignADriverToTrip(trip);
                    this->driver = this->trip->getDriver();
                }
                /*  int numberOfThreads = this->taxiCenter->getTrips().size();
                  while (numberOfThreads > 0) {

                  }*/
                taxiCenter->timePassed(time);
                this->numberOfCase = 9;
                break;

            default:
                break;
        }
        cin >> input;
    }
    ///
    this->numberOfCase = 7;
    Driver *driver = this->taxiCenter->getDrivers().front();
    while (this->taxiCenter->getDrivers().size() > 0) {
        for (int i = 0; i < 100; i++) {
            if (driver->getId() == i) {
                if (this->ports[i] != -1) {
                    driver->setLocation();
                    this->sendDriver(driver, this->ports[driver->getId()]);
                    this->taxiCenter->deleteFirstDriver();
                    delete driver;
                    driver = this->taxiCenter->getDrivers().front();
                }
                break;
            }
        }
    }
    cout << "before finish" << endl;
    return;
}

// add static function
void *MainFlow::handelThread(void *mainFlow1) {
    MainFlow *mainFlow = (MainFlow *) mainFlow1;
    int cabId = 0;
    cout << "before accept" << endl;
    int port = mainFlow->socket->acceptDescriptorCommunicate();
    cout << "Succuss with the connection with the client" << endl;
    char buffer[4096];
    Driver *driver1;
    mainFlow->socket->reciveData(buffer, sizeof(buffer), port);
    char *end = buffer + 4095;
    basic_array_source<char> device(buffer, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char>> s2(device);
    binary_iarchive ia(s2);
    ia >> driver1;
    AbstractNode *node = mainFlow->taxiCenter->getNode(0, 0);
    delete driver1->getLocation();
    delete driver1->getBFS();
    driver1->setLocation2(node);
    cout << "after accept" << endl;
    pthread_mutex_lock(&lock);
    driver1->setBFS(mainFlow->taxiCenter->getBFS());
    mainFlow->taxiCenter->addDriver(driver1);
    mainFlow->taxiCenter->assignCabToDriver(cabId, driver1->getId());
    mainFlow->ports[driver1->getId()] = port;
    mainFlow->sendCab(driver1->getTaxi(), port);
    AbstractNode *currentPoint = driver1->getLocation();
    pthread_mutex_unlock(&lock);
    while (true) { //the conection between the server and the client
        if (mainFlow->numberOfCase == 7) { // close conection
            break;
        }
        if (!currentPoint->operator==(*driver1->getLocation())) {
            mainFlow->sendDriver(driver1, port);
            cout << *driver1->getLocation() << endl;
            currentPoint = driver1->getLocation();

        }
    }
}
//

/*
 * get the driver from the client
 */
void MainFlow::addDriver(int num) {
    int i = 0;
    while (num > 0) {
        pthread_t pthread;
        pthread_create(&pthread, NULL, handelThread, (void *) this);
        this->threads[i] = pthread;
        i++;
        // pthread_join(pthread, NULL);
        num -= 1;
    }
}

/*
 * send the new location of the driver to the client
 */
void MainFlow::sendDriver(Driver *driver, int descriptor) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << driver;
    s.flush();
    this->socket->sendData(serial_str, descriptor);
}

/*
 * send the cab of the driver to the client
 */
void MainFlow::sendCab(AbstractCab *cab, int descriptor) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << cab;
    s.flush();
    this->socket->sendData(serial_str, descriptor);
    numberOfDrivers++;
}

/*
 * send the trip the driver have now
 */
void MainFlow::sendTrip(Trip *trip, int descriptor) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << trip;
    s.flush();
    this->socket->sendData(serial_str, descriptor);
}

/**
 * Sends a numerical message to client.
 * @param num message
 */
void MainFlow::sendMessage(int num, int descriptor) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << num;
    s.flush();
    this->socket->sendData(serial_str, descriptor);
}

/**
 * @param c char representing a MartialStatus
 * @return Martial status based on c.
 */
MartialStatus MainFlow::getStatusByChar(char c) {
    switch (c) {
        case 'S':
            return MartialStatus::S;
        case 'M':
            return MartialStatus::M;
        case 'W':
            return MartialStatus::W;
        case 'D':
            return MartialStatus::D;
        default:
            return MartialStatus::S;
    }
}

/**
 * @param c char representing a CarManufactorer
 * @return The CarManufactur value of c.
 */
CarManufactur MainFlow::getManuByChar(char c) {
    switch (c) {
        case 'S':
            return CarManufactur::S;
        case 'H':
            return CarManufactur::H;
        case 'F':
            return CarManufactur::F;
        case 'T':
            return CarManufactur::T;
        default:
            return CarManufactur::S;
    }
}

/**
 * @param c char representing a CarColor
 * @return The CarColor value of c.
 */
CarColor MainFlow::getColorByChar(char c) {
    switch (c) {
        case 'R':
            return CarColor::R;
        case 'B':
            return CarColor::B;
        case 'W':
            return CarColor::W;
        case 'G':
            return CarColor::G;
        default:
            return CarColor::P;
    }
}


