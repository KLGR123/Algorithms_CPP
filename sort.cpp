#include <iostream>
#include <fstream>
using namespace std;

//数组存储待排序元素， 0号元素不用
void bubbleSort(int a[], int n)
{
	//两重循环，外循环控制趟数， 内循环处理每一趟怎么做
	int pos = n;
	while (pos > 0) //外循环 n-1趟
	{
		int bound = pos;
		pos = 0;
		for (int j = 1; j < bound; j++)         
		{
			if (a[j] > a[j + 1])
			{
				int t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				pos = j;
			}
		}
	}
}

void InsertSort(int a[], int n)
{
	//两重循环，外循环控制趟数， 内循环处理每一趟怎么做
	for (int i = 2; i <= n; i++) //循环n-1趟
	{
		a[0] = a[i];   //第i趟，a[i]在有序区【1，i-1】 中的位置
		int j;
		for (j = i - 1; a[0] < a[j]; j--)
			a[j + 1] = a[j];  //边比较边后移，最耗时
		a[j + 1] = a[0];
	}
}

void SelectSort(int a[], int n)
{
	//两重循环，外循环控制趟数， 内循环处理每一趟怎么做
	for (int i = 1; i < n; i++)  //n-1趟
	{
		//第i趟 在【i,n】选择最小数，放在i的位置
		int min = i; 
		for (int j = i + 1; j <= n; j++)
			if (a[j] < a[min])
				min = j;
		if (min != i)
		{
			int t = a[i];
			a[i] = a[min];
			a[min] = t;
		}

	}
}

int Partion(int a[], int first, int end)
{
	int pivot = a[first];//轴值
	int i = first; //从前到后遍历， 找比轴值大的数
	int j = end;   //从后向前遍历，找比轴值小的数

	while(i<j)
	{
		//从后向前找，找比轴值小的数
		while (a[j] >= pivot && i<j) j--;
		a[i] = a[j];
		//从前到后遍历， 找比轴值大的数
		while (a[i] <= pivot && i<j) i++;
		a[j] = a[i];
	}
	a[i] = pivot;
	return i;
}

void QuickSort(int a[], int first, int end)
{
	if (first < end)
	{
		int k = Partion(a, first, end);
		QuickSort(a, first, k - 1);
		QuickSort(a, k + 1, end);
	}
}

void main()
{
	int a[] = { 0,5,2,7,3,1,4,9,6,10,8 };
	QuickSort(a, 1,10);
	for (int i = 1; i < 11; i++)
		cout << a[i] << endl;

}
