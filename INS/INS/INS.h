#ifndef INS_H
#define INS_H

#define ARDUINO_WAIT_TIME	2000
#define MAX_DATA_LENGTH		255
#define COMPORT				"COM3"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class INS
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
public:
	INS(/*char *portName*/);
    ~INS();


    int readINS(char *buffer, unsigned int buf_size);
    bool writeINS(char *buffer, unsigned int buf_size);
    bool isConnected();
};

#endif // INS_H
