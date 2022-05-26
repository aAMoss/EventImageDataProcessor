// process.h

// Program Specific Headers
#include "dataio.h"
#include "raw.h"
#include "pbfe.h"
#include "idfe.h"

// Function Prototypes
void process_event_data(int sample_events,int packet_size, int packet_overlap, int packets_req, int last_packet_size, int c,
                        long int EventPacketX[], long int EventPacketY[], long int EventPacketP[],long int EventPacketT[],
                        int fe_mode, int type);





// log file stuff
FILE *eidp_open_log_file_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label);
FILE *eidp_open_log_file_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label);

void eidp_print_log_file0_test(FILE *EIDP_LOG_FILE_TEST, char *output_dir_label, int fe_mode);
void eidp_print_log_file0_train(FILE *EIDP_LOG_FILE_TRAIN, char *output_dir_label, int fe_mode);
void eidp_print_log_file1_test(FILE *EIDP_LOG_FILE_TEST, int class,
                          long int sample_bytes, long int sample_events,
                          int packet_size, int packet_overlap, int packets_req,
                               int packet_events_overshoot, int last_packet_zeros, int last_packet_size);
void eidp_print_log_file1_train(FILE *EIDP_LOG_FILE_TRAIN, int class,
                          long int sample_bytes, long int sample_events,
                          int packet_size, int packet_overlap, int packets_req,
                                int packet_events_overshoot, int last_packet_zeros, int last_packet_size);

void eidp_print_log_file2(FILE *EIDP_LOG_FILE_TEST, FILE *EIDP_LOG_FILE_TRAIN,
                          int type, int fe_mode, double cpu_time_used);

