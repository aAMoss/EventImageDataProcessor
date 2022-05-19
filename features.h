// features.h

// Defintions - features_literals_raw_dat
#define RAW_XY_BOOL 6
#define RAW_P_BOOL 1
#define RAW_T_BOOL 24
#define RAW_C_BOOL 4
#define RAW_BOOL_MAX ((2*RAW_XY_BOOL) + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL) //41

#define MAXFRAME_X 32
#define MAXFRAME_Y 32

#define F_DIV 2
#define REG_X 8
#define REG_Y 8


#define MIN_FRAME_X (MAXFRAME_X / F_DIV)
#define MIN_FRAME_Y (MAXFRAME_Y / F_DIV)

int EventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int EventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y];
int EventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y];

int PrevEventFrameCountALL[MAXFRAME_X][MAXFRAME_Y];
int PrevEventFrameCountPOS[MAXFRAME_X][MAXFRAME_Y];
int PrevEventFrameCountNEG[MAXFRAME_X][MAXFRAME_Y];

int OutputEventFrameBoolsALL[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsPOS[MAXFRAME_X][MAXFRAME_Y];
int OutputEventFrameBoolsNEG[MAXFRAME_X][MAXFRAME_Y];

int MiniEventFrameBoolsALL[MIN_FRAME_X][MIN_FRAME_Y];
int MiniEventFrameBoolsPOS[MIN_FRAME_X][MIN_FRAME_Y];
int MiniEventFrameBoolsNEG[MIN_FRAME_X][MIN_FRAME_Y];

float EventFrameDensityALL[MAXFRAME_X][MAXFRAME_Y];
float EventFrameDensityPOS[MAXFRAME_X][MAXFRAME_Y];
float EventFrameDensityNEG[MAXFRAME_X][MAXFRAME_Y];


// Function Prototypes - raw
void features_literals_raw_data(long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                             int f_packet_size, int c, int literals_raw[RAW_BOOL_MAX][f_packet_size]);
