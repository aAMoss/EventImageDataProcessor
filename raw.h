// raw.h

#ifndef RAW_H
#define RAW_H

#include "eidp.h"


// Function Prototypes - raw
void raw_literals_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][f_packet_size]);
                             
                             
                             
#endif //RAW_H
