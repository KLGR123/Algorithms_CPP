#include <iostream>
using namespace std;

void Convert1(int num, int r) //数组
{
	int stack[100];
	int top = -1;
	while (num>0)
	{
		int t = num % r;  //存储
		stack[++top] = t;   //入栈
		num = num / r;
	}
	while (top != -1)
		cout << stack[top--];//出栈
}
void Convert2(int num, int r) //递归
{
	if (num>0)
	{
		int t = num % r;  
		Convert2(num / r, r);
		cout << t;
	}
}

void main()
{
	Convert2(77, 2);
}
