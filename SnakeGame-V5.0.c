#include<stdio.h>
#include<conio.h>
#include<windows.h>										//光标定位函数的头文件
#include<time.h>                						// 日期和时间头文件

const int SNAKE_LENGTH = 3;//设置一个常量

//定义全局变量
char Dire=77;//方向
int WaitTime=1000;//等待时间

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

void Init()//初始化界面
	{	
	system("title 贪吃蛇");//设置窗口的标题
	system("mode con: cols=100 lines=40");//调整控制台的宽高各//可以把游戏窗口看做是40*40的网格，坐标从0-39 
	PInterface();
	}

void InitSnake(int (*Snake)[2],int SnakeLength)//初始化蛇身
	{
	int i;
	for(i=SnakeLength-1;i>=0;i--)//遍历蛇身
		{
		*(Snake[i]+0) = 12-i;//设置初始值
		*(Snake[i]+1) = 4;
		//设置颜色
		SetColor(10);
		PBox(*(Snake[i]+0),*(Snake[i]+1));//打印身体
		}
	}

void Clear(int x,int y)//清除x，y处的字符
	{
	Goto(x,y);
	putchar('\0');
	}

void NextStape(int *Sx,int *Sy)//根据方向确定下一步的x，y
	{
	switch (Dire)
	  {
	  case 72: (*Sy)--;break; //上
	  case 80: (*Sy)++;break; //下
	  case 75: (*Sx)--;break; //左
	  case 77: (*Sx)++;break; //右
	  }
	}

void MoveSnake(int Sx,int Sy,int (*Snake)[2],int SnakeLength)  //移动蛇到指定的点
	{
	int j;
	Clear(*(Snake[SnakeLength-1]+0),*(Snake[SnakeLength-1]+1));//清除蛇尾
	for(j=SnakeLength;j>=2;j--)//遍历蛇身
		{
		*(Snake[j-1]+0) = *(Snake[j-2]+0); //把蛇身坐标依次从后往前传递
		*(Snake[j-1]+1) = *(Snake[j-2]+1);
		}
	*(Snake[0]+0)=Sx;//给蛇头赋值
	*(Snake[0]+1)=Sy;
	SetColor(10);
	PBox(*(Snake[0]+0),*(Snake[0]+1));  //打印蛇头
	}

//线程监听键盘输入
DWORD WINAPI ListenKey( LPVOID lpParam )				//检测键盘的敲击
	{
    for(;;)
      {
	  char flag = getch();//获取键盘信息
	  switch(flag)
			{
			case 72: if(Dire!=80)//判读输入的值，是否与当前值方向相反
						{Dire=flag;WaitTime=0;break;}//如果不相反，改变方向，重置等待时间，跳出switch
                     else  
						{break;}
			case 80: if(Dire!=72) 
						{Dire=flag;WaitTime=0;break;}
                     else 
						{break;}
			case 75: if(Dire!=77) 
						{Dire=flag;WaitTime=0;break;}
                     else  
						{break;}
			case 77: if(Dire!=75) 
						{Dire=flag;WaitTime=0;break;}
                     else  
						 {break;}
			}
		}
	   return 0;
	}

int main(void){
	int Snake[400][2];
	int SnakeLength = SNAKE_LENGTH;//初始化蛇身长度
	int i;
	clock_t NowTime; //声明时间变量
	CreateThread( NULL, 0,ListenKey, 0, 0, 0 );   //使用CreateThread方法开启线程，让开启的线程执行ListenKey方法
	Init(); //初始化界面
	InitSnake(Snake,SnakeLength);//Snake是按地址调用，初始化蛇身
	for(i=0;;i++) //主循环
		{
		int Sx = Snake[0][0];//取出蛇头的坐标
		int Sy = Snake[0][1];
		if(WaitTime==0)//还原WaitTime
			{
			WaitTime=1000;
			}
		//Sx++;
		NextStape(&Sx,&Sy);//根据方向，计算下步蛇头位置	
		MoveSnake(Sx,Sy,Snake,SnakeLength);//移动蛇身体
		NowTime=clock();//获取当前时间
		for(;clock()-NowTime<WaitTime;){}	//计时器，用当前时间减去上面获取的时间与等待时间比较
		}
	getch();
	return 0;
}
