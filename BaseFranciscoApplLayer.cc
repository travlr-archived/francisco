#include "BaseFranciscoApplLayer.h"
#include "AnnotationManager.h"
#include <TraCIConstants.h>
#include <TraCICoord.h>

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;


Define_Module(BaseFranciscoApplLayer);


void BaseFranciscoApplLayer::initialize(int stage)
{
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        cModule* parentModule = getParentModule();
        ASSERT(parentModule);
        traci = TraCIMobilityAccess().get(parentModule);

        franciscoMobility = new FranciscoMobility(traci);
        ASSERT(franciscoMobility);
        annotationManager = AnnotationManagerAccess().getIfExists();
        ASSERT(annotationManager);

        sentMessage = false;
        lastDroveAt = simTime();
    }
}

void BaseFranciscoApplLayer::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj)
{
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal)
        handlePositionUpdate(obj);
}

void BaseFranciscoApplLayer::finish()
{
    BaseWaveApplLayer::finish();
    delete franciscoMobility;
}

void BaseFranciscoApplLayer::onBeacon(WaveShortMessage *wsm)
{

}

void BaseFranciscoApplLayer::onData(WaveShortMessage *wsm)
{

}



void BaseFranciscoApplLayer::sendWarningMessage(std::string blockedRoadId)
{
    sentMessage = true;

    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    WaveShortMessage* wsm = prepareWSM("data", dataLengthBits, channel, dataPriority, -1, 2);
    wsm->setWsmData(blockedRoadId.c_str());
    sendWSM(wsm);
}

void BaseFranciscoApplLayer::handlePositionUpdate(cObject *obj)
{
    if (traci->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10) {
            findHost()->getDisplayString().updateWith("r=16,red");
            if (!sentMessage)
                sendWarningMessage(traci->getRoadId());
        }
    }
    else
        lastDroveAt = simTime();
}

void BaseFranciscoApplLayer::sendWSM(WaveShortMessage *wsm)
{
    sendDelayedDown(wsm, individualOffset);
}




