#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//假设编码aaabbccde字符串，其中每个字符  a：0   b：10    c：110  d:1110  e:1111
struct CodeTable
{
	char ch;
	char code[10];
};
CodeTable table[10] = { { 'a',"0" },{ 'b',"10" },{ 'c',"110" } ,{ 'd',"1110" },{ 'e',"1111" } };

void WriteBinaryFile(char *filename,char *s, CodeTable table[],int n);
void ReadBinaryFile(char *filename, CodeTable table[],int n);

void main()
{
	WriteBinaryFile("abc.dat", "aaabbccde", table, 5);
	cout << endl;
	ReadBinaryFile("abc.dat", table, 5);
	cout << "\n最后字符多出了3个字符a， 是因为写文件的时候不足8bit，填充了3个0导致，请同学们自行思考如何解决！"<<endl;
}
//*s为待编码的字符，table为编码表 ,返回值为最后一个字符不足8bit的差值
void WriteBinaryFile(char *filename, char *s, CodeTable table[], int n)
{
	ofstream out(filename, ios::binary); //二进制读写文件
	if (out.fail())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	unsigned char tmp = 0x0;
	
	int count = 0;//0-7,表示的是一个BYTE是否已经充满
	while (*s != '\0')
	{
		for (int i = 0; i < n; i++)
		{
			if (*s == table[i].ch)
			{
				//处理bit位
				char *t = table[i].code;
				while (*t!='\0')
				{
					if (*t == '0'){
						tmp = tmp & 0xFE; 		cout << "0";
					}
					else{
						tmp = tmp | 0x01;		cout << "1";
					}
					if (count == 7){//1个字节满了，可以写文件
						cout << " ";
						out << tmp;
						count = 0;
						tmp = 0x0;
					}
					else{
						tmp = tmp << 1;
						count++;
					}
					t++;
				}
				break;
			}
		}
		s++;
	}
	if (count != 0){ //最后一个字节编码不足 8个bit
		tmp = tmp << 7 - count ;
		out << tmp;
		out.close();
	}
	return;
}

void ReadBinaryFile(char *filename, CodeTable table[], int n )
{
	ifstream in(filename, ios::binary); //二进制读写文件
	if (in.fail())
	{
		cout << "文件打开失败！" << endl;
		return;
	}
	unsigned char tmp = 0x0;
	char code[100] = {0};
	int count = 0;
	tmp = in.get();
	while (!in.eof())
	{
		for (int k = 0; k < 8; k++)
		{
			if ((tmp & 0x80) == 0)
				strcat(code, "0");
			else
				strcat(code, "1");
			tmp = tmp << 1;

			for (int i = 0; i < n; i++)
			{
				if (strcmp(code, table[i].code)==0)
				{
					cout << table[i].ch;
					memset(code, 0, sizeof(code));
					break;
				}
			}
		}
		tmp = in.get();
	}
	in.close();

}