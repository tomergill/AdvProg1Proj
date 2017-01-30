#include "MainFlow.h"
#include "Udp.h"
#include "Tcp.h"
#include "MatrixMap.h"
#include <boost/regex.hpp>
//#include "../easylogging++.h"
//he'ara

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_t pthread1;
pthread_t pthread2;
int numberOfDrivers = 0;
int numberOfClients = 0;
bool was9 = false;
int closeConections = 0;

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
    this->numberOfCase = -1;
    this->socket->initialize();
    this->finishCalculate = false;

}

/*
 * start the taxi center
 */
void MainFlow::startFlow() { ;
    int obsNum, i, h, w, j;
    char dummy;
    string matrixInput, obstacle;
    Map *map = NULL;
    bool cont = false;
    boost::regex mapSizes(" *([0-9])+ ([0-9])+"), number("[0-9]+"),
            obstacleregex("[0-9]+,[0-9]+");

    while (map == NULL) {
        getline(cin, matrixInput); //matrix size
//        cout << '"' << matrixInput << '"' << endl;
        if (!boost::regex_match(matrixInput, mapSizes))
        {
            cout << "-1" << endl;
//            cout << "ERROR regex map sizes not match" << endl;
            continue;
        }
        stringstream s(matrixInput);
        //s >> h >> /*dummy >>*/ w /*>> dummy*/;
        if (!(s >> h >> w && s.eof()))
        {
            cout << "-1" << endl;
//            cout << "ERROR parsing" << endl;
            continue;
        }
        if (h < 1)
        {
            cout << "-1" << endl;
//            cout << "height less than 1" << endl;
            continue;
        }
        if (w < 1)
        {
            cout << "-1" << endl;
//            cout << "width less than 1" << endl;
            continue;
        }
        getline(cin, obstacle);
//        cout << '"' << obstacle << '"' << endl;
//        if (!isStringAnInteger(obstacle))
//        {
//            cout << "-1" <<endl;
//            cout << "obstacle not int" << endl;
//            continue;
//        }
        if (!boost::regex_match(obstacle, number))
        {
            cout << "-1" << endl;
//            cout << "ERROR regex obstacle number not match" << endl;
            continue;
        }
        obsNum = atoi(&obstacle[0]);
        if (obsNum < 0 || obsNum >= h * w) {
            cout << "-1" << endl;
//            cout << "wrong obstacle number" << endl;
            continue;
        }
//        getline(cin, obstacle);
//        cout << '"' << obsNum << '"' << endl;
        for (i = 0; i < obsNum; ++i) { //receiving obstacles
            getline(cin, obstacle);
//            cout << '"' << obstacle << '"' << endl;
            if (!boost::regex_match(obstacle, obstacleregex))
            {
                cout << "-1" << endl;
//                cout << "ERROR obstacle wrong" << endl;
                cont = true;
                break;
            }
            matrixInput += "|" + obstacle;
        }
        if (cont)
        {
            cont = false;
            continue;
        }
        map = mapFactory->buildMap(matrixInput);
        if (map == NULL)
            cout << "-1" << endl;
    }
    taxiCenter = new TaxiCenter(map);
    flow();
}

MainFlow::~MainFlow() {
    delete taxiCenter;
    if (socket != NULL)
        delete socket;
}

/**
 * @return the input for the switch case
 */
int MainFlow::getInput()
{
    string str;
    boost::regex inp("(1|2|3|4|7|9)");
    int i;

    while (true) {
        getline(cin, str);
        stringstream s(str);
        if (!boost::regex_match(str, inp) || !(s >> i && s.eof())) {
            cout << "-1" << endl;
//            cout << "wrong input mission" << endl;
            continue;
        }
        return i;
    }
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
    string inputline = "";
    boost::regex taxi("[0-9]+,(1|2),(H|S|T|F),(R|B|G|P|W)"), number("[0-9]+")
    , tripregex("[0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+,[0-9]+(.[0-9]+)?,[0-9]+");

    input = getInput();
    while (input != 7) {
        //cout << taxiCenter->getTrips().size() << endl;
        switch (input) {
            case 1: //New Driver
            {
                this->numberOfCase = 1;
                getline(cin, inputline);
                stringstream dnumstream(inputline);
                if (!boost::regex_match(inputline, number)
                    || !(dnumstream >> numOfDrivers && dnumstream.eof())
                    || numOfDrivers < 1)
                {
                    cout << "-1" << endl;
                    input = getInput();
                    continue;
                }
//                LINFO << numOfDrivers << endl;
                this->addDriver(numOfDrivers);
                break;
            }
            case 2: //New Trip
            {
                this->numberOfCase = 2;
                getline(cin, inputline);
                stringstream tripstream(inputline);
                if (!boost::regex_match(inputline, tripregex)
                    || !(tripstream >> rideId >> dummy >> start_x >> dummy
                                    >> start_y >> dummy >> end_x >> dummy
                                    >> end_y >> dummy >> pass_num >> dummy
                                    >> tariff >> dummy >> time1
                         && tripstream.eof())) {
                    cout << "-1" << endl;
                    input = getInput();
                    continue;
                }
                MatrixMap *mat = (MatrixMap *)taxiCenter->getMap();
                if (start_x < 0 || start_x >= mat->xlimit()
                    || start_y < 0 || start_y >= mat->ylimit()
                    || end_x < 0 || end_x >= mat->xlimit()
                    || end_y < 0 || end_y >= mat->ylimit()
                    || (start_x == end_x && start_y == end_y)
                    || pass_num < 1 || time1 < 1
                    || !taxiCenter->isFreeTripId(rideId))
                {
                    if (!(start_x == end_x && start_y == end_y))
                        cout << "-1" << endl;
                    input = getInput();
                    continue;
                }
                taxiCenter->answerCall(rideId, new Point(start_x, start_y),
                                       new Point(end_x, end_y), tariff,
                                       pass_num, time1);
                break;
            }
            case 3: //New Cab
            {
                this->numberOfCase = 3;
                getline(cin, inputline);
                if (!boost::regex_match(inputline, taxi)) {
                    cout << "-1" << endl;
//                    cout << "no match regex taxi" << endl;
                    input = getInput();
                    continue;
                }
                stringstream taxistream(inputline);
                //cout << inputline.length() << endl;
                if (!(taxistream >> cabId >> dummy >> taxi_type >> dummy
                                 >> manu >> dummy >> cColor
                     /* && taxistream.eof()*/)
                    || !taxiCenter->isFreeCabId(cabId)) {
                    cout << "-1" << endl;
                    input = getInput();
                    continue;
                }
                manufactur = getManuByChar(manu);
                color = getColorByChar(cColor);
                if (taxi_type == 1)
                    taxiCenter->addTaxi(new Cab(cabId, manufactur, color));
                else
                    taxiCenter->addTaxi(new LuxuryCab(cabId, manufactur,
                                                      color));
                break;
            }
            case 4: //Print driver's location
            {
                this->numberOfCase = 4;
                getline(cin, inputline);
                stringstream s(inputline);
                if (!boost::regex_match(inputline, number) || !(s >> driverId
                                                                && s.eof()))
                {
                    cout << "-1" << endl;
//                    cout << "no match regex taxi" << endl;
                    input = getInput();
                    continue;
                }
                taxiCenter->printDriverLocation(driverId);
                break;
            }
            case 9: //move trips
                was9 = true;
                while (true) {
                    if (numberOfDrivers >= numOfDrivers) {
                        break;
                    }
                }
//                LINFO << "got all drivers" << endl;
//                if (!this->finishCalculate) {
//                    this->taxiCenter->waitForThread();
//                    this->finishCalculate = true;
//                }
                time++;
                taxiCenter->timePassed(time);
                this->numberOfCase = 9;
                break;

            default:
                break;
        }
        input = getInput();
    }
    ///
    this->numberOfCase = 7;
    while (true) {
        if (numberOfDrivers <= closeConections) {
            break;
        }
    }
    Driver *driver = this->taxiCenter->getDrivers().front();
    int size = this->taxiCenter->getDrivers().size();
    while (size > 0) {
        driver->setLocation();
        this->sendDriver(driver, driver->getDescriptor());
        this->taxiCenter->deleteFirstDriver();
        if (this->taxiCenter->getDrivers().size() > 0)
            driver = this->taxiCenter->getDrivers().front();
        size--;
    }
//    LINFO << "before finish" << endl;
    // pthread_exit(NULL);
    return;
}

// add static function
void *MainFlow::handelThread(void *mainFlow1) {
    MainFlow *mainFlow = (MainFlow *) mainFlow1;
//    int cabId = 0;
//    LINFO << "before accept" << endl;
    int port = mainFlow->socket->acceptDescriptorCommunicate();
//    LINFO << "Succuss with the connection with the client" << endl;
    char buffer[4096];
    Driver *driver1 = NULL;
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
//    LINFO << "after accept" << endl;
    pthread_mutex_lock(&lock);
    driver1->setBFS(mainFlow->taxiCenter->getBFS());
    mainFlow->taxiCenter->addDriver(driver1);
    mainFlow->taxiCenter->assignCabToDriver(driver1->getCabId(), driver1->getId());
    driver1->setDescriptor(port);
    mainFlow->sendCab(driver1->getTaxi(), port);
    AbstractNode *currentPoint = driver1->getLocation();
    driver1->setLastPoint(NULL);
    driver1->setClientGotPoint(false);
    pthread_mutex_unlock(&lock);
    while (true) { //the conection between the server and the client
        if (mainFlow->numberOfCase == 7) { // close conection
            if (was9) {
                mainFlow->sendDriver(driver1, port);
            }
            pthread_mutex_lock(&lock3);
            closeConections++;
            pthread_mutex_unlock(&lock3);
            delete driver1;
            break;
        }
        if (!currentPoint->operator==(*driver1->getLocation())) {
            mainFlow->sendDriver(driver1, port);
            currentPoint = driver1->getLocation();

        }
        if (driver1->getLastPoint() != NULL && driver1->getLocation() != NULL) {
            if (driver1->getLocation()->operator==(*driver1->getLastPoint())) {
                driver1->setClientGotPoint(true);
            }
        }
        if (driver1->getClientGotPoint()) {
            numberOfClients++;
            driver1->setClientGotPoint(false);
        }

    }
}


/*
 * get the driver from the client
 */
void MainFlow::addDriver(int num) {
//    LINFO << "in addDriver" << endl;
    while (num > 0) {
        pthread_t pthread;
        pthread_create(&pthread, NULL, handelThread, (void *) this);
        //pthread_join(pthread, NULL);
        //LINFO << "wait for clients first!!!!!" << endl;
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
    /*pthread_mutex_lock(&lock3);
    numberOfClients++;
    pthread_mutex_unlock(&lock3);*/
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
    //  pthread_mutex_lock(&lock2);
    numberOfDrivers++;
    // pthread_mutex_unlock(&lock2);
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

bool MainFlow::allDriversInEndPoint() {
    bool allFinish = true;
    Driver *arr[this->taxiCenter->getDrivers().size()];
    int i = 0;
    int size = this->taxiCenter->getDrivers().size();
    while (i < size) {
        arr[i] = this->taxiCenter->getDrivers().front();
        this->taxiCenter->getDrivers().pop_front();
        i++;
    }
    i = 0;
    while (i < size) {
        if (!arr[i]->getLocation()->operator==(*arr[i]->getLastPoint())) {
            allFinish = false;
        } else {
            arr[i]->setClientGotPoint(true);
        }
        this->taxiCenter->getDrivers().push_back(arr[i]);
        i++;
    }
    return allFinish;
}

/**
 * The function checks of the string is an integer, meaning containing only
 * digits.
 * @param s string to be checked
 * @return true if integer, false otherwise
 */
bool MainFlow::isStringAnInteger(string s)
{
    int i;
    for (i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

