#ifndef NSFAPPLLAYER_H_
#define NSFAPPLLAYER_H_

#include <map>
#include <BaseApplLayer.h>
#include <Consts80211p.h>
#include <Mac80211Pkt_m.h>
#include <WaveShortMessage_m.h>
#include <ChannelAccess.h>
#include <WaveAppToMac1609_4Interface.h>

#ifndef DBG
#define DBG EV
#endif

class NsfApplLayer : public BaseApplLayer {

    public:
        ~NsfApplLayer();
        virtual void initialize(int stage);
        virtual void finish();

        virtual  void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);

        enum WaveApplMessageKinds {
            SERVICE_PROVIDER = LAST_BASE_APPL_MESSAGE_KIND,
            SEND_BEACON_EVT
        };

    protected:

        static const simsignalwrap_t mobilityStateChangedSignal;

        /** @brief handle messages from below */
        virtual void handleLowerMsg(cMessage* msg);
        /** @brief handle self messages */
        virtual void handleSelfMsg(cMessage* msg);

        virtual WaveShortMessage* prepareWSM(std::string name, int dataLengthBits, t_channel channel, int priority, int rcvId, int serial=0);
        virtual void sendWSM(WaveShortMessage* wsm);
        virtual void onBeacon(WaveShortMessage* wsm) = 0;
        virtual void onData(WaveShortMessage* wsm) = 0;

        virtual void handlePositionUpdate(cObject* obj);

    protected:
        int beaconLengthBits;
        int beaconPriority;
        bool sendData;
        bool sendBeacons;
        simtime_t individualOffset;
        int dataLengthBits;
        bool dataOnSch;
        int dataPriority;
        Coord curPosition;
        int mySCH;
        int myId;

        cMessage* sendBeaconEvt;

        WaveAppToMac1609_4Interface* myMac;
};

#endif /* NSFAPPLLAYER_H_ */
