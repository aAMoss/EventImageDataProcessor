// idfe.h - inter (packet) dynamics feature extraction

// Program Specific Headers
#include "dataio.h"






int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y];
int MiniEventFrameBoolsALL[MIN_FRAME_X][MIN_FRAME_Y];
float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y];



// Function Prototypes - zeroing
void idfe_zero_EventFrameCounts(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y]);
                                    
void idfe_zero_PrevEventFrameCounts(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y]);
                                    
void idfe_zero_OutputEventFrameBools(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);


void idfe_zero_EventFrameDensity(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y]);





// Function Prototypes - packet features
void idfe_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


void idfe_event_frame_density(int f_packet_size, int *packet_event_no, float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                  long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);





// Function Prototypes - inter-packet features
void idfe_eframe_continuous_bool(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                 int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                 int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);


// Function Prototypes - printing to terminal

void idfe_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                      long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void idfe_print_eframe_continuous_bool(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);

void idfe_print_event_frame_density(float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y]);
