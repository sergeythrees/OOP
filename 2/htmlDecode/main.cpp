
#include "stdafx.h"
#include <iostream>
#include "Decode.h"

using namespace std;

void DecodeHtmlLines()
{
	string inputText, temp;
	char c;
	
	while (cin.get(c))
	{
		inputText += c;
	}
		
	cout << DecodeHtmlText(inputText);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������� ����� � HTML" << endl
		<< "��� ��������� ����� ������� Ctrl+Z � ENTER � ������ ������" << endl;
	DecodeHtmlLines();
	cout << endl;

	return 0;
}