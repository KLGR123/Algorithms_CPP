#include <iostream>
#include <fstream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* lch;
	Node<T>* rch;
};
template <class T> class BiTree
{
protected:
	Node<T>* root;
	void Create(Node<T>*& R, T data[], int i, int n);
	void Release(Node<T>* R);
public:
	BiTree() : root(NULL) {} //注意此处语法
	BiTree(T data[], int n);
	void PreOrder(Node<T>* R); //前序
	void InOrder(Node<T>* R);   //中序
	void PostOrder(Node<T>* R); //后序
	void LevelOrder(Node<T>* R);  //层序
	~BiTree();
	Node<T>* GetRoot() { return root; }
	int GetTotalNode(Node<T>* R);
};
template <class T>
BiTree<T>::BiTree(T data[], int n)
{
	Create(root, data, 1, n);
}
template <class T>
BiTree<T>::~BiTree()
{
	Release(root);
}
template <class T>
void BiTree<T>::Release(Node<T>* R) //销毁二叉树
{
	if (R != NULL)
	{
		Release(R->lch); //析构左子树
		Release(R->rch);  //析构右子树
		delete R;        //析构根
	}
}

template <class T>
void BiTree<T>::Create(Node<T>*& R, T data[], int i, int n) //创建二叉树
{ //R当前要建立的根节点指针，i当前根节点编号  n表示最后一个叶子结点的编号
	//R的类型：指针的引用
	if ((i <= n) && (data[i - 1] != '0')) //执行条件  1.小于等于n  2.节点存在
	{
		R = new Node<T>;					//1、建立根结点
		R->data = data[i - 1];
		R->lch = NULL;  //注意声明好
		R->rch = NULL;
		//注意前后顺序
		Create(R->lch, data, 2 * i, n);		//2、建立左子树
		Create(R->rch, data, 2 * i + 1, n);//3、建立右子树
	}
}

template <class T>
void BiTree<T>::PreOrder(Node<T>* R) //前序O(n)
{
	if (R != NULL) //终止条件
	{
		cout << R->data; //访问根节点
		//if (R->lch != NULL)   //访问左支
		PreOrder(R->lch);
		//if (R->rch != NULL)  //访问右支
		PreOrder(R->rch);
	}
}
template <class T>
void BiTree<T>::InOrder(Node<T>* R) //中序O(n)
{
	if (R != NULL)
	{
		InOrder(R->lch);
		cout << R->data;
		InOrder(R->rch);
	}
}
template <class T>
void BiTree<T>::PostOrder(Node<T>* R) //后序O(n)
{
	if (R != NULL)
	{
		PostOrder(R->lch);
		PostOrder(R->rch);
		cout << R->data;
	}
}
template <class T>
void BiTree<T>::LevelOrder(Node<T>* R) //层序O(n) //非递归
{   //队列的初始化 还有栈的初始化都需要熟悉
	Node<T>* queue[128]; //循环队列
	int f, r;
	f = 0; //队空状态

	//根节点入队；启动层序遍历
	r = 1;
	queue[r] = R;
	while (f != r)//队列不空 // 循环 <---> 递归
	{
		//f总是指向第一个元素前面
		f = (f + 1) % 128;//队头元素出队访问
		R = queue[f];
		cout << R->data;
		//队头的左右孩子入队
		if (R->lch != NULL) { r = (r + 1) % 128;	queue[r] = R->lch; }
		if (R->rch != NULL) { r = (r + 1) % 128;	queue[r] = R->rch; }
	}
}
template <class T>
int BiTree<T>::GetTotalNode(Node<T>* R)
{
	if (R == NULL)
		return 0;
	else
	{
		int n = GetTotalNode(R->lch); //非常妙的递归
		int m = GetTotalNode(R->rch);
		return m + n + 1;
	}
}
void main()
{
	char data[20] = "ABCDEG000F00H"; //0表示没有节点
	BiTree<char> tree(data, 13);
	cout << "前序：";
	tree.PreOrder(tree.GetRoot());
	cout << "\n中序：";
	tree.InOrder(tree.GetRoot());
	cout << "\n后序：";
	tree.PostOrder(tree.GetRoot());
	cout << "\n层序：";
	tree.LevelOrder(tree.GetRoot());
	cout << "\n结点总数：" << tree.GetTotalNode(tree.GetRoot()) << endl;
	tree.~BiTree();
}
