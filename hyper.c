// hyper.c - Hyper-parameters and configuration

// just experimenting right now

// HYPER PARAMETERS

// Packet Size in number of events - could this be made the percentage of the event sample??
// Packet Overlap in number of events - could this be a percentage as well?
// Maybe have a configuration parameter that is set before running make that determines if these values are fixed or percentages

// number of features - feature extraction method dependent


#include 'hyper.h'

// Generic Variable Types
typedef long int generic_event_var;
typedef long int generic_packet_var;

// Specific Event Data Variable Types
typedef unsigned int event_var_x;
typedef unsigned int event_var_y;
typedef unsigned char event_var_p;
typedef unsigned long int event_var_t;

// Specific Event Packet Variable Types
typedef long int packet_var;


event_var_x x[];
event_var_y y[];
event_var_p p[];
event_var_t t[];

packet_var packet_size;
packet_var packet_overlap;




