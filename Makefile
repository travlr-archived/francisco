#
# OMNeT++/OMNEST Makefile for francisco
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/obstacle -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/messages -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/analogueModel -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/base/connectionManager -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/base/messages -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/utility -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/phy -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/base/phyLayer -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/base/modules -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/mac/ieee80211p -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/base/utils -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules/application/ieee80211p -I/home/prodatalab/src/_veins-2.2/veins-veins-2.2/src/modules -L/home/prodatalab/src/_veins-2.2/veins-veins-2.2/out/$$\(CONFIGNAME\)/tests/testUtils -L/home/prodatalab/src/_veins-2.2/veins-veins-2.2/out/$$\(CONFIGNAME\)/src/base -L/home/prodatalab/src/_veins-2.2/veins-veins-2.2/out/$$\(CONFIGNAME\)/src/modules -lmiximtestUtils -lmiximbase -lmiximmodules -KMIXIM_PROJ=/home/prodatalab/src/_veins-2.2/veins-veins-2.2
#

# Name of target to be created (-o option)
TARGET = francisco$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(MIXIM_PROJ)/src/modules/obstacle \
    -I$(MIXIM_PROJ)/src/modules/messages \
    -I$(MIXIM_PROJ)/src/modules/analogueModel \
    -I$(MIXIM_PROJ)/src/base/connectionManager \
    -I$(MIXIM_PROJ)/src/base/messages \
    -I$(MIXIM_PROJ)/src/modules/utility \
    -I$(MIXIM_PROJ)/src/modules/phy \
    -I$(MIXIM_PROJ)/src/base/phyLayer \
    -I$(MIXIM_PROJ)/src/base/modules \
    -I$(MIXIM_PROJ)/src/modules/mac/ieee80211p \
    -I$(MIXIM_PROJ)/src/base/utils \
    -I$(MIXIM_PROJ)/src/modules/application/ieee80211p \
    -I$(MIXIM_PROJ)/src/modules \
    -I. \
    -Iresults

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(MIXIM_PROJ)/out/$(CONFIGNAME)/tests/testUtils -L$(MIXIM_PROJ)/out/$(CONFIGNAME)/src/base -L$(MIXIM_PROJ)/out/$(CONFIGNAME)/src/modules  -lmiximtestUtils -lmiximbase -lmiximmodules
LIBS += -Wl,-rpath,`abspath $(MIXIM_PROJ)/out/$(CONFIGNAME)/tests/testUtils` -Wl,-rpath,`abspath $(MIXIM_PROJ)/out/$(CONFIGNAME)/src/base` -Wl,-rpath,`abspath $(MIXIM_PROJ)/out/$(CONFIGNAME)/src/modules`

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/FloodingApplLayer.o \
    $O/DvcastApplLayer.o \
    $O/CounterApplLayer.o \
    $O/NjlApplLayer.o \
    $O/NsfApplLayer.o \
    $O/EmdrApplLayer.o \
    $O/DistanceApplLayer.o \
    $O/EsbrApplLayer.o \
    $O/Warning_m.o

# Message files
MSGFILES = \
    Warning.msg

# Other makefile variables (-K)
MIXIM_PROJ=/home/prodatalab/src/_veins-2.2/veins-veins-2.2

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f francisco francisco.exe libfrancisco.so libfrancisco.a libfrancisco.dll libfrancisco.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f results/*_m.cc results/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc results/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/CounterApplLayer.o: CounterApplLayer.cc \
	CounterApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/DistanceApplLayer.o: DistanceApplLayer.cc \
	DistanceApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/DvcastApplLayer.o: DvcastApplLayer.cc \
	DvcastApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/EmdrApplLayer.o: EmdrApplLayer.cc \
	EmdrApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/EsbrApplLayer.o: EsbrApplLayer.cc \
	EsbrApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/FloodingApplLayer.o: FloodingApplLayer.cc \
	FloodingApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/NjlApplLayer.o: NjlApplLayer.cc \
	NjlApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/NsfApplLayer.o: NsfApplLayer.cc \
	NsfApplLayer.h \
	$(MIXIM_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(MIXIM_PROJ)/src/base/messages/MacPkt_m.h \
	$(MIXIM_PROJ)/src/base/modules/BaseApplLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseBattery.h \
	$(MIXIM_PROJ)/src/base/modules/BaseLayer.h \
	$(MIXIM_PROJ)/src/base/modules/BaseMobility.h \
	$(MIXIM_PROJ)/src/base/modules/BaseModule.h \
	$(MIXIM_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(MIXIM_PROJ)/src/base/modules/BatteryAccess.h \
	$(MIXIM_PROJ)/src/base/utils/Coord.h \
	$(MIXIM_PROJ)/src/base/utils/FWMath.h \
	$(MIXIM_PROJ)/src/base/utils/FindModule.h \
	$(MIXIM_PROJ)/src/base/utils/HostState.h \
	$(MIXIM_PROJ)/src/base/utils/MiXiMDefs.h \
	$(MIXIM_PROJ)/src/base/utils/Move.h \
	$(MIXIM_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(MIXIM_PROJ)/src/base/utils/PassedMessage.h \
	$(MIXIM_PROJ)/src/base/utils/SimpleAddress.h \
	$(MIXIM_PROJ)/src/base/utils/miximkerneldefs.h \
	$(MIXIM_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(MIXIM_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(MIXIM_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(MIXIM_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(MIXIM_PROJ)/src/modules/utility/Consts80211p.h
$O/Warning_m.o: Warning_m.cc \
	Warning_m.h

