// hyper.c - Hyper-parameters and configuration

// just experimenting right now

// HYPER PARAMETERS

// Packet Size in number of events - could this be made the percentage of the event sample??
// Packet Overlap in number of events - could this be a percentage as well?
// Maybe have a configuration parameter that is set before running make that determines if these values are fixed or percentages

// number of features - feature extraction method dependent

#include 'hyper.h'



packet_var_s PacketSize;
packet_var_o PacketOverlap;
int Features;
int CmdFlag = 0;
int FeatureMode = 0;
// both functions will need to be able to account for the inclusion or absence of commandline arguments
void  hyper_set_PacketSize(packet_var_s *PacketSize)
{







}

void hyper_set_PacketOverlap(packet_var_o *PacketOverlap)
{







}












