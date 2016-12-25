
#include "MainFlow.h"
#include "MatrixMap.h"

/*
 * c-tor of main flow
 */
MainFlow::MainFlow(MapFactory *factory) {
    mapFactory = factory;
    taxiCenter = NULL;
}

/*
 * start the taxi center
 */
void MainFlow::startFlow(string mapInput) {
    taxiCenter = new TaxiCenter(mapFactory->buildMap(mapInput));
    flow();
}
MainFlow::~MainFlow(){
delete taxiCenter;
}
/*
 * run the program
 */
void MainFlow::flow() {
    int input, driverId = 0, age = 0, experience = 0, cabId = 0, start_x = 0,
            start_y = 0, end_x = 0, end_y = 0, pass_num = 0, rideId = 0,
            taxi_type = 1;
    MartialStatus status = S;
    double tariff = 0.0;
    CarColor color = CarColor::R;
    CarManufactur manufactur = CarManufactur::F;
    char dummy = ',', mstatus, cColor, manu;

    cin >> input;
    while (input != 7) {
        switch (input) {
            case 1: //New Driver
                cin >> driverId >> dummy >> age >> dummy >> mstatus >> dummy
                    >> experience >> dummy >> cabId;
                status = getStatusByChar(mstatus);
                taxiCenter->addDriver(driverId, age, status);
                taxiCenter->assignCabToDriver(cabId, driverId);
                break;

            case 2: //New Trip
                cin >> rideId >> dummy >> start_x >> dummy >> start_y >> dummy
                    >> end_x >> dummy >> end_y >> dummy >> pass_num >> dummy
                    >> tariff;
                taxiCenter->answerCall(rideId, new Point(start_x, start_y),
                                       new Point(end_x, end_y), tariff,
                                       pass_num);
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
            case 6: //move all trips
                taxiCenter->moveAllTrips();
            default:
                break;
        }
        cin >> input;
    }
}

/**
 * @param c char representing a MartialStatus
 * @return Martial status based on c.
 */
MartialStatus MainFlow::getStatusByChar(char c) {
    switch (c) {
        case 'S':
            return S;
        case 'M':
            return M;
        case 'W':
            return W;
        case 'D':
            return D;
        default:
            return S;
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