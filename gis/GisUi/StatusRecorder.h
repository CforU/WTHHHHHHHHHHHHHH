#ifndef __STATUSRECODER_H__
#define __STATUSRECODER_H__

#include <qmap.h>
#include <qlist.h>

// StatusRecorder 状态记录机 用于记录按键的操作流 用于高亮显示和返回

//记录重要的按键  1 状态栏切换 2 按键切换 
//按键正常为ture 按下为false	

class StatusRecorder
{
public:
	StatusRecorder();
	~StatusRecorder();
	enum btnCode{

	};
	//QList<QMap<enum btnCode, bool status> >  rcording;//记录链表
	//Map记录按键键值和 按键状态 按键正常为ture 按下为false	

	QList<QMap<enum btnCode, bool> >  rcording;//记录链表 
	bool  rFlags;//返回标志  真需要返回  false 无需返回
	static void recode();//  记录一条记录 //static  //记录重要的按键  1 状态栏切换 2 按键切换 
	static void returns();// 处理返回    //static  //通过标志位从后往前处理每一个返回，  提前定义好返回的操作

};
#endif __STATUSRECODER_H__