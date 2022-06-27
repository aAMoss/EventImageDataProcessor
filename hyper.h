// hyper.h - Hyper-parameters and configuration

#ifndef HYPER_H
#define HYPER_H

//#include "config.h"





hyper_parse_cmd_args(argc, argv);

hyper_parse_cmd_args1(argc, argv, &fe_mode);

hyper_parse_cmd_args2(argc, argv, fe_mode, &features);

hyper_parse_cmd_args3(argc, argv, &packet_size);

hyper_parse_cmd_args4(argc, argv, packet_size, &packet_overlap);

hyper_set_out_dir_label(fe_mode, features, packet_size, packet_overlap,
						output_dir_label);

#endif //HYPER_H
