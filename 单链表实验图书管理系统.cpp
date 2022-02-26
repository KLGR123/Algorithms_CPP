#include <iosfwd>
#include <iostream>
using namespace std;

//今天课上的第一项内容， 就当是复习上节课讲的单链表的实现。 本次课讲单链表实现图书管理系统。
//首先，补充完整以下两个函数： length()和print();
//然后，改进Loacte()函数匹配出一个结果，若是多个关键字相同的结果，如何处理？
//最后，改进==运算符重载， 精确匹配 改进成模糊匹配

//定义结点的结构
template <class T>
struct Node
{
	T data;
	Node<T>  *next;
};
template <class T> class LinkList
{
public:
	LinkList();
	LinkList(T a[], int n);
	T 		Get(int);                      //查找
	void 	Insert(T , int);               //插入
	T		Remove(int);                   //删除
	int     Locate(T x,int start=0);      //改进定位函数，能够定位多个关键字相同的元素
	int 	Length();                      //自行完成
	void	print();                       //自行完成
		
	~LinkList();
private:
	Node<T> *first;
	int length;
};
template <class T>
LinkList<T>::~LinkList()
{
	while (first != NULL)
	{
		Node<T> *p = first;
		first = first->next;
		delete p;
	}
}
template <class T>
LinkList<T>::LinkList()
{
	first = new Node<T>;
	first->next = NULL;
	length = 0;
}
template <class T>
LinkList<T>::LinkList(T a[], int n)
{
	//first = new Node<T>;
	//first->next = NULL;

	//for (int i = 0; i < n; i++)
	//{
	//	Node<T> *s = new Node<T>;
	//	s->data = a[i];
	//	s->next = first->next;   //头插法
	//	first->next = s;
	//}
	first = new Node<T>;
	first->next = NULL;
	Node<T> *r = first;

	for (int i = 0; i < n; i++)
	{
		Node<T> *s = new Node<T>;
		s->data = a[i];
		s->next = NULL;

		r->next = s;  //尾插法
		r = s;
	}
	length = n;
}
template <class T>
int LinkList<T>::Locate(T x,int start) //找到返回结点位置
{
	//初始化
	Node<T> *p = first->next;
	int j = 1;
	while (p != NULL)
	{
		if ((j>start)&&(p->data == x)) return j;
		p = p->next;
		j++;
	}
	return 0;
}

template <class T>
T LinkList<T>::Get(int i)
{     //初始化
	Node<T> *p = first->next;
	int j = 1;
	while (p != NULL && j<i)
	{
		p = p->next; //指针下移
		j++;
	}
	if (p == NULL) throw "查找位置不合法\n";
	return p->data;
}
template <class T>
void LinkList<T>::Insert(T x, int i)
{
	//找到编号i-1的结点
	Node<T> *p = first;
	int j = 0;
	while ((p != NULL) && (j != i - 1))
	{
		p = p->next;
		j++;
	}
	if (p == NULL)  throw "插入位置非法";

	Node<T>* s = new Node<T>;
	s->data = x;
	s->next = p->next;    //插入
	p->next = s;
	length++;
}
template <class T>
T LinkList<T>::Remove(int i)
{
	//找到编号i-1的结点
	Node<T> *p = first;
	int j = 0;
	while ((p != NULL) && (j != i - 1))
	{
		p = p->next;
		j++;
	}
	if (p == NULL)  throw "删除位置非法";

	Node<T> *s = p->next;
	p->next = s->next; //p->next = p->next->next; 
	T x = s->data;
	delete s;
	length--;
	return x;
}
template <class T>
int LinkList<T>::Length()  //计算链表的长度
{
	/*Node<T> *p = first;
	int j = 0;
	while (p->next!=NULL)
	{
		p = p->next;
		j++;
	}
	return j;*/
	return length;
}

template <class T>
void LinkList<T>::print()
{
	Node<T> *p = first->next;
	while (p!=NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}
}


//实现图书管理系统 
struct BOOK
{
	char name[20];
	int ISBN;
	char author[100];
	float price;
};
//重载<<运算符   函数重载运行原理一样，<<后面的参数类型
ostream& operator << (ostream& out, BOOK& s) //<<运算符重载
{
	out << s.name << "\t" << s.ISBN << "\t" << s.author << "\t" << s.price;
	return out;

}
//重载==运算符：精确查找 和 模糊查找
bool operator  ==(BOOK& s1, BOOK& s2)
{
	//if (strcmp(s1.name, s2.name) == 0)  //精确查找
	if (strstr(s1.name, s2.name) != NULL)  //模糊查找
			return true;
	return false;
}

void main()
{
	
	BOOK b[4] = { { "数据结构与算法",12036,"徐雅静",45 },
				  { "Python编程",11035,"abc",59 },
				  { "大学英语",13035,"bcd",43 },
				  { "数据结构与STL",12038,"肖波",39 } };

	BOOK book = { "数据结构",0,"?",0 };//模糊查找，关键字书名

	LinkList<BOOK> ls(b, 4);
	try
	{
		cout << ls.Length() << endl;
		ls.print();
		cout << "******************************" << endl;
		
		int pos =ls.Locate(book);
		while (pos > 0)
		{
			cout << ls.Get(pos) << endl;
			pos =ls.Locate(book,pos);
		}

	}
	catch (const char* e)
	{
		cout << e << endl;
		return;
	}


}