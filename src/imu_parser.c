#include "../inc/imu_parser.h"
#include "../lib/tinydir.h"
#include "stdlib.h"
#include "stdio.h"





unsigned int get_imu_records_cnt(tinydir_dir* dir, const char* path_to_dir)
{
    unsigned int cnt = 0;

    // if(tinydir_file_open(&file, file.path) == -1)
    //     {
    //         printf("Error during file open!");
    //         goto error_handler;
    //     }

    //     printf("Path: %s\nName: %s\nExtension: %s\nIs dir? %s\nIs regular file? %s\n",
    //     file.path, file.name, file.extension,
    //     file.is_dir?"yes":"no", file.is_reg?"yes":"no");


    //     printf("%s\n", file.extension);
    //     if(strcmp(file.extension, "imu") == 0)
    //     {
    //         cnt_files++;
    //     }

    //     if(tinydir_next(&dir) == -1) {
    //         printf("Error geting next file.\n");
    //         goto error_handler;
    //     }

    return cnt;
}