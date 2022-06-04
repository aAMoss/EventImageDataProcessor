// process.h

#ifndef PROCESS_H
#define PROCESS_H

// Program Specific Headers
#include "eidp.h"
#include "dataio.h"
#include "raw.h"
#include "idfe.h"
#include "pbfe.h"

// Function Prototypes
void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                        int fe_mode, int type);


#endif // PROCESS_H
