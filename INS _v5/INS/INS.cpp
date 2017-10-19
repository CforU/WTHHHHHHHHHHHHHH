#include "INS.h"

INS::INS(const char* commport)
{
	this->handler = CreateFileA(static_cast<LPCSTR>(COMPORT),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		/*FILE_ATTRIBUTE_NORMAL*/0,
		NULL);
	if (this->handler == INVALID_HANDLE_VALUE){
		if (GetLastError() == ERROR_FILE_NOT_FOUND){
			//Logger::log("INS", LEVEL_ERROR, "ERROR: Handle was not attached. Reason: %s not available\n", COMPORT);
		//	printf("ERROR!!!");
		}
		else
		{
			//printf("ERROR!!!");
		}
	}
	else {
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->handler, &dcbSerialParameters)) {
			//printf("failed to get current serial parameters");
		}
		else {
			dcbSerialParameters.BaudRate = CBR_115200;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;

			if (!SetCommState(handler, &dcbSerialParameters))
			{
			//	printf("ALERT: could not set Serial port parameters\n");
			}
			else {
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}

INS::~INS()
{
    CloseHandle(this->handler); 
}

int INS::read(INSInfo* insData)
{
	char incomingData[MAX_DATA_LENGTH];
	DWORD bytesRead = 0;
	int readResult = ReadFile(this->handler, incomingData, MAX_DATA_LENGTH, &bytesRead, 0);
	if (!readResult){
		//printf("Error to read!");
		return -1;//读取失败
	}
	for (int i = 0; i < MAX_DATA_LENGTH; i++){
		if ((incomingData[i + 0] == END) && (incomingData[i + 1] == VERIFY) && (incomingData[i + 67] == END)){
			insData->X = *((int*)(incomingData + 2 + i));
			insData->Y = *((int*)(incomingData + 6 + i));
			insData->Altitude = *((short*)(incomingData + 10 + i));
			insData->Zone = *((char*)(incomingData + 12 + i));
			insData->Longitude = *((int*)(incomingData + 13 + i));
			insData->Latitude = *((int*)(incomingData + 17 + i));
			insData->HeadAngle = *((short*)(incomingData + 21 + i));
			insData->PitchAngle = *((short*)(incomingData + 23 + i));
			insData->SlantAangle = *((short*)(incomingData + 25 + i));
			insData->Vx = *((short*)(incomingData + 27 + i));
			insData->Vy = *((short*)(incomingData + 29 + i));
			insData->Vz = *((short*)(incomingData + 31 + i));
			insData->Wx = *((short*)(incomingData + 33 + i));
			insData->Wy = *((short*)(incomingData + 35 + i));
			insData->Wz = *((short*)(incomingData + 37 + i));
			insData->Ax = *((short*)(incomingData + 39 + i));
			insData->Ay = *((short*)(incomingData + 41 + i));
			insData->Az = *((short*)(incomingData + 43 + i));
			insData->Bx = *((short*)(incomingData + 45 + i));
			insData->By = *((short*)(incomingData + 47 + i));
			insData->Bz = *((short*)(incomingData + 49 + i));
			insData->Mileage = *((int*)(incomingData + 51 + i));
			insData->HH = *((short*)(incomingData + 55 + i));
			insData->mm = *((short*)(incomingData + 57 + i));
			insData->sss = *((char*)(incomingData + 59 + i));
			insData->yyyy = *((short*)(incomingData + 60 + i));
			insData->MM = *((char*)(incomingData + 62 + i));
			insData->dd = *((char*)(incomingData + 63 + i));
			insData->Workingstatus = *((char*)(incomingData + 64 + i));
			return 0;//成功
		}
	}
	return -2;//解析失败
}

int INS::formatINSInfo(INSInfo* insData, char* buf, int buf_size){
	int i = 0;
	int j = sizeof(insData);
	if (buf_size < j){
		return -1;
	}
	else{
		i =  sprintf_s(buf, buf_size, "坐标X:%d\n", insData->X);
		i += sprintf_s(buf + i,buf_size - i , "坐标Y:%d\n", insData->Y);
		i += sprintf_s(buf + i, buf_size - i, "高程:%d\n", insData->Altitude);
		i += sprintf_s(buf + i, buf_size - i, "区号:%d\n", insData->Zone);
		i += sprintf_s(buf + i, buf_size - i, "经度:%d\n", insData->Longitude);
		i += sprintf_s(buf + i, buf_size - i, "纬度:%d\n", insData->Latitude);
		i += sprintf_s(buf + i, buf_size - i, "航向角:%d\n", insData->HeadAngle);
		i += sprintf_s(buf + i, buf_size - i, "俯仰角:%d\n", insData->PitchAngle);
		i += sprintf_s(buf + i, buf_size - i, "倾斜角:%d\n", insData->SlantAangle);
		i += sprintf_s(buf + i, buf_size - i, "Vx:%d\n", insData->Vx);
		i += sprintf_s(buf + i, buf_size - i, "Vy:%d\n", insData->Vy);
		i += sprintf_s(buf + i, buf_size - i, "Vz:%d\n", insData->Vz);
		i += sprintf_s(buf + i, buf_size - i, "Wx:%d\n", insData->Wx);
		i += sprintf_s(buf + i, buf_size - i, "Wy:%d\n", insData->Wy);
		i += sprintf_s(buf + i, buf_size - i, "Wz:%d\n", insData->Wz);
		i += sprintf_s(buf + i, buf_size - i, "Ax:%d\n", insData->Ax);
		i += sprintf_s(buf + i, buf_size - i, "Ay:%d\n", insData->Ay);
		i += sprintf_s(buf + i, buf_size - i, "Az:%d\n", insData->Az);
		i += sprintf_s(buf + i, buf_size - i, "Bx:%d\n", insData->Bx);
		i += sprintf_s(buf + i, buf_size - i, "By:%d\n", insData->By);
		i += sprintf_s(buf + i, buf_size - i, "Bz:%hd\n", insData->Bz);
		i += sprintf_s(buf + i, buf_size - i, "本次里程:%d\n", insData->Mileage);
		i += sprintf_s(buf + i, buf_size - i, "GPS授时(hhmmss.sss):%.2d", insData->HH);
		i += sprintf_s(buf + i, buf_size - i, ":%.2d", insData->mm);
		i += sprintf_s(buf + i, buf_size - i, ":%.2d\n", insData->sss);
		i += sprintf_s(buf + i, buf_size - i, "GPS授时(yyyymmdd):%d", insData->yyyy);
		i += sprintf_s(buf + i, buf_size - i, "-%d", insData->MM);
		i += sprintf_s(buf + i, buf_size - i, "-%d\n", insData->dd);
		i += sprintf_s(buf + i, buf_size - i, "工作状态:%d\n", insData->Workingstatus);
		return 0;
	}
}

//坐标装订
void INS::initPos(int lng, int lat, int H){
	DWORD bytesSend;
	char buffer[256] = { 0 };
	char c = 0XF6;
	buffer[0] = END;
	buffer[1] = c;
	buffer[2] = lng;
	buffer[6] = lat;
	buffer[10] = H;
	buffer[12] =  c ^ lng ^ lat ^ H;
	buffer[13] = END;

	if (WriteFile(this->handler, buffer, 14, &bytesSend, 0)){
		printf("success to init!!!!!  \n");
	}
}

//对准
void INS::seeking(){
	DWORD bytesSend;
	char uc = 0XF1;
	char buf[20];
	buf[0] = END;
	buf[1] = uc;
	buf[2] = uc;
	buf[3] = END;
	if (!WriteFile(this->handler, buf, 4, &bytesSend, 0)){
		printf("fail to seeking!!!!!  \n");
	}
}

//自检
void INS::verify(){
	DWORD bytesSend;
	char uc = 0XF0;
	char buf[20];
	buf[0] = END;
	buf[1] = uc;
	buf[2] = uc;
	buf[3] = END;

	if (WriteFile(this->handler, buf, 4, &bytesSend, 0)){
		printf("success to verify!!!!!  \n");
	}

}

//参数配置
void INS::setConfigure(unsigned char id, int val){
	DWORD bytesSend;
	char buffer[256] = { 0 };
	char command = 0XF4;
	buffer[0] = END;
	buffer[1] = command;
	buffer[2] = id;
	buffer[3] = val;
	buffer[7] = id ^ val;
	buffer[8] = END;

	if (WriteFile(this->handler, buffer, 16, &bytesSend, 0)){
		printf("success to init!!!!!  \n");
	}
}

//for debug
void INS::read(){

	char dateverify[1024];
	DWORD wtf = 0;
	int readResult = ReadFile(this->handler, dateverify, 1024, &wtf, 0);
	if (!readResult){
		printf("Error to read my current information!");
		return;//读取失败
	}
	for (int i = 0; i < 1024; i++){
		if ((dateverify[0 + i] == END) && (dateverify[1 + i] == 0xffffffe0) && (dateverify[4 + i] == END)){
			printf("当前自检状态：%02X\n", dateverify[2 + i]);
		}
	}
}