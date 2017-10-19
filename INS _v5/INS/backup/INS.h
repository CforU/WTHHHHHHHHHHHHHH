#ifndef INS_H
#define INS_H

#define COMPORT				"COM3"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define END    (0xFFFFFFC0)
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

	int read(INSInfo* insData);
	int formatINSInfo(INSInfo* insData, char* buf, int buf_size);


	/*------------------------------------------------------------------
	自检：
			命令字				数据				校验字
		1字节(0XF0)		     无				 1字节
	功能：向惯性定位导航装置发送自检命令，触发方式；
	------------------------------------------------------------------*/
	void verify();//自检
	/*------------------------------------------------------------------
	坐标装订：
	命令字				经度				纬度				高程				校验字
	1字节(0XF6)	   四字节		  四字节			  四字节		  	    1字节
	功能：向惯性定位导航装置发送坐标装订命令，触发方式；
	经度/纬度值(十六进制,低位在前)，(单位为0.000001度)
	高程H值(十六进制,低位在前),(高程H单位为m，范围-9999~9999m)
	------------------------------------------------------------------*/
	void initPos(int lng, int lat, int H);//坐标装订
	/*------------------------------------------------------------------
	参数配置：
	命令字				参数序号				参数值				校验字
	1字节(0XF4)		  一字节				     四字节				 1字节
	功能：向惯性定位导航装置发送索要修改的【参数序号】及【参数值】
	，触发方式；
		参数序号数值为1-8，对应含义：
		参数序号				  参数含义				参数单位
			1						航向安装误差			 0.01mil
			2						  里程系数			     0.0001
			3						里程计脉冲数			 0.0001
			4						俯仰安装误差			 0.01mil
		  5-8						  备用参数
	------------------------------------------------------------------*/
	void seeking();//对准(寻北)
	/*------------------------------------------------------------------
	对准(寻北)：
	命令字				数据				校验字
	1字节(0XF3)	     无				 1字节
	功能：向惯性定位导航装置发送对准(寻北)命令，触发方式；
	------------------------------------------------------------------*/
	void setConfigure(unsigned char id, int val);//参数配置

	void read();//for debug

private:
	HANDLE handler;
};

#endif // INS_H
