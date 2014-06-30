#ifndef DvcastApplLayer_H
#define DvcastApplLayer_H

#include "BaseFranciscoApplLayer.h"


class DvcastApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // DvcastApplLayer_H
