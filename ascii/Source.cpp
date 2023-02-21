#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, " ");
	for (int i = 0; i < 255; i++)
	{
		cout << (char)i <<' ' << i << endl;
	}
}
