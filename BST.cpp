#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T> class BiNode
{
public:
	T data;
	BiNode <T>  *lch;
	BiNode <T>  *rch;
	BiNode() :lch(NULL), rch(NULL) { };
};

template<class T> class BST
{
public:
	BiNode<T> * root;
public:
	BST() { root = NULL; }
	void CreateBST(T a[], int n);
	void InsertBST(BiNode<T> *&R, BiNode<T> *s); //插入
	BiNode<T> * SearchBST(BiNode<T> *R, T key);//查找

	bool  DeleteBST(BiNode<T> *&R, T key);  //删除
	void Delete(BiNode<T> *&R);

	void Inorder(BiNode<T> *R);
	void Release(BiNode<T> *R);
	~BST() { Release(root); }
};
template<class T>
void BST<T>::CreateBST(T a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		BiNode<T> *s = new  BiNode<T>;
		s->data = a[i];
		InsertBST(root, s);
	}
}
//template<class T>
//void BST<T>::InsertBST(BiNode<T> *&R, BiNode<T> *s) 
//{
//	if (R == NULL)
//		R = s;
//	else if (s->data <= R->data)
//		InsertBST(R->lch, s);
//	else
//		InsertBST(R->rch, s);
//}
//非递归插入
template<class T>
void BST<T>::InsertBST(BiNode<T> *&R, BiNode<T>* s)
{
	if (R == NULL)
		R = s;
	else
	{
		BiNode<T> **p = &R;
		while (*p!=NULL)
		{
			if (s->data <= (*p)->data)
				p = &(*p)->lch;
			else
				p = &(*p)->rch;
		}
		*p = s;
	}
}
//template<class T>
//BiNode<T> * BST<T>::SearchBST(BiNode<T> *R, T key)
//{
//	if (R == NULL)
//		return NULL;                //key不存在
//	else if (key == R->data)
//		return R;
//	else  if (key < R->data)
//		SearchBST(R->lch, key);
//	else
//		SearchBST(R->rch, key);
//
//}
template<class T>
BiNode<T> * BST<T>::SearchBST(BiNode<T> *R, T key) //非递归
{
	while (R!=NULL)
	{
		if (key == R->data)
			return R;
		else if (key < R->data)
			R = R->lch;
		else
			R = R->rch;
	}
	return NULL;
}
template <class T>
bool  BST<T>::DeleteBST(BiNode<T> *&R, T key)
{
	if (R == NULL) 	      return false;
	else
	{
		if (key == R->data)     Delete(R);
		else if (key<R->data)   DeleteBST(R->lch, key);
		else                    DeleteBST(R->rch, key);
		return true;
	}
}
template <class T> 
void  BST<T>::Delete(BiNode<T> *&R)
{
	BiNode<T> *q, *s;
	if (R->lch == NULL) 
	{ q = R; R = R->rch; delete q; }
	else if (R->rch == NULL) 
	{ q = R; R = R->lch; delete q; }
	else { //s是R的前驱， q是s的双亲
		q = R; 	
		s = R->lch;
		while (s->rch != NULL)
		{ q = s; s = s->rch; }
		R->data = s->data;
		if (q != R)  
			q->rch = s->lch;
		else       
			R->lch = s->lch;    //q=R表示s为R的左孩子
		delete s;
	}
}

template<class T>
void BST<T>::Inorder(BiNode<T> *R)
{
	if (R != NULL)
	{
		Inorder(R->lch);
		cout << R->data << "  ";
		Inorder(R->rch);
	}
}
template<class T>
void BST<T>::Release(BiNode<T> *R)
{
	if (R != NULL)
	{
		Release(R->lch);
		Release(R->rch);
		delete R;
	}
}
void main()
{
	int a[] = { 63, 90, 70, 55, 67, 42, 98 };
	BST<int> btree;
	cout << "创建BST(中序遍历)：";
	btree.CreateBST(a, 7);
	btree.Inorder(btree.root);
	cout << endl;

	cout << "查找BST:";
	BiNode<int> *p = btree.SearchBST(btree.root, 55);
	if (p != NULL)
		cout << p->data << endl;
	else
		cout << "没找到" << endl;

	cout << "删除BST的根(中序遍历)：";
	btree.DeleteBST(btree.root, 63);
	btree.Inorder(btree.root);
	cout << endl;
}
