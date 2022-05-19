// pbfe.h - packet binary feature extractor

// Program Specific Headers
#include "dataio.h"

// patch D x D
#define PATCH_D 7

// max patch D origin 0,0 postion
#define PATCH_X_MAX (MAXFRAME_X - PATCH_D)
#define PATCH_Y_MAX (MAXFRAME_Y - PATCH_D)
#define PATCH_X_MIN 0
#define PATCH_Y_MIN 0


#define B_FEATURES 128

int output_binary_literals[B_FEATURES];
int binary_features_count[B_FEATURES];
int patch_o_px[B_FEATURES];
int patch_o_py[B_FEATURES];
int patch_o_nx[B_FEATURES];
int patch_o_ny[B_FEATURES];
int patch_m_px[B_FEATURES];
int patch_m_py[B_FEATURES];
int patch_m_nx[B_FEATURES];
int patch_m_ny[B_FEATURES];



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