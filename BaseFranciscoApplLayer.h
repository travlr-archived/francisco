#ifndef BaseFranciscoApplLayer_H
#define BaseFranciscoApplLayer_H

#include <BaseWaveApplLayer.h>
#include <TraCIScenarioManager.h>
#include <AnnotationManager.h>
#include "FranciscoMobility.h"
#include <vector>


using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;
using namespace std;

class BaseFranciscoApplLayer : public BaseWaveApplLayer
{

public:
    virtual void initialize(int stage);
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);
    virtual void finish();

protected:

    simtime_t lastDroveAt;
    bool sentMessage;
    FranciscoMobility* franciscoMobility;
    Veins::AnnotationManager* annotationManager;

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);
    void sendWarningMessage(std::string blockedRoadId);
    virtual void handlePositionUpdate(cObject* obj);
    virtual void sendWSM(WaveShortMessage* wsm);

protected:
    Veins::TraCIMobility* traci;




};

#endif // BaseFranciscoApplLayer_H
