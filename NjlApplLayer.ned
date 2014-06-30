package francisco;

import org.car2x.veins.modules.application.ieee80211p.BaseWaveApplLayer;


simple NjlApplLayer extends BaseWaveApplLayer
{
    @class(NjlApplLayer);
    @display("i=block/app2");
    double junctionDistanceThreshold = default(50.0);
}
