#include <stdio.h>
#include <stdlib.h>
#include "lib/tinydir.h"
#include "stdint.h"



int main()
{
    FILE *fptr;
    tinydir_dir dir;

    if(tinydir_open(&dir, "./imu") == -1)
    {
        printf("Error during dir open!\n");
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

        printf("%s\n", file.name); // debug
        fptr = fopen((char*)file.path, "rb");
        if(fptr == NULL)
        {
            printf("Error during FILE read!\n");
            goto Tinydir_handler;
        }

        fseek(fptr, 0, SEEK_END); 
        size_t file_size_in_bytes = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        fclose(fptr);

        if(tinydir_next(&dir) == -1) {
            printf("Error getting next file.\n");
            goto Tinydir_handler;
        }
    }

Tinydir_handler:
    tinydir_close(&dir);
    return 0;
}