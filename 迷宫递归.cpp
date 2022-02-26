#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;

struct Point 
{
	int X;
	int Y;
};
//��ӡ��ͼ
void PrintPath(int arr[][10]);
//�ݹ��㷨
int Maze(int arr[][10], Point cur, Point end);
//�ǵݹ��㷨
int next(int arr[][10],Point cur, Point end);
//��̬Ч��
void Gotoxy(int x, int y);  //����ƶ�����x��y��λ��
void HideCursor();//����ʾ���

//�ݹ��ҳ�����·
void nextAll(int arr[][10], Point cur, Point end);
void PrintPath1(int arr[][10]);

//��ͼ
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
	//Maze(arr,cur,end); //�ǵݹ��㷨��ֻ���ҳ�һ��·
	next(arr,cur,end);//�ݹ��㷨 ��ֻ���ҳ�һ��·
	Gotoxy(1,22);
	//nextAll(arr, cur, end);//�ݹ��㷨���ҳ�����·���㷨
	
}

//��겻��ʾ
void HideCursor()
{
	
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//���ÿ���̨���״̬
}
//ָ��λ�����
void Gotoxy(int x, int y)
{
    COORD c;
    c.X = x; 
    c.Y = y;
    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int Maze(int arr[][10],Point cur, Point end)//�ǵݹ�
{
	Point stack[256];
	int top = -1;
	do	
	{
		arr[cur.X][cur.Y] = 2;
		stack[++top] = cur;
		
		//��̬��ʾ��ʼ
		Gotoxy(cur.Y*2, cur.X);       
		cout<<" *";        
		Sleep(500);
		//��̬��ʾ����
		
		if (arr[cur.X + 1][cur.Y] == 0)	cur.X++; 
		else if (arr[cur.X][cur.Y + 1] == 0)	cur.Y++;
		else if (arr[cur.X-1][cur.Y] ==0)	cur.X--;
		else if(arr[cur.X][cur.Y - 1] == 0)  	cur.Y--; 
		else
		{
			arr[cur.X][cur.Y] = 1; // �߲�ͨ

			//��̬��ʾ��ʼ
			Gotoxy(cur.Y*2, cur.X);
			cout<<" 1";
			Sleep(500);
			//��̬��ʾ����
			top--;
			cur.X = stack[top].X;
			cur.Y = stack[top].Y;
			top--;
		}
	}while(top!=-1 && (cur.X != end.X  || cur.Y != end.Y));	
	
	//��̬��ʾ��ʼ
	Gotoxy(cur.Y*2, cur.X);
	cout<<" *";	
	//��̬��ʾ����
	return true;
}


int next(int arr[][10],Point cur, Point end)//�ݹ�
{
		if(cur.X == end.X  && cur.Y == end.Y)  	
		{
			//��̬��ʾ��ʼ
			Gotoxy(cur.Y*2,cur.X);
			cout<<" *";
			//��̬��ʾ����
			return true;
		}
		else
		{
			arr[cur.X][cur.Y] = 2;
			//��̬��ʾ��ʼ
			Gotoxy(cur.Y*2,cur.X);
			cout<<" *";
			Sleep(500);
			//��̬��ʾ����
			
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
			arr[cur.X][cur.Y] = 1; // �߲�ͨ
			//��̬��ʾ��ʼ
			Gotoxy(cur.Y*2,cur.X);
			cout<<" 1";
			Sleep(500);
			//��̬��ʾ����
			return false;
		}
}
void PrintPath(int arr[][10])
{
	for (int i=0;i<10;i++)
	{
		for (int j=0;j<10;j++)
		{
			if (arr[i][j]==-1) cout<<"��";
			else cout<<"��";
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
			if (arr[i][j] == -1) cout << "��";
			else if (arr[i][j] == 2) cout << "* ";
			else cout << "��";
		}
		cout << endl;
	}
	cout << endl;
}
void nextAll(int arr[][10], Point cur, Point end)//�ݹ�
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
		arr[cur.X][cur.Y] = 1; // �߲�ͨ
		
	}
}