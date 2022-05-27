#ifndef IMU_PARSER
#define IMU_PARSER

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#pragma pack(1)
typedef struct imu_t
{
    int32_t bip;
    int8_t ack_rx;
    int32_t interupt_time;
    int32_t msg_sample_rate[5];
    int32_t msg_lost[5];
    int32_t timestamp_euler;
    float euler_orientation[3];
    float eulerstd_dev[3];
    int32_t status_euler;
    int32_t timestamp_quat;
    float quaternion[4];
    float eulerstd_dev_[3];
    int32_t status_quat;
    int32_t timestamp_nav;
    float velocity[3];
    float velocitystd_dev[3];
    double position[3];
    float undulation;
    float positionstd_dev[3];
    int32_t status_nav;
    int32_t timestamp_stat;
    int16_t general_status;
    int16_t reserverd1;
    int32_t com_status;
    int32_t aiding_status;
    int32_t reserved2;
    int16_t reserved3;
    int32_t uptime;
    int32_t timestamp_utc;
    int16_t status_utc;
    int16_t year;
    int8_t month;
    int8_t day;
    int8_t hour;
    int8_t minut;
    int8_t second;
    int32_t nanosecond;
    int32_t gsp_time_of_week;
    int8_t encoder_directrion;
}imu_t;





#endif