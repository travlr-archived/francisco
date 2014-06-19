#ifndef NSFAPPLLAYER_H_
#define NSFAPPLLAYER_H_

#include "BaseModule.h"
#include <BaseWaveApplLayer.h>

#ifndef DBG
#define DBG EV
#endif

class NsfApplLayer  :  public BaseWaveApplLayer {
    public:

        virtual ~NsfApplLayer();

        virtual void initialize(int stage);

    protected:
        virtual void onBeacon(WaveShortMessage* wsm);
        virtual void onData(WaveShortMessage* wsm);

    protected:
        uint32_t receivedBeacons;
        uint32_t receivedData;

};

#endif /* NSFAPPLLAYER_H_ */
