#include <iosfwd>
#include <iostream>
using namespace std;

//1 数据类型T（任意）
//2 数据长度L（任意）
//3 通用操作（算法）：插入 删除 查找 输出


//T 形式化参数
template <class T,int N> class Seqlist
{
	//数据成员
private:
	T data[N];
	int length; //有效数据长度
	//成员函数
public:
	Seqlist() { length = 0; }
	void Insert(T e, int pos);
	T Remove(int pos);
	int Locate(T e);
	T Search(int pos);
	void print();
};

template <class T, int N>
void Seqlist<T,N>::Insert(T e, int pos)
{
	//异常处理 防止由于用户输入不当导致的程序崩溃
	if (pos < 1 || pos > length+1)
		throw "插入位置异常。";  //抛出异常

	//for (int j = length ; j >= pos; j--) //后移
	//	data[j] = data[j - 1];

	for (int j = length-1 ; j >= pos-1 ; j--) //后移
		data[j+1] = data[j];
	
	data[pos - 1] = e;
	length++;
	return;
}
template <class T, int N>
T Seqlist<T, N>::Remove(int pos) //计算时间复杂度
{
	//异常处理 防止由于用户输入不当导致的程序崩溃
		if (pos < 1 || pos > length)
			throw "删除位置异常。";  //抛出异常
			
		T t = data[pos - 1];
		//正常执行代码
		for (int i = pos-1 ; i < length-1 ; i++) //前移
			data[i] = data[i + 1];
		
		//for (int i = pos ; i < length ; i++)//前移
		//	data[i-1] = data[i];
		length--;
		return t;
}
template <class T, int N>
int Seqlist<T, N>::Locate(T e)
{
	for (int i = 0; i < length; i++) 
		if (data[i] == e)
			return i + 1;
	return 0;
}

template <class T, int N>
T Seqlist<T, N>::Search(int pos)
{
	if (pos < 1 || pos > length)
		throw "查找位置异常。";  //抛出异常

	return data[pos - 1];
}
template <class T, int N>
void Seqlist<T, N>::print()
{
	for (int i = 0; i < length; i++)   
		cout << data[i]<<endl;
}

struct STUDENT {
	char name[20];
	int age;
	int gender;
	float score;
};

//运算符重载 ==》函数重载==》函数名是运算符的函数  cout属于什么类？ ostream  cin属于什么类？  istream
ostream & operator <<(ostream & out, STUDENT& s)
{
	out << s.name << "\t" << s.age << "\t" << s.gender << "\t" << s.score;
	return out;
}
bool operator ==(STUDENT& s1, STUDENT& s2)
{
	if (strcmp(s1.name, s2.name) == 0)
		return true;
	return false;
}

//学籍管理系统
void main()
{
	Seqlist<STUDENT,1000> list;
	try
	{
		STUDENT s[4] = { {"abc",19,1,88},{ "bcd",18,0,82 },{ "cde",19,0,90 }, { "efg",19,1,77 } };
		list.Insert(s[0], 1);
		list.Insert(s[1], 2);
		list.Insert(s[2], 3);
		list.Insert(s[3], 4);
		list.print();
		
		int pos = list.Locate(s[1]);
		cout << pos << endl;

		list.Remove(2);
		list.print();
	
	}
	catch (const char *e)
	{
		cout << e <<endl;
		return;
	}
}


