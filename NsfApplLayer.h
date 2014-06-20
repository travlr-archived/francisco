#ifndef NSFAPPLLAYER_H_
#define NSFAPPLLAYER_H_

#include "BaseModule.h"
#include <BaseWaveApplLayer.h>
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

    protected:
        uint32_t receivedBeacons;
        uint32_t receivedData;
        std::vector<WaveShortMessage*> neighbors;
        std::vector<WaveShortMessage*> warnings;
        double sendInterval = par("sendInterval");
};

#endif /* NSFAPPLLAYER_H_ */
