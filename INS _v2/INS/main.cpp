#include "INS.h"
#include <string.h>
#include <iostream>


using namespace std;
//char* portName = COMPORT; //´®¿ÚºÅ
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
 
        std::cout << "Connection established at port " << /*portName*/COMPORT << endl;

}
