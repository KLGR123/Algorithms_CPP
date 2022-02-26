//矩阵乘法 按行优先
void Matrix(int a[][2], int b[][4], int c[][4], int m, int n, int p)
{
	//C[m][p]
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
		{
			c[i][j] = 0;   //问题转化
			for (int k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}


//朴素的模式匹配算法
int BF(char S[], char T[])
{
	int i = 0, j = 0;
	while (T[j]!='\0' && S[i]!='\0')
	{
		//1 什么情况下继续比较后继字符
		if (S[i]==T[j])	{
			i++; j++;
		}
		else//2 什么情况下指针后退重新开始匹配
		{
			i = i-j + 1;//本次比较起始位置的下一个位置下标
			j = 0;
		}
	}
	//3  输出匹配结果
	if (T[j] != '\0') return i - j + 1;//本次比较起始位置，不是下标;
	return 0;
}