#ifndef NSFAPPLLAYER_H_
#define NSFAPPLLAYER_H_

#include "BaseModule.h"
#include <BaseWaveApplLayer.h>
#include "mobility/traci/TraCIMobility.h"
#include <vector>

#ifndef DBG
#define DBG EV
#endif

#define MAX_NEIGHBORS 1000


class NsfApplLayer  :  public BaseWaveApplLayer {
    public:

        virtual ~NsfApplLayer();

        virtual void initialize(int stage);

    protected:
        virtual void onBeacon(WaveShortMessage* wsm);
        virtual void onData(WaveShortMessage* wsm);
        void removeNeighbor(WaveShortMessage* neighborsToRemove, uint32_t numToRemove);
        void sendMessage(WaveShortMessage *wsm);
        void sendMessage(std::string blockedRoadId);
        virtual void handlePositionUpdate(cObject* obj);

    protected:
        uint32_t receivedBeacons;
        uint32_t receivedData;
        std::vector<WaveShortMessage*> neighbors;
        std::vector<WaveShortMessage*> warnings;
        double sendInterval;
        WaveShortMessage* generatedWarningMessage;
        TraCIMobility* traci;
        AnnotationManager* annotations;
        simtime_t lastDroveAt;
        bool sentMessage;
};

#endif /* NSFAPPLLAYER_H_ */
