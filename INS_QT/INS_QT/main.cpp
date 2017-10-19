#include "ins.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	INS *ins = new INS();
	INSInfo* insData = new INSInfo;

	//printf("----------------test-verify-----------------\n");
	//ins->verify();//ok
	//printf("----------------test-seeking-----------------\n");
	//ins->seeking();//ok
	//printf("----------------test-setConfigure-----------------\n");
	//ins->setConfigure(1, 1);
	//printf("----------------test-getConfigure-----------------\n");
	//ins->getConfigure(9);

	printf("----------------test-initpos-----------------\n");
	ins->initPos(110, 88,  10);	
	_sleep(5000);
	getchar();
	while (1){
#if 0
		system("cls");

		int result = ins->read(insData);
		if (result){
			printf("Error to read!\n");
			break;
		}
		else{
			printf("Connection established at port %s\n", COMPORT);
		}

		char p[1024] = {};
		result = ins->formatINSInfo(insData, p, 1024);
		if (!result){
			printf("success to formatINSInfo!\n");
		}	
		printf("%s\n", p);

		_sleep(1000);
#else
		printf("---------------test-read-------------------\n");
		ins->read();//for debug
#endif
	}
	delete insData;
	return a.exec();
}
