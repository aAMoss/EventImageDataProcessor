// config.h - Configuration Parameters

#ifndef CONFIG_H
#define CONFIG_H

// STANDARD HEADERS
#include <math.h>

// POSIX HEADERS

// FUNCTION PROTOTYPES
void config_parse_cmd_args(int argc, char *argv[]);

void config_parse_cmd_args1(int argc, char *argv[], int *fe_mode);

void config_parse_cmd_args2(int argc, char *argv[], int fe_mode, int *features);

void config_parse_cmd_args3(int argc, char *argv[], int *packet_size);

void config_parse_cmd_args4(int argc, char *argv[], int packet_size,
							int *packet_overlap);

void config_set_out_dir_label(int fe_mode, int features,
							  int packet_size, int packet_overlap,
							  char *output_dir_label);


//
//
//// DIRECTORY NAME DEFINITIONS
////#define TEST_IN_DIR "./N-MNIST_test/Test/"
////#define TRAIN_IN_DIR "./N-MNIST_test/Train/"
//#define TEST_IN_DIR "./N-MNIST/Test/"
//#define TRAIN_IN_DIR "./N-MNIST/Train/"
//
//
//// N-MNIST DEFINITIONS
//#define CLASSES 10
//#define MAX_EVENTS_PER_SAMPLE 10000
//#define MAX_FRAME_X 32
//#define MAX_FRAME_Y 32
//#define F_DIV 2
//#define REG_X 8
//#define REG_Y 8
//#define MIN_FRAME_X (MAXFRAME_X / F_DIV)
//#define MIN_FRAME_Y (MAXFRAME_Y / F_DIV)
//
//
//// EVENT DATA DEFINITIONS
//#define PACKET_MAX 1500
//#define PACKET_MIN 100
//#define EVENT_BUFF_SIZE 5
//
//
//// DATA NAME DEFINITIONS
//#define DATA_IN_NAME_MAX 200
//#define DATA_OUT_NAME_MAX 200
//
//
//// RAW DEFINITIONS
//#define RAW_FEATURES 41
//#define RAW_BOOL_X 6
//#define RAW_BOOL_Y 6
//#define RAW_BOOL_P 1
//#define RAW_BOOL_T 24
//#define RAW_BOOL_C 4
//#define RAW_BOOL_MAX (RAW_BOOL_X + RAW_BOOL_Y + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL) //41
//
//
//// PBFE DEFINITIONS
//#define MAX_PBFE_FEATURES 1024
//#define MIN_PBFE_FEATURES 4
//#define PBFE_FEATURES 64
// must be between 4 and 1024, a multiple of 4,
//and a perfect square root: 4, 16, 64, 256, 1024
//#define PATCH_SIZE 7 		//x*x
//#define MAX_PATCH_POS_X (MAX_FRAME_X - PATCH_SIZE)
// max patch D origin 0,0 postion
//#define MAX_PATCH_POS_Y (MAX_FRAME_Y - PATCH_SIZE)
//#define MIN_PATCH_POS_X 0
//#define MIN_PATCH_POS_Y 0
//#define PBFE_FEATURES_STRING (B_FEATURES + 1)
//#define PBFE_FEATURES_CLASS (B_FEATURES + 4)
//
//
//// IDFE DEFINITIONS
//#define MAX_IDFE_FEATURES 1024
//#define MIN_IDFE_FEATURES 4
//#define IDFE_FEATURES 64	// 4, 16, 64, 256, 1024 features respectively
//#define THRESHOLD_DIV 3
//#define SEG_X (sqrt(S_FEATURES))
//#define SEG_Y (sqrt(S_FEATURES))
//#define SEG_A_X (MAXFRAME_X / SEG_X)
//#define SEG_A_Y (MAXFRAME_Y / SEG_Y)
//
//
//
//
//
//// GENERIC VARIABLE TYPES
//typedef long int generic_event_var;
//typedef long int generic_packet_var;
//
//// EVENT DATA VARIABLE TYPES
//typedef int event_var_x;
//typedef int event_var_y;
//typedef int event_var_p;
//typedef unsigned long int event_var_t;
//
//// SPECIFIC EVENT PACKET VARIABLE TYPES
//typedef int packet_var_s;
//typedef int packet_var_o;
//{
//
//
//
//
//
//
//}
//





#endif //CONFIG_H
