#ifndef DistanceApplLayer_H
#define DistanceApplLayer_H

#include "BaseFranciscoApplLayer.h"


class DistanceApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // DistanceApplLayer_H
