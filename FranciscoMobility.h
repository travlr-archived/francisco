#ifndef FRANCISCOMOBILITY_H
#define FRANCISCOMOBILITY_H

#include <TraCIMobility.h>
#include <TraCICoord.h>
#include <Coord.h>
#include <list>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Junction;
class WaveShortMessage;

class FranciscoMobility
{
public:
    FranciscoMobility(Veins::TraCIMobility* traci);
    ~FranciscoMobility();

    std::string getRoadId();
    Coord getPositionAt(const simtime_t &time) const;  // traci->getPositionAt(simTime())
    void commandChangeRoute(std::string roadId, double travelTime);
    Coord getJunctionPosition(std::string junctionId);
    Coord getVehiclePosition(std::string vehicleId);
    vector<std::string> getJunctionNeighbors(const Coord &coord, double threshold);
    Veins::TraCIMobility* getTraci() { return traci; }
    vector<std::string> getVehicleIds();
    bool isClosestToJunction(string vehicleId, string junctionId, vector<string> neighborIds);

private:
    vector<std::string> vehicleIds;
    vector<std::string> junctionIds;
    map<std::string, Junction*> junctionObjs;
    Veins::TraCIMobility* traci;
    Veins::AnnotationManager* annotationManager;


private:



};


class Junction {

public:
    Junction(std::string id, FranciscoMobility* fm) : id(id)
    {
        traci = fm->getTraci();
        coord = new Coord(fm->getJunctionPosition(id));
    }

    ~Junction()
    {
        delete this->coord;
    }

    Coord* getCoord() { return coord; }
    std::string getId() { return id; }


protected:
    std::string id;
    std::string closestVehicleId;
    Veins::TraCICoord traciCoord;
    Coord* coord;
    Veins::TraCIMobility* traci;
    map<std::string, Coord> vehicleCoordsMap;
    double distanceFromLastWarningHost;
    map<std::string, Junction*> neighborJunctions;

};

#endif // FRANCISCOMOBILITY_H
