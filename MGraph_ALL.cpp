#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int const MAX = 999999;

//边集数组的存储结构
struct VEdge {
	int    fromV;      // 起始顶点
	int    endV;       //终止顶点
	int    weight;    // 边的权值
};

template <class T, int N>
class MGraph
{
public:
	MGraph(const char* filename);  //构造函数
	void DFS_ALL(int v);
	void BFS_ALL(int v);
	void DFS(int v);                 //从v出发深度优先
	void BFS(int v);                  //从v出发广度优先
	
	void CreateTree_Kruskal(VEdge EdgeList[]); //kruskal算法
	void GenSortEdge(VEdge EdgeList[]); 
	
	void CreateTree();//prim算法
	int mininum(int lowcost[]);

	void ShortPath(int v); //最短路径Dijkstral算法
	int FindMin(int Disk[], bool S[], int n);
	void Print(int Disk[], int Path[], int n);

private:
	T vertex[N];
	int arc[N][N];
	int vNum, arcNum;      //顶点数、边数
	bool visited[N];
};

template <class T, int N>
MGraph<T, N>::MGraph(const char* filename)  //构造函数
{
	ifstream in(filename);
	if (in.fail())
		throw "图文件打开失败！";
	in >> vNum >> arcNum;
	for (int i = 0; i < vNum; i++)
		in >> vertex[i];

	memset(arc, 0, N*N * sizeof(int));
	int b, e, w;
	for (int i = 0; i < arcNum; i++)
	{
		in >> b >> e >> w;
		arc[b][e] = w;
		arc[e][b] = w; //无向图
	}
	in.close();
	memset(visited, 0, N * sizeof(bool));
}
template <class T, int N>
void MGraph<T, N>::DFS_ALL(int v)
{
	memset(visited, 0, N * sizeof(bool));
	DFS(v);
	for (int i = 0; i < vNum; i++)
		if (visited[i] == 0)
			DFS(i);

}
//template <class T, int N>
//void MGraph<T, N>::DFS(int v) //deep first search 访问一个连通分量O(n*n)
//{
//	int stack[1024];
//	int top = -1;
//	int i;
//	cout << vertex[v];
//	visited[v] = 1;//访问标记
//	stack[++top] = v;
//	while (top != -1)
//	{
//		for (i = 0; i < vNum; i++) //O(n)
//			if (arc[v][i] == 1 && visited[i] == 0)  //递归模式
//			{
//				v = i;
//				cout << vertex[v]; 	visited[v] = 1;	stack[++top] = v;
//				break;
//			}
//		if (i == vNum) //找不到未访问的邻接点
//		{
//			top--;
//			v = stack[top];
//		}
//	}
//}
template <class T, int N>
void MGraph<T, N>::DFS(int v) //deep first search 访问一个连通分量O(n*n)
{
	/*①从某顶点v出发并访问
	②访问v的第一个未访问的邻接点w，v-->w
	……访问w的第一个未访问的邻接点u，
	③若当前顶点的所有邻接点都被访问过，则回溯，从上一级顶点的下一个未访问过的顶点开始深度优先遍历
	直到所有和v路径相通的顶点都被访问到；*/
	cout << vertex[v];
	visited[v] = 1;//访问标记
	for (int i = 0; i < vNum; i++) //O(n)
		if (arc[v][i] == 1 && visited[i] == 0)  //递归模式
			DFS(i);
	return;
}
template <class T, int N>
void MGraph<T, N> ::BFS_ALL(int v)
{
	memset(visited, 0, N * sizeof(bool));
	BFS(v);
	for (int i = 0; i < vNum; i++)
		if (visited[i] == 0)
			BFS(i);
}
template <class T, int N>
void MGraph<T, N>::BFS(int v) //时间复杂度O(n*n)
{
	int queue[1024];
	int f, r;
	f = r = -1;
	queue[++r] = v;
	while (f != r)
	{
		//队头元素出队
		v = queue[++f];
		cout << vertex[v];
		visited[v] = 1;
		//队头元素的所有未访问过的邻接点入队
		for (int i = 0; i<vNum; i++)
			if (arc[v][i] == 1 && visited[i] == 0)
				queue[++r] = i;
	}
}
template <class T, int N>
void MGraph<T, N>::GenSortEdge(VEdge EdgeList[])//预处理：邻接矩阵-->边集数组
{
	int k = 0, i, j;
	for (i = 0; i < vNum; i++)                        //边集数组初始化
	{
		for (j = i; j < vNum; j++)                  //遍历上三角
			if (arc[i][j] != 0)
			{
				EdgeList[k].fromV = i;
				EdgeList[k].endV = j;
				EdgeList[k].weight = arc[i][j];
				k++;
			}
    }

	for (i = 1; i < arcNum; i++)     //冒泡排序 外循环n-1趟      O（e*e） --> 快速排序算法 O(eloge)
	{
		for (j = 0; j < arcNum - i; j++)   //每一趟排序怎么做？
			if (EdgeList[j].weight > EdgeList[j + 1].weight)//相邻两个顶点比较，大的放后面，小的放前面
			{
				VEdge t = EdgeList[j];                //交换
				EdgeList[j] = EdgeList[j+1];
				EdgeList[j+1] = t;
			}
	}
}
template <class T, int N>
void MGraph<T, N>::CreateTree_Kruskal(VEdge EdgeList[])  //O(n*n)
{
	int vset[N];
	//设置顶点各自独立
	for (int i = 0; i < vNum; i++) 
		vset[i] = i;    
	int k = 0, j = 0;  //k一共取了几条边   j是当前取第几条边

	while (k < vNum - 1)  //O(n)
	{
		int m = EdgeList[j].fromV;
		int n = EdgeList[j].endV;

		int s1 = vset[n];  //n顶点的集合号
		int s2 = vset[m];  //m顶点的集合号
		if (s1 != s2)  //判断这条边可用
		{
			cout << vertex[m] << "-->" << vertex[n] <<"\t"<<arc[m][n]<< endl;
			k++;
			for (int i = 0; i < vNum; i++)  //O(n)
				if (vset[i] == s1)
					vset[i] = s2;
		}
		j++;
	}
}

template <class T, int N>
void MGraph<T, N>::CreateTree()  //Prim
{
	int k = 1;
	int adjvex[N] = {0};  //U集合中的点
	int lowcost[N] = {0}; //U-->V-U集合中的边
	for (int i = 0; i < vNum; i++) //辅助数组存储所有到的编号为Vk的边
	{
		adjvex[i] = k;
		if (arc[k][i]!=0)
			lowcost[i] = arc[k][i];
		else
			lowcost[i] = MAX;
	}

	lowcost[k] = 0;         //初始化U={Vk}

	//Prim算法循环
	for (int i = 1; i < vNum; i++)	                    //循环n-1次
	{
		k = mininum(lowcost);  //求下一个顶点
		cout << vertex[adjvex[k]]<< "-->"<< vertex[k] <<"\t"<<arc[adjvex[k]][k]<< endl;
		lowcost[k] = 0;               //U=U+{Vk}
		
		for (int j = 0; j < vNum; j++)          //设置辅助数组
		{
			if (lowcost[j] != 0 && arc[k][j] !=0 && arc[k][j] < lowcost[j])
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
	for (int i = 0; i<vNum; i++)
	{
		if (lowcost[i] != 0 && lowcost[i]<min)
		{
			min = lowcost[i];
			k = i;
		}
	}
	return k;
}

template <class T, int N>
void MGraph<T, N> ::ShortPath( int v)  //最短路径算法
{
	bool S[N];  //记录顶点i是否已找到最短路径
	int Disk[N]; //记录源点到顶点i的最短路径的长度
	int Path[N];  //记录源点到顶点的路径
	for (int i = 0; i<vNum; i++)              //初始化辅助数组
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

	for (int i = 0; i<vNum-1; i++)
	{     // 寻找离V0最近的顶点
		if ((v = FindMin(Disk, S, vNum)) == -1)  
			return;
		S[v] = true;   //加入S
		for (int j = 0; j<vNum; j++) //更新辅助数组… 	
			if (!S[j] && arc[v][j] !=0 && (Disk[j]>arc[v][j] + Disk[v])) //关键
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
	for (int i = 0; i<n; i++)
	{
		if (!S[i] && min>Disk[i])
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
	for (int i = 0; i<n; i++)
	{
		cout << vertex[i] << ": " << Disk[i] << "\t{" << vertex[i];
		int pre = Path[i];
		while (pre != -1)
		{
			cout << "<--"<<vertex[pre];
			pre = Path[pre];
		}
		cout << "}" << endl;
	}
}


void main()
{
	MGraph<string, 10> g("MSTree.txt");
	//cout << "深度优先遍历：";
	//g.DFS_ALL(2);
	//cout << "\n广度优先遍历：";
	//g.BFS_ALL(0);
	
	cout << "\nKruskal最小生成树：\n";
	VEdge  EdgeList[100];  //kruskal
	g.GenSortEdge(EdgeList);
	g.CreateTree_Kruskal(EdgeList);
	cout << "\nPrim最小生成树：\n";
	g.CreateTree(); 
	cout << "\nDijkstra最短路径：\n";
	g.ShortPath(0);
}
