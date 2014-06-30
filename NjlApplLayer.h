#ifndef NjlApplLayer_H
#define NjlApplLayer_H

#include "BaseFranciscoApplLayer.h"
#include <list>
#include <vector>

#define SEND_REBROADCAST_EVENT 3

using namespace std;

class Junction;

class NjlApplLayer : public BaseFranciscoApplLayer
{

public:
    virtual void initialize(int stage);

protected:
    double junctionDistanceThreshold;


protected:
    virtual void onBeacon(WaveShortMessage* wsm);
    virtual void onData(WaveShortMessage* wsm);
    virtual void handleSelfMsg(cMessage* msg);

private:

    vector<WaveShortMessage*> neighborMsgs;
    vector<std::string> neighborIds;
    vector<WaveShortMessage*> warningMsgs;

    vector<std::string> neighborJunctions;
    vector<WaveShortMessage*> hotWSMs;                    // msgs requiring the 'security' delay
    vector<int> hotWSMRepeatIndices;                      // indices of those hotMsgs that have been recv'd again.
    Veins::AnnotationManager* annotationManager;
};


#endif // NjlApplLayer_H
