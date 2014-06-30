#ifndef COUNTERAPPLLAYER_H
#define COUNTERAPPLLAYER_H

#include "BaseFranciscoApplLayer.h"


class CounterApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // COUNTERAPPLLAYER_H
