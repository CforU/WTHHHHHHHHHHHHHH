#include "ScaleWidget.h"
#include "qdebug.h"

ScaleWidget::ScaleWidget(QWidget *parent) :
QWidget(parent)
{
	
}

ScaleWidget::~ScaleWidget()
{

}

void ScaleWidget::getData(int as, int sbw){

	myActualSize = as;
	myScaleBarWidth = sbw;
}

void ScaleWidget::paintEvent(QPaintEvent* event){

	QPainter* theQPainter = new QPainter(this);
	//theQPainter->setPen(Qt::blue); //设置画笔为灰色
	//theQPainter->drawLine(0, 10, 10, 10); //(0, 0)为初始坐标，（100, 100）为最终坐标

	//Get type of map units and set scale bar unit label text
	QString myScaleBarUnitLabel;

	if (myActualSize > 1000.0)
	{
		myScaleBarUnitLabel = tr(" km");
		myActualSize = myActualSize / 1000;
	}
	else if (myActualSize < 0.01)
	{
		myScaleBarUnitLabel = tr(" mm");
		myActualSize = myActualSize * 1000;
	}
	else if (myActualSize < 0.1)
	{
		myScaleBarUnitLabel = tr(" cm");
		myActualSize = myActualSize * 100;
	}
	else
		myScaleBarUnitLabel = tr(" m");

	//Set font and calculate width of unit label
	int myFontSize = 10; //we use this later for buffering
	QFont myFont("helvetica", myFontSize);
	theQPainter->setFont(myFont);
	QFontMetrics myFontMetrics(myFont);
	double myFontWidth = myFontMetrics.width(myScaleBarUnitLabel);
	double myFontHeight = myFontMetrics.height();

	//Calculate total width of scale bar and label
	double myTotalScaleBarWidth = myScaleBarWidth + myFontWidth;

	int myOriginX = 10;
	int myOriginY = 20;

	/////////////////////////////////////////


	//Cast myScaleBarWidth to int for drawing
	int myScaleBarWidthInt = static_cast< int >(myScaleBarWidth);
	//		绘制Tick UP
	//Set pen to draw with
	QPen myForegroundPen(Qt::green, 2);
	QPen myBackgroundPen(Qt::white, 4);

	QPolygon myTickUpArray(4);
	//draw a buffer first so bar shows up on dark images
	theQPainter->setPen(myBackgroundPen);
	myTickUpArray.putPoints(0, 4,
		myOriginX, myOriginY,
		myOriginX, myOriginY + 8,
		myScaleBarWidthInt + myOriginX, myOriginY + 8,
		myScaleBarWidthInt + myOriginX, myOriginY
		);
	theQPainter->drawPolyline(myTickUpArray);
	//now draw the bar itself in user selected color
	theQPainter->setPen(myForegroundPen);
	myTickUpArray.putPoints(0, 4,
		myOriginX, myOriginY,
		myOriginX, myOriginY + 8,
		myScaleBarWidthInt + myOriginX, myOriginY + 8,
		myScaleBarWidthInt + myOriginX, myOriginY
		);
	theQPainter->drawPolyline(myTickUpArray);

	//////////////////////////////////////////

	//  	绘制比例尺
	//Do drawing of scale bar text
	//
	int myBufferSize = 1; //softcode this later
	QColor myBackColor = Qt::white;
	QColor myForeColor = Qt::black;

	//Draw the minimum label buffer
	theQPainter->setPen(myBackColor);
	myFontWidth = myFontMetrics.width("0");
	myFontHeight = myFontMetrics.height();

	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(int(i + (myOriginX - (myFontWidth / 2))),
				int(j + (myOriginY - (myFontHeight / 4))),
				"0");
		}
	}

	//Set the maximum label
	QString myScaleBarMaxLabel = QLocale::system().toString(myActualSize);

	//Draw minimum label
	theQPainter->setPen(myForeColor);

	theQPainter->drawText(
		int(myOriginX - (myFontWidth / 2)),
		int(myOriginY - (myFontHeight / 4)),
		"0"
		);

	//
	//Draw maximum label
	//
	theQPainter->setPen(myBackColor);
	myFontWidth = myFontMetrics.width(myScaleBarMaxLabel);
	myFontHeight = myFontMetrics.height();
	//first the buffer
	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(int(i + (myOriginX + myScaleBarWidthInt - (myFontWidth / 2))),
				int(j + (myOriginY - (myFontHeight / 4))),
				myScaleBarMaxLabel);
		}
	}
	//then the text itself
	theQPainter->setPen(myForeColor);
	theQPainter->drawText(
		int(myOriginX + myScaleBarWidthInt - (myFontWidth / 2)),
		int(myOriginY - (myFontHeight / 4)),
		myScaleBarMaxLabel
		);

	//绘制单位标签
	//Draw unit label 
	//
	theQPainter->setPen(myBackColor);
	//first the buffer
	for (int i = 0 - myBufferSize; i <= myBufferSize; i++)
	{
		for (int j = 0 - myBufferSize; j <= myBufferSize; j++)
		{
			theQPainter->drawText(i + (myOriginX + myScaleBarWidthInt + 3),
				j + (myOriginY + 8),
				myScaleBarUnitLabel);
		}
	}
	//then the text itself
	theQPainter->setPen(myForeColor);
	theQPainter->drawText(
		(myOriginX + myScaleBarWidthInt + 3),
		(myOriginY + 8),
		myScaleBarUnitLabel
		);
}