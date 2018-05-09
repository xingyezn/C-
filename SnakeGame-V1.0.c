#include<stdio.h>
#include<conio.h>
#include<windows.h>										//光标定位函数的头文件

void Hide_Cursor(HANDLE hConsole)				                    	// 隐藏光标 固定函数
	{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(hConsole, &cursor_info);
	}

void Goto(int x, int y)//定义光标函数 输入要显示得到x坐标，y坐标，坐标原点为程序窗口左上角，向下为y轴，向右为x轴
	{
	short a=(short)x*2;									//*2保证xy是1:1的转换，把x的扩大二倍，因为用的打印的方块都是占一个字符
	COORD pos = {a, (short)y };		        	      // 定义一个字符在控制台屏幕上的坐标POS
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取标准输出的句柄
	SetConsoleCursorPosition(hConsole, pos);	    	// 定位光标位置的函数<windows.h>
	Hide_Cursor(hConsole);
	}

void SetColor(int color)		                    	// 设置颜色，打印的颜色，前景，就近原则
	{	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);		// 是API设置字体颜色和背景色的函数
													// 格式：SetConsoleTextAttribute(句柄,颜色);
	}

void PBox(int x,int y)//在x，y处打印方块
	{
	Goto(x,y);
	printf("■");
	}

void PInterface()//打印界面
	{
	int i=0;
	SetColor(15);//设置颜色
	for(;i<50;i++)
	{
	if(i<=39)
		{	
		PBox(0,i);//打印竖线
		PBox(39,i);
		PBox(49,i);
		PBox(i,0);//打印横线
		PBox(i,39);
		}
	else
		{	
		PBox(i,0);//打印竖线
		PBox(i,39);
		}	
	}
	Goto(42,4);//打印信息
	printf("贪吃蛇游戏");
	Goto(42,33);
	printf("上下左右");
	Goto(42,35);
	printf("控制移动");
	}

//初始化界面
void Init()
	{	
	system("title 贪吃蛇");//设置窗口的标题
	system("mode con: cols=100 lines=40");//调整控制台的宽高各//可以把游戏窗口看做是40*40的网格，坐标从0-39 
	PInterface();
	}


int main(void){
	Init(); //初始化界面
	getch();
	return 0;
}
