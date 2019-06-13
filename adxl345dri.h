#ifndef ADXL345DRI_H
#define ADXL345DRI_H


#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "mainwindow.h"

#define  DevAddr  0x53  //device address




void adxl345_init(int fd)
{
    wiringPiI2CWriteReg8(fd, 0x31, 0x0b);
    wiringPiI2CWriteReg8(fd, 0x2d, 0x08);
    //	wiringPiI2CWriteReg8(fd, 0x2e, 0x00);
    wiringPiI2CWriteReg8(fd, 0x1e, 0x00);
    wiringPiI2CWriteReg8(fd, 0x1f, 0x00);
    wiringPiI2CWriteReg8(fd, 0x20, 0x00);
    wiringPiI2CWriteReg8(fd, 0x21, 0x00);
    wiringPiI2CWriteReg8(fd, 0x22, 0x00);
    wiringPiI2CWriteReg8(fd, 0x23, 0x00);
    wiringPiI2CWriteReg8(fd, 0x24, 0x01);
    wiringPiI2CWriteReg8(fd, 0x25, 0x0f);
    wiringPiI2CWriteReg8(fd, 0x26, 0x2b);
    wiringPiI2CWriteReg8(fd, 0x27, 0x00);
    wiringPiI2CWriteReg8(fd, 0x28, 0x09);
    wiringPiI2CWriteReg8(fd, 0x29, 0xff);
    wiringPiI2CWriteReg8(fd, 0x2a, 0x80);
    wiringPiI2CWriteReg8(fd, 0x2c, 0x0a);
    wiringPiI2CWriteReg8(fd, 0x2f, 0x00);
    wiringPiI2CWriteReg8(fd, 0x38, 0x9f);
}

struct acc_dat adxl345_read_xyz(int fd)
{	char x0, y0, z0, x1, y1, z1;
    struct acc_dat acc_xyz;

    x0 = 0xff - wiringPiI2CReadReg8(fd, 0x32);
    x1 = 0xff - wiringPiI2CReadReg8(fd, 0x33);
    y0 = 0xff - wiringPiI2CReadReg8(fd, 0x34);
    y1 = 0xff - wiringPiI2CReadReg8(fd, 0x35);
    z0 = 0xff - wiringPiI2CReadReg8(fd, 0x36);
    z1 = 0xff - wiringPiI2CReadReg8(fd, 0x37);

    acc_xyz.x = (int)(x1 << 8) + (int)x0;
    acc_xyz.y = (int)(y1 << 8) + (int)y0;
    acc_xyz.z = (int)(z1 << 8) + (int)z0;


    if(acc_xyz.x>65535/2) acc_xyz.x=acc_xyz.x-65535;
    if(acc_xyz.y>65535/2) acc_xyz.y=acc_xyz.y-65535;
    if(acc_xyz.z>65535/2) acc_xyz.z=acc_xyz.z-65535;

    acc_xyz.xg= acc_xyz.x/256.00*9.8;
    acc_xyz.yg= acc_xyz.y/256.00*9.8;
    acc_xyz.zg= acc_xyz.z/256.00*9.8;

    acc_xyz.roll = atan2(acc_xyz.y , acc_xyz.z) * 57.3;//z
    acc_xyz.pitch= atan2((- acc_xyz.x) , sqrt(acc_xyz.y * acc_xyz.y + acc_xyz.z* acc_xyz.z)) * 57.3;//x
    acc_xyz.yaw= atan2((- acc_xyz.y) , sqrt(acc_xyz.x * acc_xyz.x + acc_xyz.z* acc_xyz.z)) * 57.3;//y

    return acc_xyz;
}

int GetADXL345fd ()
{
    int fd;
    fd = wiringPiI2CSetup(DevAddr);
    return fd;
}



#endif // ADXL345DRI_H
