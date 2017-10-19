#include "INS.h"

int main()
{
	INS* ins = new INS(COMPORT);
	INSInfo* insData = new INSInfo;

	printf("----------------test-verify-----------------\n");
	ins->verify();//ok
	//printf("----------------test-seeking-----------------\n");
	//ins->seeking();//ok
	//printf("----------------test-initpos-----------------\n");
	//ins->initPos(110, 88, 10);//×ø±ê×°¶©
	//Sleep(1000);

	while (1){
		system("cls");//ÇåÆÁ
#if 1	
		printf("---------------------read-------------------------\n");
		Sleep(1000);
		ins->read();
		printf("---------------------end-------------------------\n");
		Sleep(1000);

#else
		int result = ins->read(insData);
		if (result){
			printf("Error to read!\n");
		}
		else{
			printf("Connection established at port %s\n", COMPORT);
		}

		/***********TEST*****************/
		char p[1024] = {};
		result = ins->formatINSInfo(insData, p, 1024);
		if (!result){
			printf("success to formatINSInfo!\n");
		}
		printf("%s\n", p);
		Sleep(1000);
#endif
	}
	delete insData;
	return 0;
}
