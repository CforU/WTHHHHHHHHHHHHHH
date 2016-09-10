#ifndef INS_H
#define INS_H

#define COMPORT				"COM3"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

//char* portName = COMPORT; //串口号
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

private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
	char incomingData[MAX_DATA_LENGTH];
    //QgsPoint currentPosition;//实时位置

public:
	INS();
    ~INS();
	//API
	int read(INSInfo* insData);
private:
	int initialize();

	void receiveData(); 

	INSInfo* insData;

};

#endif // INS_H
