#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int const MAX = 999999;

struct node //构造节点
{
	int col, w; //某元素对应列索引，对应权值
	node(int a, int b) { col = a; w = b; } //构造函数
	bool operator < (const node& a) const //预定义,std::<bitset>本身没有重载,自动排序前需重载 operator < 方法
	{
		if (w == a.w)			 //当两节点权值相同，按列靠前优先
			return col < a.col;
		else					 //权值不同，比较后权值小的在栈顶
			return w > a.w;
	}
};

template <class T, int N>
class MGraph
{
public:
	MGraph(const char* filename);  //构造函数
	void CreateTree(int k); //prim算法
	int mininum(int lowcost[]);

	void ShortPath(int v); //Dijkstral算法
	void ShortPath2(int v); //改进Dijkstral算法
	int FindMin(int Disk[], bool S[], int n);
	void Print(int Disk[], int Path[], int n); //打印路径

private:
	T vertex[N];
	int arc[N][N];
	int vNum, arcNum; //顶点数、边数
	vector<node> eg[N]; //node节点构成的向量组
};

template <class T, int N>
MGraph<T, N>::MGraph(const char* filename)  //构造函数
{
	ifstream in(filename);
	if (in.fail())
		throw "图文件打开失败！";
	in >> vNum >> arcNum;
	for (int i = 0; i < vNum; i++)
	{
		in >> vertex[i];
		eg[i].clear();
	}

	memset(arc, 0, N * N * sizeof(int));
	int b, e, w;
	for (int i = 0; i < arcNum; i++)
	{
		in >> b >> e >> w;
		arc[b][e] = w; //写入邻接矩阵
		eg[b].push_back(node(e, w)); //写入vector内节点，过程与矩阵写入类似

		arc[e][b] = w; //无向图对称
		eg[e].push_back(node(b, w));
	}
	in.close();
}

template <class T, int N>
void MGraph<T, N>::CreateTree(int k)  //Prim算法
{
	int adjvex[N] = { 0 };   //U集合中的点
	int lowcost[N] = { 0 };  //U-->V-U集合中的边
	for (int i = 0; i < vNum; i++) //辅助数组存储编号为Vk的边
	{
		adjvex[i] = k;
		if (arc[k][i] != 0)
			lowcost[i] = arc[k][i];
		else
			lowcost[i] = MAX;
	}

	lowcost[k] = 0;         //初始化点集 U = { Vk }

	for (int i = 1; i < vNum; i++)
	{
		k = mininum(lowcost);  //求下一个顶点
		cout << vertex[adjvex[k]] << "-->" << vertex[k] << "\t" << arc[adjvex[k]][k] << endl;
		lowcost[k] = 0;   //U = U + {Vk}

		for (int j = 0; j < vNum; j++)  //设置辅助数组
		{
			if (lowcost[j] != 0 && arc[k][j] != 0 && arc[k][j] < lowcost[j]) //刷新条件为新边存在且更短
			{
				lowcost[j] = arc[k][j];
				adjvex[j] = k;
			}
		}
	}
}

template <class T, int N>
int MGraph<T, N> ::mininum(int lowcost[]) //Prim算法中找出最小生成树的下一个顶点
{
	int min = MAX;	int k = 0;
	for (int i = 0; i < vNum; i++)
	{
		if (lowcost[i] != 0 && lowcost[i] < min)
		{
			min = lowcost[i];
			k = i;
		}
	}
	return k; //返回最小值对应的索引
}

template <class T, int N>
void MGraph<T, N> ::ShortPath(int v)  //Dijkstra最短路径算法 时间复杂度o(n^2)
{
	bool S[N];    //记录顶点i是否已找到最短路径
	int Disk[N];  //记录源点到顶点i的最短路径的长度
	int Path[N];  //记录源点到顶点的路径
	for (int i = 0; i < vNum; i++)              //初始化辅助数组
	{
		S[i] = false;
		if (arc[v][i] == 0)
			Disk[i] = MAX;
		else
			Disk[i] = arc[v][i];

		if (Disk[i] != MAX)
			Path[i] = v;
		else
			Path[i] = -1;        //无前驱
	}
	S[v] = true;
	Disk[v] = 0;               //初始化V0顶点∈S 

	for (int i = 0; i < vNum - 1; i++)
	{     // 寻找离V0最近的顶点
		if ((v = FindMin(Disk, S, vNum)) == -1)
			return;
		S[v] = true;   //加入S
		for (int j = 0; j < vNum; j++) //更新辅助数组 	
			if (!S[j] && arc[v][j] != 0 && (Disk[j] > arc[v][j] + Disk[v])) //更新条件为新点到目标距离小于当前目标距离
			{
				Disk[j] = arc[v][j] + Disk[v];
				Path[j] = v;
			}
	}
	Print(Disk, Path, vNum);
}

template <class T, int N>
int MGraph<T, N> ::FindMin(int Disk[], bool S[], int n)  //找出DISK中距离最短的一条路径
{
	int k = 0, min = MAX;
	for (int i = 0; i < n; i++)
	{
		if (!S[i] && min > Disk[i])
		{
			min = Disk[i];	k = i;
		}
	}
	if (min == MAX) return -1;
	return k;
}

template <class T, int N>
void MGraph<T, N> ::Print(int Disk[], int Path[], int n) //输出路径
{
	for (int i = 0; i < n; i++)
	{
		cout << vertex[i] << ": " << Disk[i] << "\t{" << vertex[i];
		int pre = Path[i];
		while (pre != -1)
		{
			cout << "<--" << vertex[pre];
			pre = Path[pre];
		}
		cout << "}" << endl;
	}
}

template<class T, int N>
void MGraph<T, N>::ShortPath2(int v) //基于Dijkstra的优化算法，时间复杂度降低为o(n*logn)
{
	int Disk[N];
	for (int i = 0; i <= vNum; i++)
		Disk[i] = MAX;

	Disk[v] = 0;

	priority_queue<node> q; //用优先队列优化，自动排序
	q.push(node(v, Disk[v])); //起点入队
	while (!q.empty()) //o(n*logn)
	{
		node front = q.top(); //访问队头，一定是最小边
		q.pop();
		for (int i = 0; i < eg[front.col].size(); i++) //更新辅助数组
		{
			node t = eg[front.col][i]; //队头的邻接元素
			if (Disk[t.col] > front.w + t.w) //原理与D算法相同
			{
				Disk[t.col] = front.w + t.w;
				q.push(node(t.col, Disk[t.col])); //o(logn)更新队列，原理为二叉堆存储
			}
		}
	}
	//直接打印
	for (int i = 0; i < vNum; i++)
		cout << vertex[i] << ":" << Disk[i] << endl;
}

void main()
{
	MGraph<string, 10> g("MSTree.txt");
	cout << "\nPrim最小生成树：\n";
	g.CreateTree(1);
	cout << "\nDijkstra最短路径：\n";
	g.ShortPath(0);
	cout << "\n改进算法最短路径：(路径同上)\n";
	g.ShortPath2(0);
}
