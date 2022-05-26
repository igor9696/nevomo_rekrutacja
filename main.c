#include <stdio.h>
#include <stdlib.h>
#include "lib/tinydir.h"
#include "stdint.h"

typedef uint8_t BYTE;


float bytesToFloat(uint8_t *bytes, unsigned int bytes_offset, char big_endian) {
    float f;
    uint8_t *f_ptr = (uint8_t *) &f;
    bytes_offset = bytes_offset * 4;
    if (big_endian) {
        f_ptr[3] = bytes[bytes_offset];
        f_ptr[2] = bytes[bytes_offset + 1];
        f_ptr[1] = bytes[bytes_offset + 2];
        f_ptr[0] = bytes[bytes_offset + 3];
    } else {
        f_ptr[3] = bytes[bytes_offset + 3];
        f_ptr[2] = bytes[bytes_offset + 2];
        f_ptr[1] = bytes[bytes_offset + 1];
        f_ptr[0] = bytes[bytes_offset];
    }
    return f;
}


int main()
{
    FILE *fptr;

    // unsigned char buffer[255];
    // memset(buffer, 0, sizeof(buffer));
    tinydir_dir dir;
    if(tinydir_open(&dir, "./imu") == -1)
    {
        printf("Error during dir open!\n");
        goto error_handler;
    }
    unsigned int global_cnt = 0;
    while(dir.has_next) {
        tinydir_file file;
        if(tinydir_readfile(&dir, &file) == -1)
        {
            printf("Error during file read!\n");
            goto error_handler;
        }
        if(strcmp(file.extension, "imu") != 0)
        {
            if(tinydir_next(&dir) == -1) {
                printf("Error geting next file.\n");
                goto error_handler;
            }
            continue;
        }

        // get file name and create FILE ptr
        // printf("%s\n", file.path);
        fptr = fopen((char*)file.path, "rb");
        if(fptr == NULL)
        {
            printf("Error during FILE read!\n");
            goto error_handler;
        }

        fseek(fptr, 0, SEEK_END); 
        size_t file_size_in_bytes = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        // allocate memory
        unsigned char* buff = (unsigned char*)malloc(file_size_in_bytes);
        if(buff == NULL) {
            printf("MALLOC ERROR!\n");
            goto error_handler;
        }
        memset(buff, 0, sizeof(buff));
        if(fread(buff, 1, file_size_in_bytes, fptr) != file_size_in_bytes) {
            printf("Smth goes wrong with reading bytes\n");
            goto error_handler;
        }

        float velocity[3] = {0, 0, 0};
        unsigned char bytes_temp[12];
        memset(bytes_temp, 0, sizeof(bytes_temp));
        unsigned int tmp = 0;
        for(int i = 121; i < 134; i++)
        {
            bytes_temp[tmp] = buff[i];
            tmp++;
        }
    
        velocity[0] = bytesToFloat(bytes_temp, 0, 0);
        velocity[1] = bytesToFloat(bytes_temp, 1, 0);
        velocity[2] = bytesToFloat(bytes_temp, 2, 0);

        printf("[%d] Velocity: %f, %f, %f\n", global_cnt, velocity[0], velocity[1], velocity[2]);
        global_cnt++;
        free(buff);
        fclose(fptr);

        if(tinydir_next(&dir) == -1) {
            printf("Error geting next file.\n");
            goto error_handler;
        }
    }
error_handler:
    if(fptr != NULL) {
        fclose(fptr);
    }
    tinydir_close(&dir);
    printf("Script DONE\n");
    return 0;
}