#include "ins.h"

static int decode(const char* buffer, int size, char* decoded);
static int encode(const char* buffer, int size, char* encoded);
INS::INS(QWidget *parent)
: QMainWindow(parent)
{
	myCom = new QSerialPort(COMPORT);
	if (myCom->open(QIODevice::ReadWrite)){
		//以读写方式打开串口  
		myCom->setBaudRate(QSerialPort::Baud115200);
		//波特率设置，设置为115200  
		myCom->setDataBits(QSerialPort::Data8);
		//数据位设置，设置为8位数据位  
		myCom->setParity(QSerialPort::NoParity);
		//奇偶校验设置，设置为无校验 
		myCom->setStopBits(QSerialPort::OneStop);
		//停止位设置，设置为1位停止位  
		//myCom->setReadBufferSize(MAX_DATA_LENGTH);
	}
	else{
		qDebug("error to open myCom!!!!\n");
	}
}

INS::~INS()
{
	myCom->close();
}

#if 0
int INS::read(INSInfo* insData)
{
	int numRead = 0;
	char incomingData[1024];
	forever{
		numRead = myCom->read(incomingData, MAX_DATA_LENGTH);
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
		myCom->waitForReadyRead(2000);
	}
	return -2;//解析失败
}
#endif

int INS::read(INSInfo* insData)
{
	char incomingData[MAX_DATA_LENGTH], decodeData[MAX_DATA_LENGTH];
	forever{
		myCom->read(incomingData, MAX_DATA_LENGTH);
		decode(incomingData, MAX_DATA_LENGTH, decodeData);
		for (int i = 0; i < MAX_DATA_LENGTH; ++i){
			if (decodeData[0 + i] == VERIFY){
				insData->X = *((int*)(decodeData + i + 1));
				insData->Y = *((int*)(decodeData + i + 5));
				insData->Altitude = *((short*)(decodeData + i + 9));
				insData->Zone = *((char*)(decodeData + i + 11));
				insData->Longitude = *((int*)(decodeData + i + 12));
				insData->Latitude = *((int*)(decodeData + i + 16));
				insData->HeadAngle = *((short*)(decodeData + i + 20));
				insData->PitchAngle = *((short*)(decodeData + i + 22));
				insData->SlantAangle = *((short*)(decodeData + i + 24));
				insData->Vx = *((short*)(decodeData + i + 26));
				insData->Vy = *((short*)(decodeData + i + 28));
				insData->Vz = *((short*)(decodeData + i + 30));
				insData->Wx = *((short*)(decodeData + i + 32));
				insData->Wy = *((short*)(decodeData + i + 34));
				insData->Wz = *((short*)(decodeData + i + 36));
				insData->Ax = *((short*)(decodeData + i + 38));
				insData->Ay = *((short*)(decodeData + i + 40));
				insData->Az = *((short*)(decodeData + i + 42));
				insData->Bx = *((short*)(decodeData + i + 44));
				insData->By = *((short*)(decodeData + i + 46));
				insData->Bz = *((short*)(decodeData + i + 48));
				insData->Mileage = *((int*)(decodeData + i + 50));
				insData->HH = *((short*)(decodeData + i + 54));
				insData->mm = *((short*)(decodeData + i + 56));
				insData->sss = *((char*)(decodeData + i + 58));
				insData->yyyy = *((short*)(decodeData + i + 59));
				insData->MM = *((char*)(decodeData + i + 61));
				insData->dd = *((char*)(decodeData + i + 62));
				insData->Workingstatus = *((char*)(decodeData + i + 63));
				return 0;//成功
			}
		}
		myCom->waitForReadyRead(1000);
	}
	return -1;//失败
}

int INS::formatINSInfo(INSInfo* insData, char* buf, int buf_size){
	int i = 0;
	int j = sizeof(insData);
	if (buf_size < j){
		return -1;
	}
	else{
		i = sprintf_s(buf, buf_size, "坐标X:%d\n", insData->X);
		i += sprintf_s(buf + i, buf_size - i, "坐标Y:%d\n", insData->Y);
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


//1自检
void INS::verify(){
	char buf[20];
	buf[0] = END;
	buf[1] = 0XF0;
	buf[2] = 0XF0;
	buf[3] = END;	

	myCom->write(buf, 4);
}

//2对准
void INS::seeking(){
	char buf[20];
	buf[0] = END;
	buf[1] = 0XF1;
	buf[2] = 0XF1;
	buf[3] = END;

	myCom->write(buf, 4);
}

//3坐标装订
void INS::initPos(int lng, int lat, int H){
	char buf[256] = {}, encodeData[256];
	unsigned char cmd = 0XF6;

	buf[0] = cmd;
	*(int*)&buf[1] = lng;
	*(int*)&buf[5] = lat;
	*(int*)&buf[9] = H;
	buf[13] = cmd ^ lng ^ lat ^ H;

	printf("encodeData begain:\n");
	int res = encode(buf, 14, encodeData);
	for (int i = 0; i < res; ++i)
		printf("%02X ", encodeData[i]);
	printf("encodeData end!\n");
	if (res){
		myCom->write(encodeData, res);
	}
}

//4参数配置
void INS::setConfigure(unsigned char id, int val){
	char buf[256],encodeData[256];
	char cmd = 0XF4;
	buf[0] = cmd;
	buf[1] = id;
	buf[2] = val;
	buf[6] = cmd ^ id ^ val;
	int res = encode(buf, 7, encodeData);
	if (res){
		myCom->write(encodeData, res);
	}
}

//for debug
void INS::getConfigure(unsigned char id){
	char buf[256], encodeData[256];
	char cmd = 0XF3;
	buf[0] = cmd;
	buf[1] = id;
	buf[2] = cmd ^ id ;
	int res = encode(buf, 3, encodeData);
	if (res){
		myCom->write(encodeData, res);
	}
}
//for debug
void INS::read(){
	int numRead = 0;
	char dateverify[1024];
	forever{
		numRead = myCom->read(dateverify, 1024);
		for (int i = 0; i < 1024; i++){
#if 0
			if ((dateverify[0 + i] == END) && (dateverify[1 + i] == 0xffffffe0) && (dateverify[4 + i] == END)){
				printf("当前自检状态：%02X\n", dateverify[2 + i]);
			}
#else
			if ((dateverify[0 + i] == END) && (dateverify[1 + i] == 0xffffffe6) && (dateverify[8 + i] == END)){
				printf("参数设置：序号：%02X 参数值：%d\n", dateverify[2 + i] , *((int*)(dateverify+3 + i))   );
			}
#endif
		}
		myCom->waitForReadyRead(2000);
	}
}
//封装SLIP
static int encode(const char* buffer, int size, char* encoded)
{
	if (size == 0)
		return 0;

	int read_index = 0;
	int write_index = 0;

	encoded[write_index++] = END;

	while (read_index < size)
	{
		if (buffer[read_index] == END)
		{
			encoded[write_index++] = ESC;
			encoded[write_index++] = ESC_END;
			read_index++;
		}
		else if (buffer[read_index] == ESC)
		{
			encoded[write_index++] = ESC;
			encoded[write_index++] = ESC_ESC;
			read_index++;
		}
		else
		{
			encoded[write_index++] = buffer[read_index++];
		}
	}

	encoded[write_index++] = END;
	return write_index;
}
//解析SLIP
static int decode(const char* buffer, int size, char* decoded)
{
	if (size == 0)
		return 0;

	int read_index = 0;
	int write_index = 0;

	while (read_index < size)
	{
		if (buffer[read_index] == END)
		{
			read_index++;
		}
		else if (buffer[read_index] == ESC)
		{
			if (buffer[read_index + 1] == ESC_END)
			{
				decoded[write_index++] = END;
				read_index += 2;
			}
			else if (buffer[read_index + 1] == ESC_ESC)
			{
				decoded[write_index++] = ESC;
				read_index += 2;
			}
		}
		else
		{
			decoded[write_index++] = buffer[read_index++];
		}
	}
	return write_index;
}