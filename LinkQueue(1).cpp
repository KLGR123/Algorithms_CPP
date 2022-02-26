#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T> * next;
};

template <class T> class LinkQueue
{
public:
	LinkQueue();
	int 	Empty();
	T 	GetQueue();               //获取队头元素
	void 	EnQueue(T);                    //入队
	T 	DeQueue();                        //出队
	~LinkQueue();
private:
	Node<T>  *front, *rear;
};

template <class T>
LinkQueue<T>::LinkQueue()
{
	front = new Node<T>;
	front->next = NULL;
	rear = front;
}

template <class T>
void  LinkQueue<T>::EnQueue(T e)//入队
{
	Node<T> *s = new Node<T>;
	s->data = e;
	rear->next = s;
	rear = s;

}
template <class T>
T 	LinkQueue<T>::DeQueue() //出队
{
	if (front == rear) 
		throw "队列空";
	Node<T> *p = front->next;
	T x = p->data;
	front->next = p->next;
	delete p;

	if (front->next == NULL) rear = front; //删除之后是空链表
	return x;
	
}
template <class T>
int	LinkQueue<T>::Empty()
{
	if (front == rear)
		return true;
	return false;
}

template <class T>
T	LinkQueue<T> ::GetQueue()              //获取队头元素
{
	if (front == rear)
		throw "队列空";
	return top->data;
}

template <class T>
LinkQueue<T> :: ~LinkQueue()
{
	while (f != r)
		DeQueue();

}