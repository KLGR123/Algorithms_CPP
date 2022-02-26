#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//�������aaabbccde�ַ���������ÿ���ַ�  a��0   b��10    c��110  d:1110  e:1111
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
	cout << "\n����ַ������3���ַ�a�� ����Ϊд�ļ���ʱ����8bit�������3��0���£���ͬѧ������˼����ν����"<<endl;
}
//*sΪ��������ַ���tableΪ����� ,����ֵΪ���һ���ַ�����8bit�Ĳ�ֵ
void WriteBinaryFile(char *filename, char *s, CodeTable table[], int n)
{
	ofstream out(filename, ios::binary); //�����ƶ�д�ļ�
	if (out.fail())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		return;
	}
	unsigned char tmp = 0x0;
	
	int count = 0;//0-7,��ʾ����һ��BYTE�Ƿ��Ѿ�����
	while (*s != '\0')
	{
		for (int i = 0; i < n; i++)
		{
			if (*s == table[i].ch)
			{
				//����bitλ
				char *t = table[i].code;
				while (*t!='\0')
				{
					if (*t == '0'){
						tmp = tmp & 0xFE; 		cout << "0";
					}
					else{
						tmp = tmp | 0x01;		cout << "1";
					}
					if (count == 7){//1���ֽ����ˣ�����д�ļ�
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
	if (count != 0){ //���һ���ֽڱ��벻�� 8��bit
		tmp = tmp << 7 - count ;
		out << tmp;
		out.close();
	}
	return;
}

void ReadBinaryFile(char *filename, CodeTable table[], int n )
{
	ifstream in(filename, ios::binary); //�����ƶ�д�ļ�
	if (in.fail())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
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