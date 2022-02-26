#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

int const MAX = 999999;

struct node //����ڵ�
{
	int col, w; //ĳԪ�ض�Ӧ����������ӦȨֵ
	node(int a, int b) { col = a; w = b; } //���캯��
	bool operator < (const node& a) const //Ԥ����,std::<bitset>����û������,�Զ�����ǰ������ operator < ����
	{
		if (w == a.w)			 //�����ڵ�Ȩֵ��ͬ�����п�ǰ����
			return col < a.col;
		else					 //Ȩֵ��ͬ���ȽϺ�ȨֵС����ջ��
			return w > a.w;
	}
};

template <class T, int N>
class MGraph
{
public:
	MGraph(const char* filename);  //���캯��
	void CreateTree(int k); //prim�㷨
	int mininum(int lowcost[]);

	void ShortPath(int v); //Dijkstral�㷨
	void ShortPath2(int v); //�Ľ�Dijkstral�㷨
	int FindMin(int Disk[], bool S[], int n);
	void Print(int Disk[], int Path[], int n); //��ӡ·��

private:
	T vertex[N];
	int arc[N][N];
	int vNum, arcNum; //������������
	vector<node> eg[N]; //node�ڵ㹹�ɵ�������
};

template <class T, int N>
MGraph<T, N>::MGraph(const char* filename)  //���캯��
{
	ifstream in(filename);
	if (in.fail())
		throw "ͼ�ļ���ʧ�ܣ�";
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
		arc[b][e] = w; //д���ڽӾ���
		eg[b].push_back(node(e, w)); //д��vector�ڽڵ㣬���������д������

		arc[e][b] = w; //����ͼ�Գ�
		eg[e].push_back(node(b, w));
	}
	in.close();
}

template <class T, int N>
void MGraph<T, N>::CreateTree(int k)  //Prim�㷨
{
	int adjvex[N] = { 0 };   //U�����еĵ�
	int lowcost[N] = { 0 };  //U-->V-U�����еı�
	for (int i = 0; i < vNum; i++) //��������洢���ΪVk�ı�
	{
		adjvex[i] = k;
		if (arc[k][i] != 0)
			lowcost[i] = arc[k][i];
		else
			lowcost[i] = MAX;
	}

	lowcost[k] = 0;         //��ʼ���㼯 U = { Vk }

	for (int i = 1; i < vNum; i++)
	{
		k = mininum(lowcost);  //����һ������
		cout << vertex[adjvex[k]] << "-->" << vertex[k] << "\t" << arc[adjvex[k]][k] << endl;
		lowcost[k] = 0;   //U = U + {Vk}

		for (int j = 0; j < vNum; j++)  //���ø�������
		{
			if (lowcost[j] != 0 && arc[k][j] != 0 && arc[k][j] < lowcost[j]) //ˢ������Ϊ�±ߴ����Ҹ���
			{
				lowcost[j] = arc[k][j];
				adjvex[j] = k;
			}
		}
	}
}

template <class T, int N>
int MGraph<T, N> ::mininum(int lowcost[]) //Prim�㷨���ҳ���С����������һ������
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
	return k; //������Сֵ��Ӧ������
}

template <class T, int N>
void MGraph<T, N> ::ShortPath(int v)  //Dijkstra���·���㷨 ʱ�临�Ӷ�o(n^2)
{
	bool S[N];    //��¼����i�Ƿ����ҵ����·��
	int Disk[N];  //��¼Դ�㵽����i�����·���ĳ���
	int Path[N];  //��¼Դ�㵽�����·��
	for (int i = 0; i < vNum; i++)              //��ʼ����������
	{
		S[i] = false;
		if (arc[v][i] == 0)
			Disk[i] = MAX;
		else
			Disk[i] = arc[v][i];

		if (Disk[i] != MAX)
			Path[i] = v;
		else
			Path[i] = -1;        //��ǰ��
	}
	S[v] = true;
	Disk[v] = 0;               //��ʼ��V0�����S 

	for (int i = 0; i < vNum - 1; i++)
	{     // Ѱ����V0����Ķ���
		if ((v = FindMin(Disk, S, vNum)) == -1)
			return;
		S[v] = true;   //����S
		for (int j = 0; j < vNum; j++) //���¸������� 	
			if (!S[j] && arc[v][j] != 0 && (Disk[j] > arc[v][j] + Disk[v])) //��������Ϊ�µ㵽Ŀ�����С�ڵ�ǰĿ�����
			{
				Disk[j] = arc[v][j] + Disk[v];
				Path[j] = v;
			}
	}
	Print(Disk, Path, vNum);
}

template <class T, int N>
int MGraph<T, N> ::FindMin(int Disk[], bool S[], int n)  //�ҳ�DISK�о�����̵�һ��·��
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
void MGraph<T, N> ::Print(int Disk[], int Path[], int n) //���·��
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
void MGraph<T, N>::ShortPath2(int v) //����Dijkstra���Ż��㷨��ʱ�临�ӶȽ���Ϊo(n*logn)
{
	int Disk[N];
	for (int i = 0; i <= vNum; i++)
		Disk[i] = MAX;

	Disk[v] = 0;

	priority_queue<node> q; //�����ȶ����Ż����Զ�����
	q.push(node(v, Disk[v])); //������
	while (!q.empty()) //o(n*logn)
	{
		node front = q.top(); //���ʶ�ͷ��һ������С��
		q.pop();
		for (int i = 0; i < eg[front.col].size(); i++) //���¸�������
		{
			node t = eg[front.col][i]; //��ͷ���ڽ�Ԫ��
			if (Disk[t.col] > front.w + t.w) //ԭ����D�㷨��ͬ
			{
				Disk[t.col] = front.w + t.w;
				q.push(node(t.col, Disk[t.col])); //o(logn)���¶��У�ԭ��Ϊ����Ѵ洢
			}
		}
	}
	//ֱ�Ӵ�ӡ
	for (int i = 0; i < vNum; i++)
		cout << vertex[i] << ":" << Disk[i] << endl;
}

void main()
{
	MGraph<string, 10> g("MSTree.txt");
	cout << "\nPrim��С��������\n";
	g.CreateTree(1);
	cout << "\nDijkstra���·����\n";
	g.ShortPath(0);
	cout << "\n�Ľ��㷨���·����(·��ͬ��)\n";
	g.ShortPath2(0);
}
