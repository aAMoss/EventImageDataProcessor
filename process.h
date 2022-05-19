// process.h

// Program Specific Headers
#include "dataio.h"
#include "features.h"
#include "pbfe.h"
#include "idfe.h"

// Function Prototypes
void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);
