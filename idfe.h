// idfe.h - inter (packet) dynamics feature extraction

#ifndef IDFE_H
#define IDFE_H

// Program Specific Headers
#include <math.h>
#include "eidp.h"
#include "dataio.h"







// Function Prototypes - zeroing
void idfe_zero_event_frames(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y]);
                                    
void idfe_zero_prev_event_frame(int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y]);
                                    
void idfe_zero_inter_frame_events(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);


// Function Prototypes - packet features
void idfe_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


void idfe_event_frame_density(int f_packet_size, int *packet_event_no, float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y],
                                  long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);


// Function Prototypes - inter-packet features
void idfe_create_inter_frame_events(int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                 int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                 int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);


// Function Prototypes - printing to terminal

void idfe_print_event_frame_count(int f_packet_size, int *packet_event_no, int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y],
                                      long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void idfe_print_inter_frame_events(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y]);

void idfe_inter_frame_events_counter(int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y],
                                          int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);
void idfe_print_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);
void idfe_zero_inter_frame_events_counter(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y]);


void count_segment_events(int seg_x, int seg_y,
                          int inter_frame_events[MAXFRAME_X][MAXFRAME_Y],
                          int seg_iframe_events[S_FEATURES][S_FEATURES] );

void idfe_inter_frame_events_segment_count(int inter_frame_events[MAXFRAME_X][MAXFRAME_Y],
                                           int seg_iframe_events[S_FEATURES][S_FEATURES]);


void idfe_zero_seg_iframe_events( int seg_iframe_events[S_FEATURES][S_FEATURES]);

void idfe_print_inter_frame_events_per_segment(int seg_iframe_events[S_FEATURES][S_FEATURES]);

void idfe_threshold_create_literals(int seg_iframe_events[S_FEATURES][S_FEATURES], int idfe_output_literals[S_FEATURES][S_FEATURES]);

void idfe_print_to_file_idfe_literals(FILE *Processed_Data_Output_File, int  idfe_output_literals[S_FEATURES][S_FEATURES]);


#endif //IDFE_H
