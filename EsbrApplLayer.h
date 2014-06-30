#ifndef EsbrApplLayer_H
#define EsbrApplLayer_H

#include "BaseFranciscoApplLayer.h"


class EsbrApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // EsbrApplLayer_H
