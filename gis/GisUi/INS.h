#ifndef INS_H
#define INS_H

#define COMPORT				"COM3"

//Qt
#include <qthread.h>
#include <qpoint.h>
#include "qgspoint.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <qdebug.h>


//char* portName = COMPORT; //串口号
#define END    (0xffffffc0)
#define VERIFY    (0xFFFFFFE5)
#define MAX_DATA_LENGTH 1024
#define ARDUINO_WAIT_TIME	2000

class INS :public QThread
{
	Q_OBJECT
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
	char incomingData[MAX_DATA_LENGTH];
    QgsPoint currentPosition;//实时位置

public:
	INS();
    ~INS();
	void run();

    int readINS(char *buffer, unsigned int buf_size);
    bool writeINS(char *buffer, unsigned int buf_size);
    bool isConnected();
	void receiveData(); 
	void printData();
    QgsPoint* get_position();


};

#endif // INS_H
