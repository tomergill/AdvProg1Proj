#include "MainFlow.h"
#include "Udp.h"

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;
using namespace boost::iostreams;

/*
 * c-tor of main flow
 */
MainFlow::MainFlow(MapFactory *factory) {
    mapFactory = factory;
    taxiCenter = NULL;
    time = 0;
    this->socket = new Udp(1, 12345);
    this->trip = NULL;
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
                cin >> numOfDrivers;
                this->addDriver(numOfDrivers);
                break;

            case 2: //New Trip
                cin >> rideId >> dummy >> start_x >> dummy >> start_y >> dummy
                    >> end_x >> dummy >> end_y >> dummy >> pass_num >> dummy
                    >> tariff >> dummy >> time1;
                taxiCenter->answerCall(rideId, new Point(start_x, start_y),
                                       new Point(end_x, end_y), tariff,
                                       pass_num, time1);
                break;
            case 3: //New Cab
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
                cin >> driverId;
                taxiCenter->printDriverLocation(driverId);
                break;
            case 9: //move trips
                time++;
                //this->driver = this->taxiCenter->getDrivers().front();
                if (this->trip == NULL) {
                    this->trip = this->taxiCenter->getTrips().front();
                    this->trip->setDriver(NULL);
                    //this->sendTrip(this->trip);
                    taxiCenter->assignADriverToTrip(trip);
                }
                //this->trip->setDriver(this->driver);
                taxiCenter->timePassed(time);
                //this->sendDriver(this->driver);

            default:
                break;
        }
        cin >> input;
    }
    //this->driver->setLocation();
    //this->sendDriver(this->driver);
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

void MainFlow::addDriver(int num) {
    while (num > 0) {
        int input, driverId = 0, age = 0, experience = 0, cabId = 0, start_x = 0,
                start_y = 0, end_x = 0, end_y = 0, pass_num = 0, rideId = 0,
                taxi_type = 1, time1 = 0;
        MartialStatus status = MartialStatus::S;
        double tariff = 0.0;
        CarColor color = CarColor::R;
        CarManufactur manufactur = CarManufactur::F;
        char dummy = ',', mstatus, cColor, manu;
        //Udp udp(1, 12345);
        this->socket->initialize();

        char buffer[4096];
        Driver *gp2;
        // FactoryCab factoryCab;
        // Cab* gp2;
        this->socket->reciveData(buffer, sizeof(buffer));
        char *end = buffer + 4095;
        basic_array_source<char> device(buffer, end);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        binary_iarchive ia(s2);
        ia >> gp2;
        taxiCenter->addDriver(gp2);
        taxiCenter->assignCabToDriver(cabId, gp2->getId());
        this->sendCab(gp2->getTaxi());
        num -= 1;
    }
}

void MainFlow::sendDriver(Driver *driver) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    binary_oarchive oa(s);
    oa << driver;
    s.flush();
    this->socket->sendData(serial_str);
}

void MainFlow::sendCab(AbstractCab *cab) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    binary_oarchive oa(s);
    oa << cab;
    s.flush();
    this->socket->sendData(serial_str);
}

void MainFlow::sendTrip(Trip *trip) {
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    binary_oarchive oa(s);
    oa << trip;
    s.flush();
    this->socket->sendData(serial_str);
}
