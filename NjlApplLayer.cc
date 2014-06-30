
#include "NjlApplLayer.h"
#include <WaveShortMessage_m.h>
#include <cstdio>


Define_Module(NjlApplLayer)

void NjlApplLayer::initialize(int stage)
{

    BaseFranciscoApplLayer::initialize(stage);

    // junctionDistanceThreshold = par("junctionDistanceThreshold").doubleValue();

    junctionDistanceThreshold = 0;


}


void NjlApplLayer::onBeacon(WaveShortMessage *wsm)
{

    bool isNewNeighbor = true;
    std::vector<int> removableIndices;

    for (uint32_t i = 0; i < neighborMsgs.size(); ++i) {

        if (simTime() > (neighborMsgs[i]->getTimestamp() + SimTime(2, 0)))
            removableIndices.push_back(i);

        WaveShortMessage* n = neighborMsgs[i];

        if (n == wsm) {
            isNewNeighbor = false;
        }
    }

    for (uint32_t i = 0; i < removableIndices.size(); ++i) {

        neighborMsgs.erase(neighborMsgs.begin() + removableIndices[i]);
    }

    if (isNewNeighbor) {

        neighborMsgs.push_back(wsm);
        char s[32];
        sprintf(s, "%d", wsm->getSenderAddress());

        neighborIds.push_back(std::string(s));
        // the junction distance threshold.
        char vehicleId[32];
        sprintf(vehicleId, "%d", wsm->getSenderAddress());
        double distance = franciscoMobility->getPositionAt(simTime()).distance(franciscoMobility->getVehiclePosition(vehicleId));

        if (distance > junctionDistanceThreshold)

            junctionDistanceThreshold = distance;
    }
}


void NjlApplLayer::onData(WaveShortMessage *wsm)
{

    for (uint i = 0; i < hotWSMs.size(); ++i) {

        if (wsm->getSenderAddress() == hotWSMs[i]->getSenderAddress())
            hotWSMRepeatIndices.push_back(i);
    }

    Coord position = franciscoMobility->getPositionAt(simTime());

    findHost()->getDisplayString().updateWith("r=16,green");
    annotationManager->scheduleErase(1, annotationManager->drawLine(wsm->getSenderPos(), position, "blue"));

    if (franciscoMobility->getRoadId()[0] != ':')
        franciscoMobility->commandChangeRoute(wsm->getWsmData(), 9999);

    vector<std::string> junctionNeighbors = franciscoMobility->getJunctionNeighbors(position, junctionDistanceThreshold);

    for (uint i = 0; i < junctionNeighbors.size(); ++i) {
        char idStr[32];
        sprintf(idStr, "%d", traci->getId());
        if (franciscoMobility->isClosestToJunction(idStr, junctionNeighbors[i], neighborIds)) {
            sendWSM(wsm);
        }
        else {
            cMessage* m = new cMessage("rebroadcast", SEND_REBROADCAST_EVENT);
            scheduleAt(simTime() + par("reBroadcastInterval").doubleValue(), m);
        }
    }
}


void NjlApplLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {

    case SEND_BEACON_EVT:
        sendWSM(prepareWSM("beacon", beaconLengthBits, type_CCH, beaconPriority, 0, -1));
        scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
        break;

    case SEND_REBROADCAST_EVENT:
        for (uint i = 0; i < hotWSMs.size(); ++i) {

            bool msgRebroadcasted = false;

            if (hotWSMs[i]->getTimestamp() + 2 < simTime()) {
                for (uint j = 0; j < hotWSMRepeatIndices.size(); ++j) {
                    if ((uint)hotWSMRepeatIndices[j] == i) {
                        msgRebroadcasted = true;
                    }
                }
            }

            if (!msgRebroadcasted)
                sendWSM(hotWSMs[i]);

        }


    default:
            if (msg)
                DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
    }
}
