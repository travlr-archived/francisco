#ifndef EmdrApplLayer_H
#define EmdrApplLayer_H

#include "BaseFranciscoApplLayer.h"


class EmdrApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

};

#endif // EmdrApplLayer_H
