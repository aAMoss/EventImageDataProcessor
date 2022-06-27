// hyper.h - Hyper-parameters and configuration

#ifndef HYPER_H
#define HYPER_H

/*
 *******************************************************************************
 * STANDARD HEADERS
 *******************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/*
 *******************************************************************************
 * POSIX HEADERS
 *******************************************************************************
 */
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 *******************************************************************************
 * DEFINITIONS
 *******************************************************************************
 */

//#define TEST_IN_DIR "./N-MNIST_test/Test/"
//#define TRAIN_IN_DIR "./N-MNIST_test/Train/"
#define TEST_IN_DIR "./N-MNIST/Test/"
#define TRAIN_IN_DIR "./N-MNIST/Train/"

#define EVENTS_PER_SAMPLE_MAX 10000
#define DATA_IN_NAME_MAX 200
#define FEATURES_MAX 1024
#define FEATURES_MIN 4

#define MAXFRAME_X 32
#define MAXFRAME_Y 32
#define F_DIV 2
#define REG_X 8
#define REG_Y 8
#define MIN_FRAME_X (MAXFRAME_X / F_DIV)
#define MIN_FRAME_Y (MAXFRAME_Y / F_DIV)

#define PACKET_MAX 1500
#define PACKET_MIN 100
#define EVENT_BUFF_SIZE 5
#define DATA_OUT_NAME_MAX 200
#define CLASSES 10

// DEFINITIONS RAW
#define RAW_XY_BOOL 6
#define RAW_P_BOOL 1
#define RAW_T_BOOL 24
#define RAW_C_BOOL 4
#define RAW_BOOL_MAX 41

// DEFINITIONS PBFE

// patch D x D
#define PATCH_D 7

// max patch D origin 0,0 postion
#define PATCH_X_MAX (MAXFRAME_X - PATCH_D)
#define PATCH_Y_MAX (MAXFRAME_Y - PATCH_D)
#define PATCH_X_MIN 0
#define PATCH_Y_MIN 0

// must be between 4 and 1024, a multiple of 4,
//and a perfect square root: 4, 16, 64, 256, 1024
#define B_FEATURES 64
#define B_FEATURES_STRING (B_FEATURES + 1)
#define B_FEATURES_CLASS (B_FEATURES + 4)

// DEFINITIONS IDFE
#define S_FEATURES 64	// 4, 16, 64, 256, 1024 features respectively
#define THRESHOLD_DIV 3
#define SEG_X (sqrt(S_FEATURES))
#define SEG_Y (sqrt(S_FEATURES))
#define SEG_A_X (MAXFRAME_X / SEG_X)
#define SEG_A_Y (MAXFRAME_Y / SEG_Y)

/*
 *******************************************************************************
 * FUNCTION PROTOTYPES
 *******************************************************************************
 */

void hyper_parse_cmd_args(int argc, char *argv[]);
void hyper_parse_cmd_args1(int argc, char *argv[], int *fe_mode);
void hyper_parse_cmd_args2(int argc, char *argv[], int fe_mode, int *features);
void hyper_parse_cmd_args3(int argc, char *argv[], int *packet_size);
void hyper_parse_cmd_args4(int argc, char *argv[], int packet_size,
						   int *packet_overlap);
void hyper_set_out_dir_label(int fe_mode, int features,
							 int packet_size, int packet_overlap,
							 char *output_dir_label);






#endif //HYPER_H
