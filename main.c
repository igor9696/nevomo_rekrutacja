#include <stdio.h>
#include <stdlib.h>
#include "lib/tinydir.h"
#include "stdint.h"
#include "inc/imu_parser.h"
#include <math.h>
#include <limits.h>


int check_arguments(int argc) 
{
    if(argc == 2) {
        return 0;
    }

    else if(argc == 1) {
        printf("Path to directory not specified!\n");
        return 1;
    }

    else {
        printf("Too many arguments!\n");
        return 1;
    }
}

float velocity_min = (float)INT_MAX;
float velocity_max = (float)INT_MIN;

int main(int argc, char* argv[])
{
    imu_t imu;
    FILE *fptr;
    tinydir_dir dir;

    if(check_arguments(argc) != 0)
    {  
        return -1;
    }

    if(tinydir_open(&dir, argv[1]) == -1)
    {
        printf("Error with directory path!\n");
        return -1;
    }

    while(dir.has_next) 
    {
        tinydir_file file;
        if(tinydir_readfile(&dir, &file) == -1)
        {
            printf("Error during file read!\n");
            goto Tinydir_handler;
        }

        if(strcmp(file.extension, "imu") != 0)
        {
            if(tinydir_next(&dir) == -1) {
                printf("Error with getting next file.\n");
                goto Tinydir_handler;
            }

            continue;
        }

        // printf("%s\n", file.name); // debug
        fptr = fopen((char*)file.path, "rb");
        if(fptr == NULL)
        {
            printf("Error during FILE read!\n");
            goto Tinydir_handler;
        }

        // read data to imu struct
        if(fread(&imu, sizeof(char), sizeof(imu), fptr) == 0)
        {
            printf("Error during imu data read\n");
        }

        // printf("Velocity: %f, %f, %f\n", imu.velocity[0], imu.velocity[1], imu.velocity[2]);

        // calculate velocity from three axis
        float res_velocity;
        res_velocity = sqrtf(powf(imu.velocity[0], 2) + powf(imu.velocity[1], 2) + powf(imu.velocity[2], 2));
        // printf("Result velocity: %f\n", res_velocity);

        // update min and max values
        if(velocity_min > res_velocity)
        {
            velocity_min = res_velocity;
        }

        else if(velocity_max < res_velocity)
        {
            velocity_max = res_velocity;
        }

        // fseek(fptr, 0, SEEK_END); 
        // size_t file_size_in_bytes = ftell(fptr);
        // fseek(fptr, 0, SEEK_SET);

        fclose(fptr);

        if(tinydir_next(&dir) == -1) {
            printf("Error with getting next file.\n");
            goto Tinydir_handler;
        }
    }

    // print results
    printf("Min velocity: %f \t Max velocity: %f\n", velocity_min, velocity_max);

Tinydir_handler:
    tinydir_close(&dir);
    return 0;
}