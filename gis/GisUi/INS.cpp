#include "INS.h"




INS::INS()
{
    this->connected = false;

    this->handler = CreateFileA(static_cast<LPCSTR>(COMPORT) ,
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                /*FILE_ATTRIBUTE_NORMAL*/0,
                                NULL);
    if (this->handler == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
			printf("ERROR: Handle was not attached. Reason: %s not available\n", COMPORT);
        }
    else
        {
            printf("ERROR!!!");
        }
    }
    else {
        DCB dcbSerialParameters = {0};

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
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

INS::~INS()
{
    if (this->connected){
        this->connected = false;
        CloseHandle(this->handler);
    }
}
QgsPoint* INS::get_position()
{
	if (isConnected()){
		return &currentPosition;
	}
	else{
		return &QgsPoint(0, 0);
	}

}

int INS::readINS(char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    int toRead ;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

	if (ReadFile(this->handler, buffer, toRead, &bytesRead, 0))	return bytesRead;


    return 0;
}

//bool INS::writeINS(char *buffer, unsigned int buf_size)
//{
//    DWORD bytesSend;
//
//    if (!WriteFile(this->handler, (void*) buffer, buf_size, &bytesSend, 0)){
//        ClearCommError(this->handler, &this->errors, &this->status);
//        return false;
//    }
//    else return true;
//}

bool INS::isConnected()
{
    return this->connected;
}
/*INSData()*/
void INS::printData(){
	for (int i = 0; i < MAX_DATA_LENGTH; i++){
		if ((incomingData[i + 0] == END) && (incomingData[i + 1] == VERIFY) && (incomingData[i + 67] == END)){

			//system("cls");//清屏

			//printf("坐标X:%d\n", *((int*)(incomingData + 2 + i)));
			//printf("坐标Y:%d\n", *((int*)(incomingData + 6 + i)));
			//printf("高程:%d\n", *((short*)(incomingData + 10 + i)));
			//printf("区号:%d\n", *((char*)(incomingData + 12 + i)));
			//
			//printf("经度:%d\n", *((int*)(incomingData + 13 + i)));
			currentPosition.setX ( *((int*)(incomingData + 13 + i))/1000000 );//
			//
			//printf("纬度:%d\n", *((int*)(incomingData + 17 + i)));
			currentPosition.setY ( *((int*)(incomingData + 17 + i))/1000000 );//
			
			//printf("航向角:%d\n", *((short*)(incomingData + 21 + i)));
			//printf("俯仰角:%d\n", *((short*)(incomingData + 23 + i)));
			//printf("倾斜角:%d\n", *((short*)(incomingData + 25 + i)));
			//printf("Vx:%d\n", *((short*)(incomingData + 27 + i)));
			//printf("Vy:%d\n", *((short*)(incomingData + 29 + i)));
			//printf("Vz:%d\n", *((short*)(incomingData + 31 + i)));
			//printf("Wx:%d\n", *((short*)(incomingData + 33 + i)));
			//printf("Wy:%d\n", *((short*)(incomingData + 35 + i)));
			//printf("Wz:%d\n", *((short*)(incomingData + 37 + i)));
			//printf("Ax:%d\n", *((short*)(incomingData + 39 + i)));
			//printf("Ay:%d\n", *((short*)(incomingData + 41 + i)));
			//printf("Az:%d\n", *((short*)(incomingData + 43 + i)));
			//printf("Bx:%d\n", *((short*)(incomingData + 45 + i)));
			//printf("By:%d\n", *((short*)(incomingData + 47 + i)));
			//printf("Bz:%d\n", *((short*)(incomingData + 49 + i)));
			//printf("本次里程:%d\n", *((short*)(incomingData + 51 + i)));
			//printf("GPS授时(hhmmss.sss):%d\n", *((int*)(incomingData + 55 + i)));//5个字节??
			//printf("GPS授时(yyyymmdd):%d\n", *((int*)(incomingData + 60 + i)));
			//printf("工作状态:%d\n", *((char*)(incomingData + 64 + i)));
			
			return ;
		}
	}

}

void INS::receiveData(void)
{
	while (1){
		int readResult = readINS(incomingData, MAX_DATA_LENGTH);
		if (!readResult){
			printf("Error to read!");
			return;
		}
		//To Do ...解析数据
		printData();//打印数据
		Sleep(1000); //读取的间隔时间
	}
	
}

void INS::run()
{

	//while (this->isConnected()) 
	receiveData();

	qDebug() << "WTF WTF WTF WTF WTF WTF WTF WTF WTF ";
}