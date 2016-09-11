#include "INS.h"
#include <string.h>
#include <iostream>


using namespace std;
//char* portName = COMPORT; //串口号
#define END    (0xffffffc0)
#define VERIFY    (0xFFFFFFE5)
#define MAX_DATA_LENGTH 1024
char incomingData[MAX_DATA_LENGTH];

//Control signals for turning on and turning off the led
//Check arduino code
//char ledON[] = "ON\n";
//char ledOFF[] = "OFF\n";

//Arduino SerialPort object
INS *arduino;

//Blinking Delay
const unsigned int BLINKING_DELAY = 1000;

//If you want to send data then define "SEND" else comment it out
//#define SEND

void printData(){
	for (int i = 0; i < MAX_DATA_LENGTH; i++){
		if ((incomingData[i + 0] == END) && (incomingData[i + 1] == VERIFY) && (incomingData[i + 67] == END)){

			system("cls");//清屏
			printf("坐标X:%d\n", *((int*)(incomingData + 2 + i)));
			printf("坐标Y:%d\n", *((int*)(incomingData + 6 + i)));
			printf("高程:%d\n", *((short*)(incomingData + 10 + i)));
			printf("区号:%d\n", *((char*)(incomingData + 12 + i)));
			printf("经度:%d\n", *((int*)(incomingData + 13 + i)));
			printf("纬度:%d\n", *((int*)(incomingData + 17 + i)));
			printf("航向角:%d\n", *((short*)(incomingData + 21 + i)));
			printf("俯仰角:%d\n", *((short*)(incomingData + 23 + i)));
			printf("倾斜角:%d\n", *((short*)(incomingData + 25 + i)));
			printf("Vx:%d\n", *((short*)(incomingData + 27 + i)));
			printf("Vy:%d\n", *((short*)(incomingData + 29 + i)));
			printf("Vz:%d\n", *((short*)(incomingData + 31 + i)));
			printf("Wx:%d\n", *((short*)(incomingData + 33 + i)));
			printf("Wy:%d\n", *((short*)(incomingData + 35 + i)));
			printf("Wz:%d\n", *((short*)(incomingData + 37 + i)));
			printf("Ax:%d\n", *((short*)(incomingData + 39 + i)));
			printf("Ay:%d\n", *((short*)(incomingData + 41 + i)));
			printf("Az:%d\n", *((short*)(incomingData + 43 + i)));
			printf("Bx:%d\n", *((short*)(incomingData + 45 + i)));
			printf("By:%d\n", *((short*)(incomingData + 47 + i)));
			printf("Bz:%d\n", *((short*)(incomingData + 49 + i)));
			printf("本次里程:%d\n", *((short*)(incomingData + 51 + i)));
			printf("GPS授时(hhmmss.sss):%.2d", *((short*)(incomingData + 55 + i)));//5个字节??
			printf(":%.2d", *((short*)(incomingData + 57 + i)));
			printf(":%.2d\n", *((char*)(incomingData + 59 + i)));
			printf("GPS授时(yyyymmdd):%d", *((short*)(incomingData + 60 + i)));
			printf("-%d", *((char*)(incomingData + 62 + i)));
			printf("-%d\n", *((char*)(incomingData + 63 + i)));
			printf("工作状态:%d\n", *((char*)(incomingData + 64 + i)));
			return;
		}
	}
}

void receiveData(void)
{
	int readResult = arduino->readINS(incomingData, MAX_DATA_LENGTH);
	if (!readResult){
		printf("Error to read!");
		return;
	}
	//To Do ...解析数据
	PurgeComm(incomingData, PURGE_RXCLEAR | PURGE_TXCLEAR);
	printData();//打印数据	
	Sleep(1000); //读取的间隔时间
}

//void writeData(unsigned int delayTime)
//{
//    arduino->writeSerialPort(ledON, MAX_DATA_LENGTH);
//    Sleep(delayTime);
//    arduino->writeSerialPort(ledOFF, MAX_DATA_LENGTH);
//    Sleep(delayTime);
//}

int main()
{

    arduino = new INS(/*portName*/);

    //Checking if arduino is connected or not
    if (arduino->isConnected()){
        std::cout << "Connection established at port " << /*portName*/COMPORT << endl;
    }
	else{
		printf("error to connection the port\n");
	}


	/**************Test************/
    #ifdef SEND
        while(arduino->isConnected()) exampleWriteData(BLINKING_DELAY);
    #else // SEND
        while(arduino->isConnected()) receiveData();
    #endif // SEND
}
