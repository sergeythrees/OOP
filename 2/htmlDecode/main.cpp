
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

	cout << "¬ведите текст с HTML" << endl
		<< "ƒл€ окончани€ ввода нажмите Ctrl+Z и ENTER в пустой строке" << endl;

	DecodeHtmlLines();

	return 0;
}