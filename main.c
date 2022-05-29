#include <stdio.h>
#include <stdlib.h>
#include "lib/tinydir.h"
#include "stdint.h"
#include "inc/imu_parser.h"
#include <math.h>
#include <limits.h>


int check_arguments(int argc);

int main(int argc, char* argv[])
{
    float velocity_min = INT_MAX;
    float velocity_max = INT_MIN;
    float velocity_val = 0;

    imu_t imu;
    FILE *fptr = NULL;
    tinydir_dir dir;
    tinydir_file file;


    if(check_arguments(argc) != 0)
    {  
        return -1;
    }

    if(tinydir_open(&dir, argv[1]) == -1)
    {
        printf("Directory not found!\n");
        return -1;
    }

    while(dir.has_next) 
    {        
        if(tinydir_readfile(&dir, &file) == -1)
        {
            printf("TinyDir File read error!\n");
            goto error;
        }
        
        // check if file has .imu extension, if no take another one
        if(strcmp(file.extension, "imu") != 0)
        {
            if(tinydir_next(&dir) == -1)
            {
                printf("Error during capturing next file.\n");
                goto error;
            }

            continue;
        }

        fptr = fopen((char*)file.path, "rb");
        if(fptr == NULL)
        {
            printf("File open failed!\n");
            goto error;
        }

        // Try to read data directly to a struct, if data size is different than struct size skip file 
        if(fread(&imu, sizeof(char), sizeof(imu), fptr) != sizeof(imu))
        {
            printf("Data read fail!\n");
            fclose(fptr);
            if(tinydir_next(&dir) == -1) 
            {
                printf("Error with getting next file.\n");
                goto error;
            }

            continue;
        }

        // calculate velocity magnitude from three axis
        velocity_val = sqrtf(powf(imu.velocity[0], 2) + powf(imu.velocity[1], 2) + powf(imu.velocity[2], 2));

        // update min and max values
        if(velocity_min > velocity_val)
        {
            velocity_min = velocity_val;
        }

        else if(velocity_max < velocity_val)
        {
            velocity_max = velocity_val;
        }

        fclose(fptr);

        // get next file
        if(tinydir_next(&dir) == -1)
        {
            printf("Error with getting next file.\n");
            goto error;
        }
    }

    // if velocity_min or velocity_max remain unchanged there wasn't valid data inside dir
    if(velocity_min == INT_MAX || velocity_max == INT_MIN)
    {
        printf("Coulnd't find any valid .imu file!\n");
        tinydir_close(&dir);
        return 1;
    }

    printf("Max velocity: %f \t Min velocity: %f\n", velocity_max, velocity_min);
    tinydir_close(&dir);
    return 0;

error:
    tinydir_close(&dir);
    return -1;
}

int check_arguments(int argc)
{
    if(argc == 2)
    {
        return 0;
    }

    else if(argc == 1)
    {
        printf("Path to directory not specified!\n");
        return 1;
    }

    else 
    {
        printf("Too many arguments!\n");
        return -1;
    }
}