#include <iostream>
#include <ctime>
using namespace std;

//双向列表结点
struct Node
{
	int data;
	Node* next;
	Node* prior;
};

//链表类
class LinkList
{
public:
	LinkList(int n); //构造函数 
	~LinkList(); //析构函数
	void show(); //打印数字
	int compare(LinkList& b); //用以比较两数字大小 返回1本值更大 返回2则LinkList b 更大
	void addBig(LinkList& b, LinkList& result); //两大数相加
	void minusBig(LinkList& b, LinkList& result);//两大数相减绝对值
private:
	Node* first;
	int length;
};

LinkList::LinkList(int n)
{
	first = new Node;
	first->next = NULL;
	first->prior = NULL;
	length = n;

	Node* p = first;
	for (int i = 0; i < length; i++)
	{
		Node* q = new Node;

		if (i == length - 1) //保证最后一位不是0
		{
			int num = rand() % 10;
			while (!num) { num = rand() % 10; }
			q->data = num;
		}
		//产生随机数并赋值
		else { q->data = rand() % 10; }
		//尾插法 最终得到以first为头结点的双向链表
		q->next = NULL;
		q->prior = p;
		p->next = q;
		p = q;
	}
}

LinkList::~LinkList()
{
	while (first != NULL)
	{
		Node* p = first;
		first = first->next;
		delete p;
	}
}

void LinkList::show()
{
	Node* p = first;
	while (p->next != NULL) { p = p->next; }
	//由于加减法之后， 链表末可能是0 故需要找到起始有效位 再打印
	if (p->data == 0)
	{
		while (p->data == 0)
		{
			p = p->prior;
		}
	}

	while (p != first)
	{
		cout << p->data;
		p = p->prior;
	}
	cout << '\n' << endl;
}

int LinkList::compare(LinkList& b)
{
	if (length > b.length) { return 1; }
	else if (length < b.length) { return 2; }
	else //两个数一样长
	{
		Node* p = first;
		Node* q = b.first;
		while (p->next != NULL)
		{
			p = p->next;
			q = q->next;
		}
		while (p->data == q->data)//如果相同位数字相同 回滚
		{
			p = p->prior;
			q = q->prior;
		}
		if (p->data > q->data) { return 1; }
		else { return 2; }
	}
}

//加法 传入的加数更大
void LinkList::addBig(LinkList& b, LinkList& result)
{
	Node* p = first;
	Node* q = b.first;
	Node* re = result.first;
	while (q != NULL)
	{
		if (p->data + q->data > 9)
		{
			if (p->next == NULL) //如果两个加数一样长
				re->next->data = 1;
			else
				p->next->data++;
			re->data = p->data - 10 + q->data;
		}
		else
		{
			if (p->next == NULL)
			{
				re->next->data = 0;
			}
			re->data = p->data + q->data;
		}
		p = p->next;
		q = q->next;
		re = re->next;
	}

	int mark = 0;
	while (p != NULL)//两个加数不一样长 继续加
	{
		if (p->data > 9)
		{
			if (p->next != NULL)
			{
				p->next->data++;
				re->data = p->data - 10;
			}
			else
			{
				re->next->data = 1;
				re->data = p->data - 10;
				mark++;
			}
		}
		else { re->data = p->data; }
		p = p->next;
		re = re->next;

		if (mark == 0 && p == NULL) { re->data = 0; }
	}

}

//减法 传入的参数为减数
void LinkList::minusBig(LinkList& b, LinkList& result)
{
	Node* r = result.first;
	while (r != 0)
	{
		r->data = 0;
		r = r->next;
	}

	Node* p = first;
	Node* q = b.first;
	Node* re = result.first;
	while (q != NULL)
	{
		if (p->data < q->data)
		{
			p->next->data--;
			re->data = p->data + 10 - q->data;
		}
		else { re->data = p->data - q->data; }

		p = p->next;
		q = q->next;
		re = re->next;
	}
	//此时 减数已到达最大长度
	while (p != NULL)
	{
		if (p->data < 0)//前面是0的借位 该位将变为-1
		{
			p->next->data--;
			re->data = p->data + 10;
		}
		else { re->data = p->data; }
		p = p->next;
		re = re->next;
	}
}

int main()
{
	try {
		int k1, k2;
		cout << "请您输入第一个大整数与第二个大整数的位数，用空格分开" << endl;
		cin >> k1 >> k2;
		if ((k1 < 0) || (k1 > 49) || (k2 < 0) || (k2 > 49))
			throw "位数输入不合法";

		srand((unsigned)time(NULL));
		LinkList a(k1);
		LinkList b(k2);

		cout << "第一个大整数为：" << endl;
		a.show();
		cout << "第二个大整数为：" << endl;
		b.show();

		cout << "请选择进行加法（输入1）或 减法（输入2） " << endl;
		int k;
		cin >> k;
		if (k == 1)//加法
		{
			LinkList result(k1 > k2 ? k1 + 1 : k2 + 1);
			int compare = a.compare(b);
			if (compare == 1)
			{
				a.addBig(b, result);
			}
			else { b.addBig(a, result); }
			cout << "运算结果绝对值：" << endl;
			result.show();
			result.~LinkList();
		}
		else if (k == 2) //减法
		{
			LinkList result(k1 > k2 ? k1 : k2);
			int compare = a.compare(b);
			if (compare == 1)
			{
				a.minusBig(b, result);
			}
			else { b.minusBig(a, result); }
			cout << "运算结果绝对值：" << endl;
			result.show();
			result.~LinkList();
		}
		a.~LinkList();
		b.~LinkList();
		return 0;
	}
	catch (const char* e)
	{
		cout << e << endl;
	}
}