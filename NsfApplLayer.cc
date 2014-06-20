
#include "NsfApplLayer.h"

Define_Module(NsfApplLayer);

void NsfApplLayer::initialize(int stage) {
	BaseWaveApplLayer::initialize(stage);
	receivedBeacons = 0;
	receivedData = 0;
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
	        sendWSM(warnings[i]);
	    }
	}
}

void NsfApplLayer::onData(WaveShortMessage* wsm) {

	int recipientId = wsm->getRecipientAddress();

	if (recipientId == myId) {
//		DBG  << "Received data priority  " << wsm->getPriority() << " at " << simTime() << std::endl;
	    EV << "....................ON_DATA.........................";
		receivedData++;
	}

	if (neighbors.size()) {
	    sendWSM(wsm);
	    warnings.push_back(wsm);
	}
}



NsfApplLayer::~NsfApplLayer() {

}





























































