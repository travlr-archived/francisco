package francisco;

import org.mixim.base.modules.IBaseApplLayer;
import org.mixim.base.modules.IMobility;
import org.mixim.modules.nic.Nic80211p;


//
// Example host module using an 802.11p Network interface card.
//
module Host80211p
{
    parameters:
        string applicationType = default("NsfApplLayer");
        string mobilityType = default("ConstSpeedMobility");
        @display("i=device/smallrouter");

    gates:
        input radioIn; // gate for sendDirect

    submodules:
        mobility: <mobilityType> like IMobility {
            parameters:
                @display("p=140,30;i=block/cogwheel");
        }
        nic: Nic80211p {
            parameters:
                @display("p=70,380;i=block/wrxtx,#008000");
        }
        appl: <applicationType> like IBaseApplLayer {
            parameters:
                @display("p=70,30;i=app");
        }

    connections allowunconnected:
        nic.upperLayerOut --> appl.lowerLayerIn;
        nic.upperLayerIn <-- appl.lowerLayerOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;

        radioIn --> nic.radioIn;
}
