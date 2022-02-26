#include <iostream>
#include <fstream>
#include <stack>
#include <queue>

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
	Node<T>* root; //
	bool isFull; //判断是否为满二叉树
	void Create(Node<T>*& R, T data[], int i, int n); //创建二叉树 递归
	void Release(Node<T>* R); //销毁二叉树
	Node<T>* GetPoint(Node<T>* R, T data); //搜索二叉树找到具有指定数据的结点地址 R为起始点
public:
	BiTree() : root(NULL) {} //无参构造
	BiTree(const char* filename); //构造 从文件写入二叉树
	~BiTree(); //析构
	void PreOrder(Node<T>* R); //递归前序
	void InOrder(Node<T>* R);   //递归中序
	void PostOrder(Node<T>* R); //递归后序
	void LevelOrder(Node<T>* R);  //层序 queue
	Node<T>* GetRoot() { return root; } //获取根地址
	int GetTotalNode(Node<T>* R); //获取结点总个数
	int GetDepth(Node<T>* R); //求二叉树深度
	void ShowPath(T data);//求指定结点到根的路径
	void ShowPath1(Node<T>* R);//输出从根节点到已知叶子结点指针的路径
	bool IsChild(T data1, T data2); //判断指定结点数据data1是否为data2的子孙结点
	bool IsChild(Node<T>* M, Node<T>* N);//判断指定结点M是否为指定结点N的子孙结点（已知地址）重载
	void PreOrder1(Node<T>* R);//非递归实现前序遍历二叉树
	void InOrder1(Node<T>* R);//非递归实现中序遍历二叉树
	bool IsFull() { return isFull; } //判断二叉树是否为满二叉树
	int Floor(T data);	//已知结点数据 返回结点所在层
	void TreePrint(Node<T>* parent, Node<T>* root, string& prefix); //纵向打印树
};

template <class T>
BiTree<T>::BiTree(const char* filename)
{
	ifstream in(filename);
	if (in.fail())
		throw "二叉树文件打开失败！";
	int n;   
	in >> n;  
	T data[256] = {0};
	isFull = true; //满二叉树标志
	for (int i = 0; i < n; i++) //导入数据
	{
		in >> data[i];
		if (data[i] == 0) //非满二叉树
			isFull = false;
	}
	Create(root, data, 1, n);
	in.close();
}
template <class T>
BiTree<T>::~BiTree()
{
	Release(root);
}
template <class T>
void BiTree<T>::Release(Node<T>* R)  //时间复杂度o(n)
{
	if (R != NULL)
	{
		Release(R->lch); //析构左子树
		Release(R->rch);  //析构右子树
		delete R;        //析构根
	}
}
template <class T>
void BiTree<T>::Create(Node<T>*& R, T data[], int i, int n) //时间复杂度o(n)
{   //R是当前要建立的根节点指针 i当前根节点编号
	//R的类型：指针引用
	if ((i <= n) && (data[i - 1] != 0)) //执行条件 小于等于n 且非空
	{
		R = new Node<T>;					//建立根（子根）结点
		R->data = data[i - 1];				
		R->lch = NULL; 
		R->rch = NULL;
		Create(R->lch, data, 2 * i, n);		//建立左子树
		Create(R->rch, data, 2 * i + 1, n); //建立右子树
	}
}
template <class T>
void BiTree<T>::PreOrder(Node<T>* R) //时间复杂度O(n)
{
	if (R != NULL) 
	{
		cout << R->data<<" "; //访问根节点
		PreOrder(R->lch); //访问左支
		PreOrder(R->rch);//访问右支
	}
}
template <class T>
void BiTree<T>::InOrder(Node<T>* R) //中序O(n)
{
	if (R != NULL)
	{
		InOrder(R->lch);
		cout << R->data<<" ";
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
		cout << R->data<<" ";
	}
}
template <class T>
void BiTree<T>::LevelOrder(Node<T>* R) //层序O(n) 非递归
{  
	Node<T>* queue[128]; //循环队列初始化
	int f, r;
	f = 0; 	//队空状态
	r = 1;
	queue[r] = R; //头节点入队
	while (f != r)
	{
		f = (f + 1) % 128;//队头元素出队访问
		R = queue[f];
		cout << R->data<<" ";
		//队头的左右孩子入队
		if (R->lch != NULL) { r = (r + 1) % 128;	queue[r] = R->lch; }
		if (R->rch != NULL) { r = (r + 1) % 128;	queue[r] = R->rch; }
	}

}
template <class T>
int BiTree<T>::GetTotalNode(Node<T>* R) //时间复杂度o(n)
{
	if (R == NULL)
		return 0;
	else
	{
		int n = GetTotalNode(R->lch);
		int m = GetTotalNode(R->rch);
		return m + n + 1; //左孩子数 + 右孩子数 + 1
	}
}
template <class T>
int BiTree<T>::GetDepth(Node<T>* R) //时间复杂度o(n)
{
	if (R == NULL)
		return 0;
	else
	{
		int m = 1 + GetDepth(R->lch);
		int n = 1 + GetDepth(R->rch);
		return m > n ? m : n; //取最长的一侧 递归
	}
}
template <class T>
void BiTree<T>::ShowPath(T data) //时间复杂度o(n^2)
{
	Node<T>* R = GetPoint(root, data);
	if (!IsChild(R, root))
		throw "错误 不在二叉树";

	stack<T> stack; //构造栈
	Node<T>* p = root;
	stack.push(p->data);
	while (p->data != R->data)
	{
		if (IsChild(R, p->lch)) //判断左孩子或右孩子
		{
			stack.push(p->lch->data); //入栈
			p = p->lch;
		}
		else
		{
			stack.push(p->rch->data);
			p = p->rch;
		}
	}
	while (!stack.empty()) //栈逆序输出
	{
		cout << stack.top();
		if(stack.top() != root->data)
			cout<< "->";
		stack.pop();
	}
}
template<class T>
void BiTree<T>::ShowPath1(Node<T>* R) //时间复杂度o(n^2)
{
	if (!IsChild(R, root))
		throw "错误 不在二叉树";
	Node<T>* p = root;
	cout << root->data;
	while (p->data != R->data)
	{
		if (IsChild(R, p->lch)) //正序输出
		{
			cout << "->" <<p->lch->data; 
			p = p->lch;
		}
		else
		{
			cout << "->" << p->rch->data;
			p = p->rch;
		}
	}
}
template<class T>
bool BiTree<T>::IsChild(Node<T>* M, Node<T>* N) //时间复杂度o(n)
{
	if (M == NULL || N == NULL) //传入空结点
		return false;

	if (M == N)
		return true;
	else
	{
		bool m = IsChild(M, N->lch);
		bool n = IsChild(M, N->rch);
		return m || n ? true : false; //在某一支即存在 或
	}
}
template<class T>
bool BiTree<T>::IsChild(T data1, T data2)//时间复杂度o(n)
{
	Node<T>* M = GetPoint(root, data1);
	Node<T>* N = GetPoint(root, data2);
	return IsChild(M, N); //调用重载函数
}
template<class T>
Node<T>* BiTree<T>::GetPoint(Node<T>* R,T data) //时间复杂度o(n)
{
	stack<Node<T>*> stack;
	while (!stack.empty() || R != NULL)//遍历 
	{
		if (R != NULL)
		{
			if (R->data == data)//如找到
				return R;
			stack.push(R);//入栈
			R = R->lch;
		}
		else
		{
			R = stack.top();
			stack.pop(); 
			R = R->rch;//出栈 换右支
		}
	}
}
template<class T>
void BiTree<T>::PreOrder1(Node<T>* R) //时间复杂度o(n) 非递归 stack
{
	stack<Node<T>*> stack;
	while (!stack.empty() || R != NULL)
	{
		if (R != NULL)
		{
			cout << R->data<<" ";
			stack.push(R);
			R = R->lch;
		}
		else
		{
			R = stack.top();
			stack.pop();
			R = R->rch;
		}
	}
}
template<class T>
void BiTree<T>::InOrder1(Node<T>* R) //时间复杂度o(n)
{
	stack<Node<T>*> stack;
	while (!stack.empty() || R != NULL)
	{
		if (R != NULL)
		{
			stack.push(R);
			R = R->lch;
		}
		else
		{
			R = stack.top();
			stack.pop();
			cout << R->data<<" "; //中序
			R = R->rch;
		}
	}
}
template<class T>
int BiTree<T>::Floor(T data) //时间复杂度 o(n^2)
{
	Node<T>* R = GetPoint(root, data);
	if (!IsChild(R, root))
		throw "错误 不在二叉树";

	Node<T>* p = root;
	int i = 1;
	while (p->data != data)
	{
		if (IsChild(R, p->lch))
			p = p->lch;
		else
			p = p->rch;
		i++; //下移一层
	}
	return i;
}
template<class T>
void BiTree<T>::TreePrint(Node<T>* parent, Node<T>* root, string& prefix) //时间复杂度o(n)
{
	prefix += "|"; //与上级树线段相连
	if (root) //有左或右子树
	{
		cout << prefix << "--" << root->data << endl; //打印
		if (root == parent || root == parent->rch) //当转向右支
		{
			prefix.pop_back(); //删去字符串末尾的线段
			prefix += " ";     //改为空格
		}
		TreePrint(root, root->lch, prefix + "  "); //递归 
		TreePrint(root, root->rch, prefix + "  ");
	}
	else //是叶子结点
	{
		if (parent->lch || parent->rch) //只要孩子节点不空 打印
			cout << prefix << "--" << "□" << endl;
	}
}

void main()
{
	try
	{
		BiTree<int> tree("tree.txt");
		cout << "前序：";
		tree.PreOrder(tree.GetRoot());
		cout << "\n非递归前序：";
		tree.PreOrder1(tree.GetRoot());
		cout << "\n中序：";
		tree.InOrder(tree.GetRoot());
		cout << "\n非递归中序：";
		tree.InOrder1(tree.GetRoot());
		cout << "\n后序：";
		tree.PostOrder(tree.GetRoot());
		cout << "\n层序：";
		tree.LevelOrder(tree.GetRoot());
		cout << endl;

		cout << "\n结点总数：" << tree.GetTotalNode(tree.GetRoot());
		cout << "\n最大深度：" << tree.GetDepth(tree.GetRoot()) << endl;
		cout << "\n8是不是2的子孙结点：" << tree.IsChild(8, 2);
		cout << "\n11是不是5的子孙结点：" << tree.IsChild(11, 5);
		cout << "\n25是不是3的子孙结点：" << tree.IsChild(25, 3) << endl;
		cout << "\n5到根节点1的路径：" << endl;
		tree.ShowPath(5);
		cout << "\n11到根节点1的路径：" << endl;
		tree.ShowPath(11);
		cout << endl;
		cout<< "\n根节点到5所对应的地址（5）的路径：" << endl;
		tree.ShowPath1(tree.GetRoot()->lch->rch);
		cout << "\n根节点到11所对应的地址（11）的路径：" << endl;
		tree.ShowPath1(tree.GetRoot()->rch->rch->lch);
		cout << endl;
		cout << "\n是否为满二叉树:" << tree.IsFull() << endl;
		cout << "\n6所在层为：" << tree.Floor(6);
		cout << "\n9所在层为：" << tree.Floor(9) << endl;
		cout << "二叉树打印：" << endl;

		string s;
		tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
		tree.~BiTree();
	}
	catch(char* e)
	{
		cout << e << endl;
	}
}
