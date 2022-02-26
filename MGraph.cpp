#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <class T, int N>
class MGraph
{
public:
	MGraph(const char* filename);  //构造函数
	void DFS_ALL(int v);              //深度优先遍历所有连通分量
	void BFS(int v);                  //从v出发广度优先
public:
	void DFS(int v);                 //从v出发深度优先,遍历一个连通分量
private:
	T vertex[N];
	int arc[N][N];
	int vNum, arcNum;      //顶点数、边数
	bool visited[N];
};
template <class T, int N>
MGraph<T, N>::MGraph(const char* filename)
{
	ifstream in(filename);
	if (in.fail())
		throw "图文件打开失败！";
	in >> vNum >> arcNum;
	for (int i = 0; i < vNum; i++) //顶点数据
		in >> vertex[i];
	
	memset(arc, 0, N*N * sizeof(int));
	int b, e;
	for (int i = 0; i < arcNum; i++) //邻接矩阵赋值
	{
		in >> b >> e;
		arc[b][e] = 1;
	}
	in.close();
	
}

template <class T, int N>
void MGraph<T, N>::DFS_ALL(int v)
{
	memset(visited, 0, N * sizeof(bool));
	DFS(v);
	for (int i = 0; i < vNum; i++)
		if (visited[i] == 0)    //判断是否还有其他连通分量
			DFS(i);

}
//template <class T, int N>
//void MGraph<T, N>::DFS(int v)                 //从v出发深度优先 deep first search（DFS）
//{
//	/*从某顶点v出发并访问
//		②访问v的第一个未访问的邻接点w，  v-->w?
//		访问w的第一个未访问的邻接点u，
//		……
//		③若当前顶点的所有邻接点都被访问过，则回溯，从上一级顶点的下一个未访问过的顶点开始深度优先遍历
//		直到所有和v路径相通的顶点都被访问到；*/
//		cout << vertex[v];
//		visited[v] = 1;
//		for (int i = 0; i < vNum; i++)
//			if (arc[v][i] == 1 && visited[i] == 0)
//				DFS(i);
//		return;
//}
template <class T, int N>
void MGraph<T, N>::DFS(int v)                 //从v出发深度优先 deep first search（DFS）
{ 
	   /*从某顶点v出发并访问
		②访问v的第一个未访问的邻接点w，  v-->w?
		访问w的第一个未访问的邻接点u，
		……
		③若当前顶点的所有邻接点都被访问过，则回溯，从上一级顶点的下一个未访问过的顶点开始深度优先遍历
		直到所有和v路径相通的顶点都被访问到；*/
	int stack[N];
	int top = -1;
	int i;
	cout << vertex[v];
	visited[v] = 1;
	stack[++top] = v;

	while (top != -1)
	{	
		for (i = 0; i < vNum; i++)   //递归模式
			if (arc[v][i] == 1 && visited[i] == 0)
			{
				v = i; 		cout << vertex[v]; 		visited[v] = 1; 	stack[++top] = v;
				break;
			}
		if (i == vNum) //找不到未访问过的结点，
		{
			top--; //回溯
			v = stack[top];
		}
	}
	return;
}
template <class T, int N>
void MGraph<T, N> :: BFS(int v) //O(n*n)
{
	/*①访问顶点v
		②依次访问v的所有未被访问的邻接点v1, v2, v3…
		③分别从v1, v2, v3…出发依次访问它们未被访问的邻接点
		反复①②③ ，直到所有和v路径相通的顶点都被访问到；*/

	memset(visited, 0, N * sizeof(bool));
	int queue[N];
	int f, r;
	f = r = -1;
	queue[++r] = v;
	while (f != r)
	{
		v = queue[++f];
		cout << vertex[v];
		visited[v] = 1;
		for (int i = 0; i < vNum; i++)
			if (arc[v][i]==1 && visited[i]==0)
				queue[++r] = i;
	}
}
void main()
{
	MGraph<string, 10> g("graphinfo.txt");
	cout << "深度优先遍历：";
	g.DFS_ALL(0);
	cout << "\n广度优先遍历：";
	g.BFS(0);
}
