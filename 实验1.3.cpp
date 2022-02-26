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
template <class T> class SeqLink
{
private:
	Node<T>* first;
public:
	SeqLink(T a[], int n);
	SeqLink(char *filename); //读取通信录
	void Insert(T e); 
	void print();
	void save(char *filename);//保存通信录
	~SeqLink();
};

template <class T>
SeqLink<T>::SeqLink(T a[], int n)
{
	
}
template <class T>
void SeqLink<T>::Insert(T e)//插入：要求建立的链表按照关键 字从小到大有序 
{


}
template <class T>
void SeqLink<T>::save(char *filename)
{
	
}

template <class T>
SeqLink<T>::SeqLink(char *filename)
{
	
}
template <class T>
void SeqLink<T>::print()
{
	Node<T>* p = first->next;
	while (p != NULL)
	{
		cout << p->data <<endl;
		p = p -> next;
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
	char phone[15];
	int group;
};

ostream& operator <<(ostream& out, ADDRESSBOOK& addr)
{
	out << addr.id << '\t' << addr.name << '\t' << addr.phone << '\t' << addr.group ;
	return out;
}
bool operator < (ADDRESSBOOK& addr1, ADDRESSBOOK& addr2)
{
	if (strcmp(addr1.phone, addr2.phone) < 0)
		return true;
	return false;
}

//文件输出流重载


//文件输入流重载


void main()
{

	ADDRESSBOOK addr[2] = { {1,"xyj","123",0},{2,"abc","2345",1} };

	SeqLink<ADDRESSBOOK> list(addr, 2);
	//SeqLink<ADDRESSBOOK> list("myaddr.txt");
	list.print();
	list.save("myaddr.txt");
}