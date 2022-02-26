#define MAXTERM 100
template <class T> struct  SparseMatrix
{
	struct element
	{
		int   row;
		int   col;
		T     item;
	};
	element data[MAXTERM];
	int m, n, t;  //行数、列数、非零元素数
};

void Transpose(SparseMatrix<int> A, SparseMatrix<int> &B)
{
	//初始化相关信息
	B.m = A.n;   //行数
	B.n = A.m;   //列数
	B.t = A.t;     //非零元素数
	if (B.t>0)
	{
		//① 开始三元组转置
		int k = 0;
		for (int i=0; i<A.m; i++)
			for (int j = 0; j < A.t; j++)
			{
				if (A.data[j].col == i)
				{
					B.data[k].item = A.data[j].item;
					B.data[k].row = A.data[j].col;
					B.data[k].col = A.data[j].row;
					k++;
				}
			}
	}
}
void Transpose(SparseMatrix<int> A, SparseMatrix<int> &B)//O(m+2t) O(m+t)
{
	//初始化相关信息
	B.m = A.n;   //行数
	B.n = A.m;   //列数
	B.t = A.t;     //元素数
	int number[100] = { 0 };
	int position[100] = { 0 };
	if (B.t>0)
	{
		//① //初始化附设数组
		for (int i = 0;i < A.t; i++)   //O(t)
			number[A.data[i].col]++;
		position[0] = 0;
		for (int i = 1; i < A.m; i++) //O(m)
			position[i] = position[i - 1] + number[i - 1];

		//②//扫描A，将A中元素交换行、列存储到B中
		for (int i = 0; i< A.t; i++)   //O(t)
		{
			int k = position[A.data[i].col];
			B.data[k].item = A.data[i].item;
			B.data[k].row = A.data[i].col;
			B.data[k].col = A.data[i].row;
			position[A.data[i].col]++;
		}
	}
}
