#ifndef NsfApplLayer_H
#define NsfApplLayer_H

#include "BaseFranciscoApplLayer.h"


class NsfApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);

private:
    vector<WaveShortMessage*> neighborMsgs;
    vector<WaveShortMessage*> warningMsgs;

    vector<std::string> neighborIds;

};

#endif // NsfApplLayer_H
