// hyper.c - Hyper-parameters and configuration

// just experimenting right now

// HYPER PARAMETERS

// Packet Size in number of events - could this be made the percentage of the event sample??
// Packet Overlap in number of events - could this be a percentage as well?
// Maybe have a configuration parameter that is set before running make that determines if these values are fixed or percentages

// number of features - feature extraction method dependent




// Standard Headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//Posix Headers
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Program Specific Headers
#include "eidp.h"
#include 'hyper.h'


void hyper_parse_cmd_args(int argc, char *argv[])
{
	// Check number of arguments
	if( argc == 5 )
	{
		printf("The arguments supplied: %s ", argv[0]);
		printf("%s ", argv[1]);
		printf("%s ", argv[2]);
		printf("%s ", argv[3]);
		printf("%s\n", argv[4]);
	}
	else
	if( argc > 5 )
	{
		printf("Too many arguments supplied. Program terminating.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Too few arguments, five expected. Program terminating.\n");
		exit(EXIT_FAILURE);
	}
}


void hyper_parse_cmd_args1(int argc, char *argv[], int *fe_mode)
{
	// Parse argv[1] the feature extraction method
	if(strcmp(argv[1], "raw") == 0)
	{
		*fe_mode = 0;
		printf("Feature Extraction Method: RAW\n");
	} else
	if(strcmp(argv[1], "pbfe") == 0)
	{
		*fe_mode = 1;
		printf("Feature Extraction Method: PBFE\n");
	} else
	if(strcmp(argv[1], "idfe") == 0)
	{
		*fe_mode = 2;
		printf("Feature Extraction Method: IDFE\n");
	} else
	{
		printf("Feature extraction method selection error. ");
		printf("Program terminating.\n");
		exit(EXIT_FAILURE);
	}
}


void hyper_parse_cmd_args2(int argc, char *argv[], int fe_mode, int *features)
{
	// Parse argv[2] the number of features
	//(a.k.a inputs for the Tsetlin Machine)
	int f = 0;
	int flag = 0;

	f = atoi(argv[2]);

	switch(fe_mode)
	{

	case 0:
		printf("For RAW, number of features is overridden ");
		printf("and set to %d\n", RAW_BOOL_MAX);
		*features = RAW_BOOL_MAX;
	break;

	case 1:
		if(f > 0)
		{
			*features = f;
		} else
		{
			while(flag < 1)
			{
				printf("ERROR: enter a number of features ");
				printf("that is greater than 0.\n");

				scanf("%d", &f);

				if(f < 1)
				{
					printf("\nERROR: the number of features must ");
					printf("be greater than 0!\n");
				}
				else
				{
					*features = f;
					flag++;
				}
			} //end while
		} // end if
	break;

	case 2: // need to ensure features = 4 16 64 256 1024
		if(f == 4 || f == 16 || f == 64 || f == 256 || f == 1024)
		{
			*features = f;
		} else
		{
			while(flag < 1)
			{
				printf("ERROR: Please enter a number of features ");
				printf("that is: 4, 16, 64, 256, 1024.\n");

				scanf("%d", &f);

				if(f == 4 || f == 16 || f == 64 || f == 256 || f == 1024)
				{
					*features = f;
					flag++;
				}
				else
				{
					printf("\nERROR: number of features for IDFE must be: ");
					printf("4, 16, 64, 256, 1024!\n");
				}
			} //end while
		} // end if
		break;

	}
}


void hyper_parse_cmd_args3(int argc, char *argv[],int *packet_size)
{
	int p = 0;
	int flag = 0;

	p = atoi(argv[3]);

	if(p >= PACKET_MIN && p <= PACKET_MAX)
	{
		*packet_size = p;
	} else
	{
		while(flag < 1)
		{
			printf("\nEnter an Event Packet Size in the range ");
			printf("%d to %d.\n\n", PACKET_MIN, PACKET_MAX);

			scanf("%d", &p);

			if(p < PACKET_MIN || p > PACKET_MAX)
			{
				printf("\nERROR: Event Packet Size must be between ");
				printf("%d and %d!\n\n", PACKET_MIN, PACKET_MAX);
			}
			else
			if(p >= PACKET_MIN && p <= PACKET_MAX)
			{
				*packet_size = p;
				flag++;
			}
		} // end while
	} // end if
}

void hyper_parse_cmd_args4(int argc, char *argv[],
							int packet_size, int *packet_overlap)
{
	int o = 0;
	int flag = 0;

	o = atoi(argv[4]);

	if(o > (packet_size - 1) || o < 0 )
	{
		while(flag < 1)
		{

			printf("\nERROR: Packet Overlap must be in the range 0 to ");
			printf("%d. Please enter a new value.\n\n", (packet_size - 1) );

			scanf("%d", &o);

			if(o > (packet_size - 1) || o < 0 )
			{
				printf("\nERROR: Packet Overlap must be in the range ");
				printf("0 to %d!\n\n", (packet_size - 1) );
			}
			else
			if (o >= 0 && o < packet_size)
			{
				*packet_overlap = o;
				flag++;
			}
		} // end while
	}else
	{
		*packet_overlap = o;
		flag++;
	}
}


void hyper_set_out_dir_label(int fe_mode, int features,
							  int packet_size, int packet_overlap,
							  char *output_dir_label)
{
	//sets the name of the output data directory
    char buf[5];
    char time_string[20];
    char *s = "_";
    char *s0 = "raw_";
	char *s1 = "pbfe_";
	char *s2 = "idfe_";

    memset(buf,0,sizeof(buf));
    memset(time_string,0,sizeof(time_string));
    memset(output_dir_label,0,sizeof(output_dir_label));

    time_t t = time(NULL);
    strftime(time_string, sizeof(time_string), "%Y%m%d_%H%M%S_", localtime(&t));
    strcat(output_dir_label, time_string);

    switch(fe_mode)
    {
    case 0: strcat(output_dir_label, s0); break;
    case 1: strcat(output_dir_label, s1); break;
    case 2: strcat(output_dir_label, s2); break;
    default: break;
    }

    sprintf(buf, "%d", features);
    strcat(output_dir_label,buf);
    strcat(output_dir_label,s);
    memset(buf,0,sizeof(buf));

    sprintf(buf, "%d", packet_size);
    strcat(output_dir_label,buf);
    strcat(output_dir_label,s);
    memset(buf,0,sizeof(buf));

    sprintf(buf, "%d", packet_overlap);
    strcat(output_dir_label,buf);
    memset(buf,0,sizeof(buf));
}














