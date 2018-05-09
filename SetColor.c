#include<stdio.h>
#include<conio.h>
#include<windows.h>	

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

void PCircle(int x,int y)//在x，y处打印圆
	{
	Goto(x,y);
	printf("●");
	}

int main(void)
	{
	int i;
	system("title 设置颜色");
	system("mode con: cols=80 lines=40");
	
	for(i=0;i<15;i++)
		{
			SetColor(i);
			Goto(4,i);
			printf("%d",i);
			PCircle(5,i);
		}
	getch();
	return 0;
	}
