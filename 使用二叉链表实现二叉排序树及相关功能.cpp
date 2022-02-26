#include <iostream>
using namespace std;

template<class T>class BiNode
{
public:
	T data;
	BiNode<T>* lch;
	BiNode<T>* rch;
	BiNode() :lch(NULL), rch(NULL), data(0) {};
};

template<class T>class BST
{
public:
	BST(T r[], int n); //���캯��
	~BST(); //��������
	void Release(BiNode<T>* R); //���ٺ���
	BiNode<T>* Search(BiNode<T>* R, T key); //���Һ��� �ؼ���key
	void InsertBST(BiNode<T>*& R, BiNode<T>* s); //����ڵ�
	void Delete(BiNode<T>*& R); //ɾ���ڵ�
	bool DeleteBST(BiNode<T>*& R, T key); //ɾ�������ؼ���key
	BiNode<T>* GetRoot() { return Root; } //���ظ��ڵ�
	void DeleteMax(BiNode<T>* R); //ɾ�����������Ľڵ�
	void DeleteMin(BiNode<T>* R); //ɾ����������С�Ľڵ�
	BiNode<T>* SearchFather(BiNode<T>* s, T target); //���Ҹ��ڵ�
	void TreePrint(BiNode<T>* parent, BiNode<T>* root, string& prefix);//��ӡ������
	
private:
	BiNode<T>* Root; //���ڵ�
};

template<class T>
BST<T>::BST(T r[], int n) //���캯��
{
	//���ÿո��ڵ� �����б�r
	//�����½ڵ� data ����ָ�� ��ֵ 
	//���ò��뺯��InsertBST
	Root = NULL;
	for (int i = 0; i < n; i++)
	{
		BiNode<T>* s = new BiNode<T>;
		s->data = r[i];
		s->lch = s->rch = NULL;
		InsertBST(Root, s);
	}
}

template<class T>
BST<T>::~BST() //��������
{
	Release(Root);
}

template<class T>
void BST<T>::Release(BiNode<T>* R)  //���ٺ���
{
	if (R != NULL)
	{
		Release(R->lch); //����������
		Release(R->rch); //����������
		delete R; //���ٸ�
	}
}

template<class T>
BiNode<T>* BST<T>::Search(BiNode<T>* R, T key) //���Һ��� �ؼ���key
{
	//�ݹ��㷨 ��ַR��¼��ǰ���ҵ�ַ Ϊ�շ��ؿ� ��Ϊ���ж�
	//�����Ӧ���ݵ���key�򷵻ص�ַ �����жϴ�С
	//С�ڽ��������� ������������� Search
	if (R == NULL) return NULL;
	if (key == R->data) return R;
	else if (key < R->data) return Search(R->lch, key);
	else return Search(R->rch, key);
}

template<class T>
void BST<T>::InsertBST(BiNode<T>*& R, BiNode<T>* s)//����ڵ�
{
	//Rָ��Ϊ���ڵ� sΪ��������½ڵ�
	//�ݹ� ���RΪ�� s����R��λ�� 
	//���� �жϴ�С��ϵ ���s��Ӧ����С��R��Ӧ���� �������֧InsertBST ��֮����
	if (R == NULL)
		R = s;
	else if (s->data > R->data)
		InsertBST(R->rch, s);
	else
		InsertBST(R->lch, s);
}

template<class T>
void BST<T>::Delete(BiNode<T>*& R) //ɾ���ڵ�
{
	//ɾ����֤����
	//�ȶ�ɾ��������� ��ɾ��Ҷ�ӽڵ� ɾ��ֻ�����ң������Ľڵ��һ��ڵ�
	//qΪ��ʱ��¼�ڵ� sΪ��ɾ���Ľڵ����֧�����ұߵĽڵ�
	BiNode<T>* q, * s;
	if (R->lch == NULL) //ע���ʱ������Ҷ�ӽڵ��ֻ���������Ľڵ�
	{
		q = R;
		R = R->rch;
		delete q;
	}
	else if (R->rch == NULL) //ֻ��������
	{
		q = R;
		R = R->lch;
		delete q;
	}
	else //һ�����
	{
		s = R->lch; q = R; //sΪ��ɾ���Ľڵ����֧�����ұߵĽڵ�
		while (s->rch != NULL)
		{
			q = s; //q��s��˫��
			s = s->rch; //s��������ֱ���ҵ���֧���Ҳ�ڵ�
		}
		R->data = s->data; //ʹ��ǰ����ֵ�滻��ǰ�ڵ���ֵ
		if (q != R) //��ɾ���Ľڵ�����ӵ��������ǿ� s��ʱΪq���Һ���
			q->rch = s->lch; //s�Ѿ�����ֵ����ɾ���ڵ� ���轫s�����������丸�ڵ�q����
		else //��ɾ���Ľڵ�����ӵ�������Ϊ�� s��ʱΪR������
			R->lch = s->lch;//R�����ӽ����滻Ϊs������ ��R�������ӽڵ�
		delete s;
	}
}

template<class T>
bool BST<T>::DeleteBST(BiNode<T>*& R, T key) //ɾ�������ؼ���key
{
	//R�Ƕ����������ĸ��ڵ� key�ǹؼ���
	//��δ�ҵ� ��R��Ϊ�� ����false
	//�ҵ��ؼ��ֺ� ����Deleteɾ���ڵ㲢����true
	//��key��R��Ӧdata����� �ݹ�
	//��keyС��data ������������������Ҳ�ɾ�� ��֮����������
	if (R == NULL) return false;
	else
	{
		if (key == R->data)
		{
			Delete(R);
			return true;
		}
		else if (key < R->data) return DeleteBST(R->lch, key);
		else return DeleteBST(R->rch, key);
	}
}

template<class T> 
void BST<T>::DeleteMax(BiNode<T>* R) //ɾ�����������Ľڵ�
{
	//�����������ҽڵ�һ�������ڵ�
	//ѭ������ �ҵ�maximum ɾ��
	//ȷ�������������
	if (R->rch == NULL)
		Root = Root->lch;
	if (R->rch != NULL && R->rch->rch == NULL)
	{
		Root->data = Root->rch->data;
		Root->rch = NULL;
	}
	while (R->rch->rch != NULL)
	{
		R = R->rch;
	}
	R->rch = NULL;
	delete R->rch;
}

template<class T>
void BST<T>::DeleteMin(BiNode<T>* R) //ɾ����������С�Ľڵ�
{
	if (R->lch == NULL)
		Root = Root->rch;
	if (R->lch != NULL && R->lch->lch == NULL)
	{
		Root->data = Root->lch->data;
		Root->lch = NULL;
	}
	while (R->lch->lch != NULL)
	{
		R = R->lch;
	}
	R->lch = NULL;
	delete R->lch;
}


template<class T>
BiNode<T>* BST<T>::SearchFather(BiNode<T>* s,T target) //���Ҹ��ڵ�
{
	//���sΪ�� ˵��û�ҵ� ���ؿ�
	//�ж���s�ĺ��ӽڵ���R �򷵻�s �ҵ�R���ڵ�
	//��û��R �Ƚ�data��С����Ӧ�ݹ�
	if (s == NULL) return NULL;

	if ((s->lch != NULL && s->lch->data == target)||(s->rch != NULL && s->rch->data == target))
		return s;
	if (target < s->data) 
		return SearchFather(s->lch, target);
	if (target > s->data)
		return SearchFather(s->rch, target);
}

template<class T>
void BST<T>::TreePrint(BiNode<T>* parent, BiNode<T>* root, string& prefix) //��ӡ������
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

int main()
{
	int list[12] = { 45, 12, 53, 3, 37, 100, 24, 39, 61, 113, 90, 78 };
	BST<int> tree(list, 12);
	cout<<"������������"<<endl;
	string s;
	tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
	s.clear();

	BiNode<int>* result = tree.Search(tree.GetRoot(), 37);
	cout << "��ѯ37�Ľ��Ϊ��" << result->data << endl;
	result = tree.Search(tree.GetRoot(), 90);
	cout << "��ѯ90�Ľ��Ϊ��" << result->data << endl;

	cout << endl;
	BiNode<int>* newNode= new BiNode<int>;
	newNode->data = 40;

	BiNode<int>* root = tree.GetRoot();

	cout << "�����½ڵ�40��Ч����" << endl;
	tree.InsertBST(root, newNode);
	tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
	s.clear();

	cout << "ɾȥ�ղ�����½ڵ㣺" << endl;
	tree.DeleteBST(root, 40);
	tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
	s.clear();

	cout << "ɾȥ��С�ڵ��Ч����" << endl;
	tree.DeleteMin(tree.GetRoot());
	tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
	s.clear();

	cout << "ɾȥ���ڵ��Ч����" << endl;
	tree.DeleteMax(tree.GetRoot());
	tree.TreePrint(tree.GetRoot(), tree.GetRoot(), s);
	s.clear();

	BiNode<int>* resul = NULL;
	resul = tree.SearchFather(tree.GetRoot(), 61); 
	cout << "�����ڵ�61�ĸ��׽ڵ��Ӧ���ݣ�" << resul->data << endl;

	tree.~BST();
	return 0;
}