// pbfe.h - packet binary feature extractor

#ifndef PBFE_H
#define PBFE_H

// Program Specific Headers
#include "eidp.h"
#include "dataio.h"


// Function Prototypes
void pbfe_zero_binary_variables(int output_binary_literals[], int binary_features_count[]);

void pbfe_zero_patch_variables(int patch_o_px[],int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                   int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[]);

void pbfe_binary_patch_variables(int patch_o_px[], int patch_o_py[], int patch_o_nx[], int patch_o_ny[],
                                     int patch_m_px[],int patch_m_py[], int patch_m_nx[], int patch_m_ny[]);

void pbfe_positive_binary_patch(int binary_features_count[], long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_px[], int patch_o_py[], int patch_m_px[], int patch_m_py[]);

void pbfe_negative_binary_patch(int binary_features_count[], long int EventPacketX[], long int EventPacketY[],
                                    int patch_o_nx[], int patch_o_ny[], int patch_m_nx[], int patch_m_ny[]);

void pbfe_binary_patches_output(int output_binary_literals[], int binary_features_count[],
                                    int f_packet_size, long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[]);

void pbfe_print_to_terminal(int output_binary_literals[], int packet_no);


void pbfe_output_packet_literals_min0(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count);

void pbfe_correct_zero_packet_literals(int output_binary_literals[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count);

void pbfe_output_packet_literals_min1(int pbfe_final_output[], int pbfe_output_packet_literals[packets_req][B_FEATURES], int *packets_min0_count);


void pbfe_print_to_file_pbfe_min_literals(FILE *Processed_Data_Output_File, int pbfe_final_output[]);
void pbfe_print_to_file_pbfe_literals(FILE *Processed_Data_Output_File, int output_binary_literals[]);


#endif //PBFE_H
