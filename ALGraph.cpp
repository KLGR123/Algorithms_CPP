#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ArcNode
{
	int adjvex;
	ArcNode *nextArc;
};
template <class T>
struct VertexNode
{
	T vertex;
	ArcNode *firstArc;
};

template <class T, int N> 
class ALGraph
{
public:
	ALGraph(const char* filename);  //构造函数
	void DFS_ALL(int v);
	void DFS(int v);                 //从v出发深度优先
	void BFS_ALL(int v);                  //从v出发广度优先
	void BFS(int v);                  //从v出发广度优先
	~ALGraph();
private:
	VertexNode<T> adjlist[N];
	int vNum, arcNum;      //顶点数、边数
	bool visited[N];
};
template <class T, int N>
ALGraph<T, N>::ALGraph(const char* filename)  //构造函数
{
	ifstream in(filename);
	if (in.fail())
		throw "图文件打开失败！";
	in >> vNum >> arcNum;
	for (int i = 0; i < vNum; i++)
	{
		in >> adjlist[i].vertex;
		adjlist[i].firstArc = NULL;
	}
	int b, e;
	for (int i = 0; i < arcNum; i++)
	{
		in >> b >> e;
		ArcNode *s = new ArcNode;
		s->adjvex = e;
		s->nextArc = adjlist[b].firstArc;        //头插法，插入的节点顺序和文件中的结点是反的
		adjlist[b].firstArc = s;
	}
	in.close();
	memset(visited, 0, N * sizeof(bool));
}
template <class T, int N>
ALGraph<T, N>::~ALGraph()
{
	for (int i = 0; i < vNum; i++) //一个结点一个结点的析构
	{
		ArcNode *p = adjlist[i].firstArc;
		while (p != NULL)
		{
			ArcNode *pnext = p->nextArc;
			delete p;
			p = pnext;
		}
	}
}
template <class T, int N>
void ALGraph<T, N>::DFS_ALL(int v)           //和MGraph一样
{
	memset(visited, 0, N * sizeof(bool));
	DFS(v);
	for (int i = 0; i < vNum; i++)
		if (visited[i] == 0)
			DFS(i);
}
//template <class T, int N>
//void ALGraph<T, N>::DFS(int v) //非递归deep first search 访问一个连通分量O(n*n)
//{
//	int stack[100];
//	int top = -1;
//	int i;
//	cout << adjlist[v].vertex;
//	visited[v] = 1;//访问标记
//	stack[++top] = v;

//	while (top != -1)
//	{
//		ArcNode *p = adjlist[v].firstArc;
//		while (p != NULL)
//		{
//			if (visited[p->adjvex] == 0)//递归模式
//			{
//				v = p->adjvex; cout << adjlist[v].vertex; 	visited[v] = 1;	stack[++top] = v;
//				break;
//			}
//			p = p->nextArc;
//		}
//		if (p==NULL) //找不到未访问的邻接点
//		{
//			top--;
//			v = stack[top];
//		}
//	}
//}
template <class T, int N>
void ALGraph<T, N>::DFS(int v) //deep first search 访问一个连通分量O(n*n)
{
	/*①从某顶点v出发并访问
	②访问v的第一个未访问的邻接点w，v-->w
		……访问w的第一个未访问的邻接点u，
	③若当前顶点的所有邻接点都被访问过，则回溯，从上一级顶点的下一个未访问过的顶点开始深度优先遍历
		直到所有和v路径相通的顶点都被访问到；*/
	cout << adjlist[v].vertex;
	visited[v] = 1;//访问标记
	ArcNode *p = adjlist[v].firstArc;
	while ( p!= NULL )
	{
		if (visited[p->adjvex] == 0)//递归模式
			DFS(p->adjvex);
		p = p->nextArc;
	}
	return;
}
template <class T, int N>
void ALGraph<T, N> :: BFS_ALL(int v)
{
	memset(visited, 0, N * sizeof(bool));
	BFS(v);
	for (int i = 0; i < vNum; i++)
		if (visited[i] == 0)
			BFS(i);
}
template <class T, int N>
void ALGraph<T, N>::BFS(int v) //时间复杂度O(n*n)
{
	int queue[100];
	int f, r;
	f = r = -1;
	queue[++r] = v;
	while (f!=r)
	{
		//队头元素出队
		v = queue[++f];
		cout << adjlist[v].vertex;
		visited[v] = 1;
		//队头元素的所有未访问过的邻接点入队
		ArcNode *p = adjlist[v].firstArc;
		while (p != NULL)
		{
			if (visited[p->adjvex] == 0) //未访问过的邻接点入队
				queue[++r] = p->adjvex;
			p = p->nextArc;
		}
	}
}
void main()
{
	ALGraph<string, 10> g("graphinfo.txt");
	cout << "深度优先遍历：";
	g.DFS_ALL(2);
	cout << "\n广度优先遍历：";
	g.BFS_ALL(0);

}