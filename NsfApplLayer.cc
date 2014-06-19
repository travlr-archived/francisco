
#include "NsfApplLayer.h"

Define_Module(NsfApplLayer);

void NsfApplLayer::initialize(int stage) {
	BaseWaveApplLayer::initialize(stage);
	receivedBeacons = 0;
	receivedData = 0;
}

void NsfApplLayer::onBeacon(WaveShortMessage* wsm) {
	receivedBeacons++;

	DBG << "Received beacon priority  " << wsm->getPriority() << " at " << simTime() << std::endl;
	int senderId = wsm->getSenderAddress();

	if (sendData) {
		t_channel channel = dataOnSch ? type_SCH : type_CCH;
		sendWSM(prepareWSM("data", dataLengthBits, channel, dataPriority, senderId,2));
	}
}

void NsfApplLayer::onData(WaveShortMessage* wsm) {

	int recipientId = wsm->getRecipientAddress();

	if (recipientId == myId) {
		DBG  << "Received data priority  " << wsm->getPriority() << " at " << simTime() << std::endl;
		receivedData++;
	}
}

NsfApplLayer::~NsfApplLayer() {

}
