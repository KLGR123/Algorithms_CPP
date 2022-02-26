#include <iostream>
using namespace std;

void Hanoi(int n, char A, char B, char C)//A源 C目标   B辅助
{
	if (n == 1)
		cout << A <<"-->" <<n<<"-->" << C << endl;
	else
	{
		//n->n-1 : 2步骤
		Hanoi(n - 1, A, C, B);
		cout << A << "-->" << n << "-->" << C << endl;
		Hanoi(n - 1, B, A, C);
	}
}

void main()
{
	Hanoi(4, 'A', 'B', 'C');
}