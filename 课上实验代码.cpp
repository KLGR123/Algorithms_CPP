#include <iostream>
#include <fstream>
using namespace std;

//插入：要求建立的链表按照关键 字从小到大有序
template <class T>
struct Node
{
	T data;
	Node<T> * next;
};
template <class T>
class SeqLink
{
private:
	Node<T>* first;
public:
	SeqLink(char *filename);  //读文件
	SeqLink(T a[], int n);
	void Insert(T e);
	void print();
	void save(char *filename); //写文件
	~SeqLink();
};
template <class T>
SeqLink<T>::SeqLink(char *filename) //读文件===文件输入流
{
	ifstream fin(filename);
	if (fin.fail())
		throw "文件打开失败！";

	first = new Node<T>;
	first->next = NULL;
	T x;
	while (fin>>x)  //cin>>x
	{
		Insert(x);
	}
	fin.close();
}
template <class T>
void SeqLink<T>::save(char *filename)//写文件==文件输出流
{
	ofstream fout(filename);
	if (fout.fail())
		throw "文件打开失败！";
	
	Node<T>* p = first->next;
	while (p != NULL)
	{
		fout << p->data << endl;
		p = p->next;
	}
	fout.close();
}

template <class T>
SeqLink<T>::SeqLink(T a[], int n)
{
	first = new Node<T>;
	first->next = NULL;

	for (int i = 0; i < n; i++)
		Insert(a[i]);
}
template <class T>
void SeqLink<T>::Insert(T e)//插入：要求建立的链表按照关键 字从小到大有序 
{
	//假设已有链表有序，插入一个新结点，使新链表有序
	//idea：从头到尾遍历，找到合适的位置，插入新节点。
	//合适的位置：if （结点的值>当前要插入的值）那么要插入到该结点的前面。 插入：插入位置之前的结点的指针
	Node<T> *p  =first;
	while (p->next!=NULL) //找出插入位置的前一个结点的指针
	{
		if (p->next->data > e)
			break;
		else
			p = p->next;
	}
	Node<T> *s = new Node<T>;
	s->data = e;
	s->next = p->next;
	p->next = s;
}

template <class T>
void SeqLink<T>::print()
{
	Node<T>* p = first->next;
	while (p != NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}
}

template <class T>
SeqLink<T>::~SeqLink()
{
	while (first != NULL)
	{
		Node<T>*p = first;
		first = first->next;
		delete p;
	}
}

struct ADDRESSBOOK
{
	int id;
	char name[10];
	char phonenum[15];
	int group;
};

bool  operator > (ADDRESSBOOK& addr1, ADDRESSBOOK& addr2)
{
	if (strcmp(addr1.phonenum, addr2.phonenum) > 0)
		return true;
	return false;
}

ostream& operator<<(ostream&out, ADDRESSBOOK& addr)
{
	out << addr.id << "\t" << addr.name << "\t" << addr.phonenum << "\t" << addr.group;
	return out;
}
//文件输出流
ofstream& operator<<(ofstream&out, ADDRESSBOOK& addr)
{
	out << addr.id << "\t" << addr.name << "\t" << addr.phonenum << "\t" << addr.group;
	return out;
}

//文件输入流
ifstream& operator >> (ifstream& in, ADDRESSBOOK& addr)
{
	in >> addr.id >> addr.name >> addr.phonenum >> addr.group;
	return in;
}

void main()
{
	//int a[] = { 9,3,5,2,1,6,7,8,0,4 };
	ADDRESSBOOK addr[2] = { {1,"abc","234",1},{2,"bcd","123",0} };

	//SeqLink<ADDRESSBOOK> list(addr, 2);
	SeqLink<ADDRESSBOOK> list("16-18test.txt");
	list.print();
	//list.save("16-18test.txt");
}