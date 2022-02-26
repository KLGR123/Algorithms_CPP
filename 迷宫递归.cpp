#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;

struct Point 
{
	int X;
	int Y;
};
//打印地图
void PrintPath(int arr[][10]);
//递归算法
int Maze(int arr[][10], Point cur, Point end);
//非递归算法
int next(int arr[][10],Point cur, Point end);
//动态效果
void Gotoxy(int x, int y);  //光标移动到（x，y）位置
void HideCursor();//不显示光标

//递归找出所有路
void nextAll(int arr[][10], Point cur, Point end);
void PrintPath1(int arr[][10]);

//地图
int arr[10][10]={
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
{-1, 0, 0,-1, 0, 0, 0,-1, 0,-1},
{-1, 0, 0, 0, 0,-1,-1, 0, 0,-1},
{-1, 0,-1,-1,-1, 0, 0, 0, 0,-1},
{-1, 0, 0, 0,-1, 0, 0, 0, 0,-1},
{-1, 0,-1, 0, 0, 0,-1, 0, 0,-1},
{-1, 0,-1, 0, 0, 0,-1, 0, 0,-1},
{-1, 0,-1,-1,-1, 0,-1,-1, 0,-1},
{-1,-1,	0, 0 ,0, 0, 0, 0, 0,-1},
{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};


void main()
{
	Point cur={1,1};
	Point end={8,8};
	HideCursor();
	PrintPath(arr);
	//Maze(arr,cur,end); //非递归算法：只能找出一条路
	next(arr,cur,end);//递归算法 ：只能找出一条路
	Gotoxy(1,22);
	//nextAll(arr, cur, end);//递归算法：找出所有路的算法
	
}

//光标不显示
void HideCursor()
{
	
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//设置控制台光标状态
}
//指定位置输出
void Gotoxy(int x, int y)
{
    COORD c;
    c.X = x; 
    c.Y = y;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int Maze(int arr[][10],Point cur, Point end)//非递归
{
	Point stack[256];
	int top = -1;
	do	
	{
		arr[cur.X][cur.Y] = 2;
		stack[++top] = cur;
		
		//动态显示开始
		Gotoxy(cur.Y*2, cur.X);       
		cout<<" *";        
		Sleep(500);
		//动态显示结束
		
		if (arr[cur.X + 1][cur.Y] == 0)	cur.X++; 
		else if (arr[cur.X][cur.Y + 1] == 0)	cur.Y++;
		else if (arr[cur.X-1][cur.Y] ==0)	cur.X--;
		else if(arr[cur.X][cur.Y - 1] == 0)  	cur.Y--; 
		else
		{
			arr[cur.X][cur.Y] = 1; // 走不通

			//动态显示开始
			Gotoxy(cur.Y*2, cur.X);
			cout<<" 1";
			Sleep(500);
			//动态显示结束
			top--;
			cur.X = stack[top].X;
			cur.Y = stack[top].Y;
			top--;
		}
	}while(top!=-1 && (cur.X != end.X  || cur.Y != end.Y));	
	
	//动态显示开始
	Gotoxy(cur.Y*2, cur.X);
	cout<<" *";	
	//动态显示结束
	return true;
}


int next(int arr[][10],Point cur, Point end)//递归
{
		if(cur.X == end.X  && cur.Y == end.Y)  	
		{
			//动态显示开始
			Gotoxy(cur.Y*2,cur.X);
			cout<<" *";
			//动态显示结束
			return true;
		}
		else
		{
			arr[cur.X][cur.Y] = 2;
			//动态显示开始
			Gotoxy(cur.Y*2,cur.X);
			cout<<" *";
			Sleep(500);
			//动态显示结束
			
			if (arr[cur.X][cur.Y+1] ==0)
			{
				Point t=cur; 			
				t.Y++;		
				if (next(arr,t,end)) return true;
			}
			if (arr[cur.X-1][cur.Y] ==0)
			{
				Point t=cur;
				t.X--;							
				if (next(arr,t,end)) return true;
			}
			if (arr[cur.X][cur.Y-1] ==0)
			{
				Point t=cur; 
				t.Y--;							
				if (next(arr,t,end)) return true;
			}
			if (arr[cur.X + 1][cur.Y] == 0)
			{
				Point t = cur;
				t.X++;
				if (next(arr, t, end)) return true;
			}
			arr[cur.X][cur.Y] = 1; // 走不通
			//动态显示开始
			Gotoxy(cur.Y*2,cur.X);
			cout<<" 1";
			Sleep(500);
			//动态显示结束
			return false;
		}
}
void PrintPath(int arr[][10])
{
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			if (arr[i][j]==-1) cout<<"■";
			else cout<<"□";
		}
		cout<<endl;
	}
	cout<<endl;
}
void PrintPath1(int arr[][10])
{
	for (int i = 0; i<10; i++)
	{
		for (int j = 0; j<10; j++)
		{
			if (arr[i][j] == -1) cout << "■";
			else if (arr[i][j] == 2) cout << "* ";
			else cout << "□";
		}
		cout << endl;
	}
	cout << endl;
}
void nextAll(int arr[][10], Point cur, Point end)//递归
{
	if (cur.X == end.X  && cur.Y == end.Y)
	{
		arr[end.X][end.Y] =2;
		PrintPath1(arr);
		Sleep(200);
		arr[end.X][end.Y] = 0;
	}
	else
	{
		arr[cur.X][cur.Y] = 2;
		if (arr[cur.X][cur.Y + 1] == 0)
		{
			Point t = cur;
			t.Y++;
			nextAll(arr, t, end);
			arr[cur.X][cur.Y + 1] = 0;
		}
		if (arr[cur.X - 1][cur.Y] == 0)
		{
			Point t = cur;
			t.X--;
			nextAll(arr, t, end);
			arr[cur.X - 1][cur.Y] = 0;
		}
		if (arr[cur.X][cur.Y - 1] == 0)
		{
			Point t = cur;
			t.Y--;
			nextAll(arr, t, end);
			arr[cur.X][cur.Y - 1] = 0;
		}
		if (arr[cur.X + 1][cur.Y] == 0)
		{
			Point t = cur;
			t.X++;
			nextAll(arr, t, end);
			arr[cur.X+1][cur.Y] = 0;
		}
		arr[cur.X][cur.Y] = 1; // 走不通
		
	}
}