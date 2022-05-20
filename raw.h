// features.h

// Defintions - features_literals_raw_dat
#define RAW_XY_BOOL 6
#define RAW_P_BOOL 1
#define RAW_T_BOOL 24
#define RAW_C_BOOL 4
#define RAW_BOOL_MAX ((2*RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL) //41




// Function Prototypes - raw
void raw_literals_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][f_packet_size]);