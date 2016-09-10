#include "INS.h"

INS::INS()
{
	//³õÊ¼»¯
	initialize();
	INSInfo* insData = new INSInfo;
}

INS::~INS()
{
    CloseHandle(this->handler); 
	delete insData;
}

int INS::initialize()
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
		}
		else
		{
			printf("ERROR!!!");
		}
	}
	else {
		DCB dcbSerialParameters = { 0 };

		if (!GetCommState(this->handler, &dcbSerialParameters)) {
			printf("failed to get current serial parameters");
		}
		else {
			dcbSerialParameters.BaudRate = CBR_115200;
			dcbSerialParameters.ByteSize = 8;
			dcbSerialParameters.StopBits = ONESTOPBIT;
			dcbSerialParameters.Parity = NOPARITY;
			// dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

			if (!SetCommState(handler, &dcbSerialParameters))
			{
				printf("ALERT: could not set Serial port parameters\n");
			}
			else {
				PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(ARDUINO_WAIT_TIME);
			}
		}
	}
}
//QgsPoint* INS::get_position()
//{
//	if (isConnected()){
//		return &currentPosition;
//	}
//	else{
//		return &QgsPoint(0, 0);
//	}
//
//}


int INS::read(INSInfo* insData)
{
	for (int i = 0; i < MAX_DATA_LENGTH; i++){
		if ((incomingData[i + 0] == END) && (incomingData[i + 1] == VERIFY) && (incomingData[i + 67] == END)){
			insData->X = *((int*)(incomingData + 2 + i));
			insData->Y = *((int*)(incomingData + 6 + i)));
			insData->Altitude = *((short*)(incomingData + 10 + i)));
			insData->Zone = *((char*)(incomingData + 12 + i)));
			insData->Longitude = *((int*)(incomingData + 13 + i)))/1000000;
			insData->Latitude =  *((int*)(incomingData + 17 + i)))/1000000;
			insData->HeadAngle = *((short*)(incomingData + 21 + i)));
			insData->PitchAngle = *((short*)(incomingData + 23 + i)));
			insData->SlantAangle = *((short*)(incomingData + 25 + i)));
			insData->Vx = *((short*)(incomingData + 27 + i)));
			insData->Vy = *((short*)(incomingData + 29 + i)));
			insData->Vz = *((short*)(incomingData + 31 + i)));
			insData->Wx = *((short*)(incomingData + 33 + i)));
			insData->Wy = *((short*)(incomingData + 35 + i)));
			insData->Wz = *((short*)(incomingData + 37 + i)));
			insData->Ax = *((short*)(incomingData + 39 + i)));
			insData->Ay = *((short*)(incomingData + 41 + i)));
			insData->Az = *((short*)(incomingData + 43 + i)));
			insData->Bx = *((short*)(incomingData + 45 + i)));
			insData->By = *((short*)(incomingData + 47 + i)));
			insData->Bz = *((short*)(incomingData + 49 + i)));
			insData->Mileage = *((int*)(incomingData + 51 + i)));
			insData->HH = *((short*)(incomingData + 55 + i)));
			insData->mm = *((short*)(incomingData + 57 + i)));
			insData->sss = *((char*)(incomingData + 59 + i)));
			insData->yyyy = *((short*)(incomingData + 60 + i)));
			insData->MM = *((char*)(incomingData + 62 + i)));
			insData->dd = *((char*)(incomingData + 63 + i)));
			insData->Workingstatus = *((char*)(incomingData + 64 + i)));

			return 0;
		}
	}

}
void INS::receiveData(){
	DWORD bytesRead = 0;
	while (1){
		int readResult = ReadFile(this->handler, incomingData, MAX_DATA_LENGTH, &bytesRead, 0);
		if (!readResult){
			printf("Error to read!");
			break;
		}
	}
}



