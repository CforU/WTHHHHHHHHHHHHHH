#ifndef INS_H
#define INS_H

#define _CRT_SECURE_NO_DEPRECATE // π”√sprintf
#define COMPORT				"COM3"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define END    (0xffffffc0)
#define VERIFY    (0xFFFFFFE5)
#define MAX_DATA_LENGTH 1024
#define ARDUINO_WAIT_TIME	2000


typedef struct{
	int X;
	int Y;
	short Altitude;
	char Zone;
	int Longitude;
	int Latitude;
	short HeadAngle;
	short PitchAngle;
	short SlantAangle;
	short Vx;
	short Vy;
	short Vz;
	short Wx;
	short Wy;
	short Wz;
	short Ax;
	short Ay;
	short Az;
	short Bx;
	short By;
	short Bz;
	short Mileage;
	short HH;
	short mm;
	char sss;
	short yyyy;
	char MM;
	char dd;
	char Workingstatus;
} INSInfo;

class INS 
{
public:
	INS(const char* commport);
    ~INS();
	//API
	int read(INSInfo* insData);
	int formatINSInfo(INSInfo* insData, char* buf, int buf_size);
private:
	HANDLE handler;
	char incomingData[MAX_DATA_LENGTH];
};

#endif // INS_H
