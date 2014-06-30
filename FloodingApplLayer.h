#ifndef FloodingApplLayer_H
#define FloodingApplLayer_H

#include "BaseFranciscoApplLayer.h"


class FloodingApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // FloodingApplLayer_H
