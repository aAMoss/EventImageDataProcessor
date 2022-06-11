// config.h - Configuration Parameters

#ifndef CONFIG_H
#define CONFIG_H



// DIRECTORY NAME DEFINITIONS
#define TEST_IN_DIR "./N-MNIST/Test/"
#define TRAIN_IN_DIR "./N-MNIST/Train/"

// GENERIC DEFINITIONS
#define MAX_EVENTS_PER_SAMPLE 10000
#define DATA_IN_NAME_MAX 200

// RAW DEFINITIONS
#define RAW_BOOL_X 6
#define RAW_BOOL_Y 6
#define RAW_BOOL_P 1
#define RAW_BOOL_T 24
#define RAW_BOOL_C 4
#define RAW_BOOL_MAX (RAW_BOOL_X + RAW_BOOL_Y + RAW_P_BOOL + RAW_T_BOOL + RAW_C_BOOL) //41


// PBFE DEFINITIONS
#define MAX_PBFE_FEATURES 1024
#define MIN_PBFE_FEATURES 4

// IDFE DEFINITIONS
#define MAX_IDFE_FEATURES 1024
#define MIN_IDFE_FEATURES 4







#endif //CONFIG_H
