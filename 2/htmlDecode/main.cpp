
#include "stdafx.h"
#include <iostream>
#include "Decode.h"

using namespace std;

void DecodeHtmlLines()
{
	string inputText;
	char c;
	
	while (cin.get(c))
	{
		inputText += c;
	}
		
	cout << DecodeHtmlText(inputText) << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cout << "������� ����� � HTML" << endl
		<< "��� ��������� ����� ������� Ctrl+Z � ENTER � ������ ������" << endl;

	DecodeHtmlLines();

	return 0;
}