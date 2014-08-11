#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define dID 0x23
#define PowerDown    0x00
#define PowerOn    0x01
#define Reset      0x07
#define ContinuHigh   0x10
#define ContinuLow   0x13
#define OneTimeHigh   0x20
#define OneTimeLow   0x23

int fd;
int rc;
int dID =  0x23;

int main (void)
{
int x;
char buf[5];
int readSz;
unsigned int res, lux;

/*
	if(wiringPisetup() == -1) {
		perror("ERR: wiringPi setup");
		return 1;
	}
*/
	if ((fd=wiringPiI2CSetup(dID)) < 0) {
		perror("i2cSetup");
		printf("ERR: i2c Setup failed\n");
		return 1;
	} else {
		printf("Mode set as : Active\n");
	}

	if ((rc=wiringPiI2CWrite(fd,PowerOn)) < 0) {
		perror("write PowerOn");
		printf("ERR: PowerOn\n");
		return 1;
	} else {
		printf("PowerOn Success\n");
	}

	if ((rc=wiringPiI2CWrite(fd,ContinuHigh)) < 0) {
		perror("write conversion");
		printf("ERR: conversion\n");
	} else {
		printf("conversion Success\n");
		sleep(1);
	}

	while(1) {
		readSz = read(fd,buf,2);
		res=buf[0]*256+buf[1];
		lux = res / 1.2;
		printf("ReadSz:%i\t Lux:%d\n",readSz,lux);
		sleep(1);
	}
}
