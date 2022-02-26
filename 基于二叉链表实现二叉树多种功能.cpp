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
	bool isFull; //�ж��Ƿ�Ϊ��������
	void Create(Node<T>*& R, T data[], int i, int n); //���������� �ݹ�
	void Release(Node<T>* R); //���ٶ�����
	Node<T>* GetPoint(Node<T>* R, T data); //�����������ҵ�����ָ�����ݵĽ���ַ RΪ��ʼ��
public:
	BiTree() : root(NULL) {} //�޲ι���
	BiTree(const char* filename); //���� ���ļ�д�������
	~BiTree(); //����
	void PreOrder(Node<T>* R); //�ݹ�ǰ��
	void InOrder(Node<T>* R);   //�ݹ�����
	void PostOrder(Node<T>* R); //�ݹ����
	void LevelOrder(Node<T>* R);  //���� queue
	Node<T>* GetRoot() { return root; } //��ȡ����ַ
	int GetTotalNode(Node<T>* R); //��ȡ����ܸ���
	int GetDepth(Node<T>* R); //����������
	void ShowPath(T data);//��ָ����㵽����·��
	void ShowPath1(Node<T>* R);//����Ӹ��ڵ㵽��֪Ҷ�ӽ��ָ���·��
	bool IsChild(T data1, T data2); //�ж�ָ���������data1�Ƿ�Ϊdata2��������
	bool IsChild(Node<T>* M, Node<T>* N);//�ж�ָ�����M�Ƿ�Ϊָ�����N�������㣨��֪��ַ������
	void PreOrder1(Node<T>* R);//�ǵݹ�ʵ��ǰ�����������
	void InOrder1(Node<T>* R);//�ǵݹ�ʵ���������������
	bool IsFull() { return isFull; } //�ж϶������Ƿ�Ϊ��������
	int Floor(T data);	//��֪������� ���ؽ�����ڲ�
	void TreePrint(Node<T>* parent, Node<T>* root, string& prefix); //�����ӡ��
};

template <class T>
BiTree<T>::BiTree(const char* filename)
{
	ifstream in(filename);
	if (in.fail())
		throw "�������ļ���ʧ�ܣ�";
	int n;   
	in >> n;  
	T data[256] = {0};
	isFull = true; //����������־
	for (int i = 0; i < n; i++) //��������
	{
		in >> data[i];
		if (data[i] == 0) //����������
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
void BiTree<T>::Release(Node<T>* R)  //ʱ�临�Ӷ�o(n)
{
	if (R != NULL)
	{
		Release(R->lch); //����������
		Release(R->rch);  //����������
		delete R;        //������
	}
}
template <class T>
void BiTree<T>::Create(Node<T>*& R, T data[], int i, int n) //ʱ�临�Ӷ�o(n)
{   //R�ǵ�ǰҪ�����ĸ��ڵ�ָ�� i��ǰ���ڵ���
	//R�����ͣ�ָ������
	if ((i <= n) && (data[i - 1] != 0)) //ִ������ С�ڵ���n �ҷǿ�
	{
		R = new Node<T>;					//���������Ӹ������
		R->data = data[i - 1];				
		R->lch = NULL; 
		R->rch = NULL;
		Create(R->lch, data, 2 * i, n);		//����������
		Create(R->rch, data, 2 * i + 1, n); //����������
	}
}
template <class T>
void BiTree<T>::PreOrder(Node<T>* R) //ʱ�临�Ӷ�O(n)
{
	if (R != NULL) 
	{
		cout << R->data<<" "; //���ʸ��ڵ�
		PreOrder(R->lch); //������֧
		PreOrder(R->rch);//������֧
	}
}
template <class T>
void BiTree<T>::InOrder(Node<T>* R) //����O(n)
{
	if (R != NULL)
	{
		InOrder(R->lch);
		cout << R->data<<" ";
		InOrder(R->rch);
	}
}
template <class T>
void BiTree<T>::PostOrder(Node<T>* R) //����O(n)
{
	if (R != NULL)
	{
		PostOrder(R->lch);
		PostOrder(R->rch);
		cout << R->data<<" ";
	}
}
template <class T>
void BiTree<T>::LevelOrder(Node<T>* R) //����O(n) �ǵݹ�
{  
	Node<T>* queue[128]; //ѭ�����г�ʼ��
	int f, r;
	f = 0; 	//�ӿ�״̬
	r = 1;
	queue[r] = R; //ͷ�ڵ����
	while (f != r)
	{
		f = (f + 1) % 128;//��ͷԪ�س��ӷ���
		R = queue[f];
		cout << R->data<<" ";
		//��ͷ�����Һ������
		if (R->lch != NULL) { r = (r + 1) % 128;	queue[r] = R->lch; }
		if (R->rch != NULL) { r = (r + 1) % 128;	queue[r] = R->rch; }
	}

}
template <class T>
int BiTree<T>::GetTotalNode(Node<T>* R) //ʱ�临�Ӷ�o(n)
{
	if (R == NULL)
		return 0;
	else
	{
		int n = GetTotalNode(R->lch);
		int m = GetTotalNode(R->rch);
		return m + n + 1; //������ + �Һ����� + 1
	}
}
template <class T>
int BiTree<T>::GetDepth(Node<T>* R) //ʱ�临�Ӷ�o(n)
{
	if (R == NULL)
		return 0;
	else
	{
		int m = 1 + GetDepth(R->lch);
		int n = 1 + GetDepth(R->rch);
		return m > n ? m : n; //ȡ���һ�� �ݹ�
	}
}
template <class T>
void BiTree<T>::ShowPath(T data) //ʱ�临�Ӷ�o(n^2)
{
	Node<T>* R = GetPoint(root, data);
	if (!IsChild(R, root))
		throw "���� ���ڶ�����";

	stack<T> stack; //����ջ
	Node<T>* p = root;
	stack.push(p->data);
	while (p->data != R->data)
	{
		if (IsChild(R, p->lch)) //�ж����ӻ��Һ���
		{
			stack.push(p->lch->data); //��ջ
			p = p->lch;
		}
		else
		{
			stack.push(p->rch->data);
			p = p->rch;
		}
	}
	while (!stack.empty()) //ջ�������
	{
		cout << stack.top();
		if(stack.top() != root->data)
			cout<< "->";
		stack.pop();
	}
}
template<class T>
void BiTree<T>::ShowPath1(Node<T>* R) //ʱ�临�Ӷ�o(n^2)
{
	if (!IsChild(R, root))
		throw "���� ���ڶ�����";
	Node<T>* p = root;
	cout << root->data;
	while (p->data != R->data)
	{
		if (IsChild(R, p->lch)) //�������
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
bool BiTree<T>::IsChild(Node<T>* M, Node<T>* N) //ʱ�临�Ӷ�o(n)
{
	if (M == NULL || N == NULL) //����ս��
		return false;

	if (M == N)
		return true;
	else
	{
		bool m = IsChild(M, N->lch);
		bool n = IsChild(M, N->rch);
		return m || n ? true : false; //��ĳһ֧������ ��
	}
}
template<class T>
bool BiTree<T>::IsChild(T data1, T data2)//ʱ�临�Ӷ�o(n)
{
	Node<T>* M = GetPoint(root, data1);
	Node<T>* N = GetPoint(root, data2);
	return IsChild(M, N); //�������غ���
}
template<class T>
Node<T>* BiTree<T>::GetPoint(Node<T>* R,T data) //ʱ�临�Ӷ�o(n)
{
	stack<Node<T>*> stack;
	while (!stack.empty() || R != NULL)//���� 
	{
		if (R != NULL)
		{
			if (R->data == data)//���ҵ�
				return R;
			stack.push(R);//��ջ
			R = R->lch;
		}
		else
		{
			R = stack.top();
			stack.pop(); 
			R = R->rch;//��ջ ����֧
		}
	}
}
template<class T>
void BiTree<T>::PreOrder1(Node<T>* R) //ʱ�临�Ӷ�o(n) �ǵݹ� stack
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
void BiTree<T>::InOrder1(Node<T>* R) //ʱ�临�Ӷ�o(n)
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
			cout << R->data<<" "; //����
			R = R->rch;
		}
	}
}
template<class T>
int BiTree<T>::Floor(T data) //ʱ�临�Ӷ� o(n^2)
{
	Node<T>* R = GetPoint(root, data);
	if (!IsChild(R, root))
		throw "���� ���ڶ�����";

	Node<T>* p = root;
	int i = 1;
	while (p->data != data)
	{
		if (IsChild(R, p->lch))
			p = p->lch;
		else
			p = p->rch;
		i++; //����һ��
	}
	return i;
}
template<class T>
void BiTree<T>::TreePrint(Node<T>* parent, Node<T>* root, string& prefix) //ʱ�临�Ӷ�o(n)
{
	prefix += "|"; //���ϼ����߶�����
	if (root) //�����������
	{
		cout << prefix << "--" << root->data << endl; //��ӡ
		if (root == parent || root == parent->rch) //��ת����֧
		{
			prefix.pop_back(); //ɾȥ�ַ���ĩβ���߶�
			prefix += " ";     //��Ϊ�ո�
		}
		TreePrint(root, root->lch, prefix + "  "); //�ݹ� 
		TreePrint(root, root->rch, prefix + "  ");
	}
	else //��Ҷ�ӽ��
	{
		if (parent->lch || parent->rch) //ֻҪ���ӽڵ㲻�� ��ӡ
			cout << prefix << "--" << "��" << endl;
	}
}

void main()
{
	try
	{
		BiTree<int> tree("tree.txt");
		cout << "ǰ��";
		tree.PreOrder(tree.GetRoot());
		cout << "\n�ǵݹ�ǰ��";
		tree.PreOrder1(tree.GetRoot());
		cout << "\n����";
		tree.InOrder(tree.GetRoot());
		cout << "\n�ǵݹ�����";
		tree.InOrder1(tree.GetRoot());
		cout << "\n����";
		tree.PostOrder(tree.GetRoot());
		cout << "\n����";
		tree.LevelOrder(tree.GetRoot());
		cout << endl;

		cout << "\n���������" << tree.GetTotalNode(tree.GetRoot());
		cout << "\n�����ȣ�" << tree.GetDepth(tree.GetRoot()) << endl;
		cout << "\n8�ǲ���2�������㣺" << tree.IsChild(8, 2);
		cout << "\n11�ǲ���5�������㣺" << tree.IsChild(11, 5);
		cout << "\n25�ǲ���3�������㣺" << tree.IsChild(25, 3) << endl;
		cout << "\n5�����ڵ�1��·����" << endl;
		tree.ShowPath(5);
		cout << "\n11�����ڵ�1��·����" << endl;
		tree.ShowPath(11);
		cout << endl;
		cout<< "\n���ڵ㵽5����Ӧ�ĵ�ַ��5����·����" << endl;
		tree.ShowPath1(tree.GetRoot()->lch->rch);
		cout << "\n���ڵ㵽11����Ӧ�ĵ�ַ��11����·����" << endl;
		tree.ShowPath1(tree.GetRoot()->rch->rch->lch);
		cout << endl;
		cout << "\n�Ƿ�Ϊ��������:" << tree.IsFull() << endl;
		cout << "\n6���ڲ�Ϊ��" << tree.Floor(6);
		cout << "\n9���ڲ�Ϊ��" << tree.Floor(9) << endl;
		cout << "��������ӡ��" << endl;

		string s;
		tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
		tree.~BiTree();
	}
	catch(char* e)
	{
		cout << e << endl;
	}
}
