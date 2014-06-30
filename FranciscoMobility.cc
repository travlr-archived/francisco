#include "FranciscoMobility.h"
#include <WaveShortMessage_m.h>
#include <TraCIConstants.h>
#include <TraCICoord.h>
#include <Coord.h>
#include <utility>
#include <algorithm>

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;


FranciscoMobility::FranciscoMobility(Veins::TraCIMobility* traci)
    : traci(traci)
{
    ASSERT(traci);

    annotationManager = AnnotationManagerAccess().getIfExists();
    ASSERT(annotationManager);

    // junction ids
    Veins::TraCICommandInterface* ci = traci->getCommandInterface();
    ASSERT(ci);

    std::list<std::string> l = ci->getJunctionIds();
    std::vector<std::string> v;
    std::copy( v.begin(), v.end(), std::back_inserter(l) );
    junctionIds = v;

    // vehicle ids
    vehicleIds = getVehicleIds();

    // junction coords
    for (uint32 i = 0; i < junctionIds.size(); ++i) {
        Junction* j = new Junction(junctionIds[i], this);
        junctionObjs[junctionIds[i]] = j;
    }

}


FranciscoMobility::~FranciscoMobility()
{
    for (uint i = 0; i < junctionIds.size(); ++i) {
        delete junctionObjs[junctionIds[i]];
    }
}


std::string FranciscoMobility::getRoadId()
{
    return traci->getRoadId();
}

void FranciscoMobility::commandChangeRoute(std::string roadId, double travelTime)
{
    traci->commandChangeRoute(roadId, travelTime);
}

Coord FranciscoMobility::getJunctionPosition(string junctionId)
{
    return *(junctionObjs[junctionId]->getCoord());
}

Coord FranciscoMobility::getVehiclePosition(string vehicleId)
{
    Veins::TraCICoord tc(traci->getCommandInterface()->getVehiclePosition(vehicleId));
    return Coord(tc.x, tc.y);
}


vector<std::string> FranciscoMobility::getJunctionNeighbors(const Coord & coord, double threshold)
{
    vector<std::string> junctionNeighbors;

    for (uint i = 0; i < junctionIds.size(); ++i) {
        Junction* otherJ = junctionObjs[junctionIds[i]];

        if (coord.distance(*(otherJ->getCoord())) < threshold)
            junctionNeighbors.push_back(otherJ->getId());
    }
    return junctionNeighbors;
}


Coord FranciscoMobility::getPositionAt(const simtime_t & time) const
{
    return traci->getPositionAt(simTime());
}



vector<string> FranciscoMobility::getVehicleIds()
{
    //std::vector<T> v{ std::begin(l), std::end(l) };
    std::list<std::string> l = traci->getCommandInterface()->getVehicleIds();
    vector<std::string> v;
    std::copy(v.begin(), v.end(), std::back_inserter(l));
    return v;
}

static
bool sortDistancePairsHelper(std::pair<std::string,double> a, std::pair<std::string,double> b) {

    return a.second < b.second;
}

bool FranciscoMobility::isClosestToJunction(std::string vehicleId, std::string junctionId, vector<std::string> neighborIds)
{
    Coord jpos = getJunctionPosition(junctionId);
    vector<pair<std::string, double> > distancePairs;

    for (uint i = 0; i < neighborIds.size(); ++i) {

        double d = jpos.distance(getVehiclePosition(neighborIds[i]));

        distancePairs.push_back(std::make_pair(neighborIds[i], d));
    }
    std::sort(distancePairs.begin(), distancePairs.end(), sortDistancePairsHelper);

    std::string idOfClosestVehicle = distancePairs[0].first;

    if (!strcmp(idOfClosestVehicle.c_str(), vehicleId.c_str()))
        return true;

    return false;
}



















