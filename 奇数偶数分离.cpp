#include <iostream>
using namespace std;
void  odd2Even(int a[], int n) //时间复杂度O（n）
{
	int i = 0;
	int j = n - 1;

	while (i<j)
	{
		while ((i<j) && (a[i] % 2 == 1)) i++;
		while ((i<j) && (a[j] % 2 == 0)) j--;
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}
void main()
{
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	odd2Even(a,10);
	for (int i = 0; i < 10; i++)
		cout << a[i] << endl;
		
}