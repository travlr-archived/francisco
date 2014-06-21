
#include "NsfApplLayer.h"

Define_Module(NsfApplLayer);

void NsfApplLayer::initialize(int stage) {

	BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        receivedBeacons = 0;
        receivedData = 0;
        sendInterval = par("sendInterval").doubleValue();
        sendData = true;
        dataOnSch = false;
        traci = TraCIMobilityAccess().get(getParentModule());
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);
        sentMessage = false;
        lastDroveAt = simTime();
    }
}


void NsfApplLayer::onBeacon(WaveShortMessage* wsm) {

	receivedBeacons++;

	bool isNewNeighbor = true;
	std::vector<int> removableIndices;

	for (uint32_t i = 0; i < neighbors.size(); ++i) {

	    WaveShortMessage* n = neighbors[i];

	    if (n == wsm) {
	        isNewNeighbor = false;
	    }
	}
	for (uint32_t i = 0; i < removableIndices.size(); ++i) {
	    neighbors.erase(neighbors.begin() + removableIndices[i]);
	}
	if (isNewNeighbor) {
	    neighbors.push_back(wsm);
	    EV << "[INFO] IS NEW NEIGHBOR: " << wsm->getSenderAddress() << endl;
	    for (uint32_t i = 0; i < warnings.size(); ++i ) {
	        WaveShortMessage* w = warnings[i];
            w->setSenderAddress(wsm->getSenderAddress());
            sendMessage(w);
	    }
	}
}

void NsfApplLayer::onData(WaveShortMessage* wsm) {

    receivedData++;


//	if (neighbors.size()) {
//	    sendWSM(wsm);
//	    warnings.push_back(wsm);
//	}
//}


    findHost()->getDisplayString().updateWith("r=16,green");
    annotations->scheduleErase(1, annotations->drawLine(wsm->getSenderPos(), traci->getPositionAt(simTime()), "blue"));

    if (traci->getRoadId()[0] != ':')
        traci->commandChangeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage)
        sendMessage(wsm);
}

void NsfApplLayer::sendMessage(/*std::string blockedRoadId*/WaveShortMessage* wsm) {

    sendMessage(wsm->getWsmData());
}

void NsfApplLayer::sendMessage(std::string blockedRoadId)
{
    sentMessage = true;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    WaveShortMessage* newWsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1, 2);
    newWsm->setWsmData(blockedRoadId.c_str());
    sendWSM(newWsm);
}


void NsfApplLayer::handlePositionUpdate(cObject *obj) {

    BaseWaveApplLayer::handlePositionUpdate(obj);

    // stopped for at least 10s?

    if (traci->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10) {
            findHost()->getDisplayString().updateWith("r=16,red");
            if (!sentMessage)
                sendMessage(traci->getRoadId());
        }
    }
    else {
        lastDroveAt = simTime();
    }
}

NsfApplLayer::~NsfApplLayer() {


}





























































