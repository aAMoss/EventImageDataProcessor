// hyper.h - Hyper-parameters and configuration

#ifndef HYPER_H
#define HYPER_H

//#include "config.h"





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
