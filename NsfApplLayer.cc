
#include "NsfApplLayer.h"
#include <TraCIScenarioManager.h>
#include <simtime.h>

Define_Module(NsfApplLayer);

void NsfApplLayer::initialize(int stage) {

    BaseFranciscoApplLayer::initialize(stage);

}


void NsfApplLayer::onBeacon(WaveShortMessage* wsm) {

    bool isNewNeighbor = true;
    std::vector<int> removableIndices;

    for (uint32_t i = 0; i < neighborMsgs.size(); ++i) {

        WaveShortMessage* n = neighborMsgs[i];

        if (simTime() > (n->getTimestamp() + SimTime(2, 0)))
            removableIndices.push_back(i);

        if (n == wsm) {
            isNewNeighbor = false;
        }
    }
    for (uint32_t i = 0; i < removableIndices.size(); ++i) {
        neighborMsgs.erase(neighborMsgs.begin() + removableIndices[i]);
    }
    if (isNewNeighbor) {
        neighborMsgs.push_back(wsm);
        EV << "[INFO] IS NEW NEIGHBOR: " << wsm->getSenderAddress() << endl;
        for (uint32_t i = 0; i < warningMsgs.size(); ++i ) {
            WaveShortMessage w(*(warningMsgs[i]));
            w.setSenderAddress(wsm->getSenderAddress());
            sendWSM(&w);
        }
    }
}

void NsfApplLayer::onData(WaveShortMessage* wsm) {

    if (neighborMsgs.size() > 1) {

        sendWSM(wsm);
    }

    warningMsgs.push_back(wsm);
}






























































