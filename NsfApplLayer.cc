#include "NsfApplLayer.h"

const simsignalwrap_t NsfApplLayer::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);

void NsfApplLayer::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    if (stage==0) {
        myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(
                    getParentModule());
        assert(myMac);

        myId = getParentModule()->getIndex();

        headerLength = par("headerLength").longValue();
        double maxOffset = par("maxOffset").doubleValue();
        sendBeacons = par("sendBeacons").boolValue();
        beaconLengthBits = par("beaconLengthBits").longValue();
        beaconPriority = par("beaconPriority").longValue();

        sendData = par("sendData").boolValue();
        dataLengthBits = par("dataLengthBits").longValue();
        dataOnSch = par("dataOnSch").boolValue();
        dataPriority = par("dataPriority").longValue();

        sendBeaconEvt = new cMessage("beacon evt", SEND_BEACON_EVT);

        //simulate asynchronous channel access
        double offSet = dblrand() * (par("beaconInterval").doubleValue()/2);
        offSet = offSet + floor(offSet/0.050)*0.050;
        individualOffset = dblrand() * maxOffset;

        findHost()->subscribe(mobilityStateChangedSignal, this);

        if (sendBeacons) {
            scheduleAt(simTime() + offSet, sendBeaconEvt);
        }

    }
}

WaveShortMessage*  NsfApplLayer::prepareWSM(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial) {
    WaveShortMessage* wsm =     new WaveShortMessage(name.c_str());
    wsm->addBitLength(headerLength);
    wsm->addBitLength(lengthBits);

    switch (channel) {
        case type_SCH: wsm->setChannelNumber(Channels::SCH1); break; //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        case type_CCH: wsm->setChannelNumber(Channels::CCH); break;
    }
    wsm->setPsid(0);
    wsm->setPriority(priority);
    wsm->setWsmVersion(1);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(rcvId);
    wsm->setSenderPos(curPosition);
    wsm->setSerial(serial);

    if (name == "beacon") {
        DBG << "Creating Beacon with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
    }
    if (name == "data") {
        DBG << "Creating Data with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
    }

    return wsm;
}

void NsfApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
}

void NsfApplLayer::handlePositionUpdate(cObject* obj) {
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getCurrentPosition();
}

void NsfApplLayer::handleLowerMsg(cMessage* msg) {

    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);

    if (std::string(wsm->getName()) == "beacon") {
        onBeacon(wsm);
    }
    else if (std::string(wsm->getName()) == "data") {
        onData(wsm);
    }
    else {
        DBG << "unknown message (" << wsm->getName() << ")  received\n";
    }
    delete(msg);
}

void NsfApplLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
        case SEND_BEACON_EVT: {
            sendWSM(prepareWSM("beacon", beaconLengthBits, type_CCH, beaconPriority, 0, -1));
            scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
            break;
        }
        default: {
            if (msg)
                DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

void NsfApplLayer::sendWSM(WaveShortMessage* wsm) {
    sendDelayedDown(wsm,individualOffset);
}

void NsfApplLayer::finish() {
    if (sendBeaconEvt->isScheduled()) {
        cancelAndDelete(sendBeaconEvt);
    }
    else {
        delete sendBeaconEvt;
    }

    findHost()->unsubscribe(mobilityStateChangedSignal, this);

}

NsfApplLayer::~NsfApplLayer() {

}
