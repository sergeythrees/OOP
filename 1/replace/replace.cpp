#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
static const int MAX_NUM_OF_ARGUMENTS = 5;

bool AreFilesOpened(const ifstream &input, const ofstream &output)
{
	if (!input.is_open())
	{
		cout << "Error with opening input file \n";
		return false;
	}

	if (!output.is_open())
	{
		cout << "Error with opening output file \n";
		return false;
	}
	return true;
}
bool IsValidArgumentsCount(int argumensCount)
{
	if (argumensCount != MAX_NUM_OF_ARGUMENTS)
	{
		cout << "Wrong arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return false;
	}

	return true;
}
bool IsSearchStringNotEmpty(const string &searchString)
{
	if (searchString.empty())
	{
		cout << "Search string should not be empty\n";
		return false;
	}

	return true;
}
string::size_type KMP_search(const string& inputLine, size_t begin, const string& searchString) {
	vector<size_t> prefixFunction(searchString.length());

	prefixFunction[0] = 0;
	for (size_t k = 0, readPos = 1; readPos < searchString.length(); ++readPos) {
		while (k > 0 && searchString[readPos] != searchString[k])
			k = prefixFunction[k - 1];

		if (searchString[readPos] == searchString[k])
			k++;

		prefixFunction[readPos] = k;
	}

	for (size_t k = 0, readPos = begin; readPos < inputLine.length(); ++readPos) {
		while ((k > 0) && (searchString[k] != inputLine[readPos]))
			k = prefixFunction[k - 1];

		if (searchString[k] == inputLine[readPos])
			k++;

		if (k == searchString.length())
			return (readPos - searchString.length() + 1);//либо продолжаем поиск следующих вхождений
	}

	return (string::npos);
}
void ReplaceSubString(string &inputLine, const string &searchString, const string &replaceString)
{
	if ((searchString == replaceString) || searchString.empty())
		return;

	size_t foundPosition = 0;
	size_t currentPosition = 0;
	size_t numberOfReplacements = 0;
	string result;
	result.reserve(inputLine.length());

	while ((foundPosition = KMP_search(inputLine, currentPosition, searchString)) != string::npos)
	{
		result.append(inputLine, currentPosition, foundPosition - currentPosition);
		result += replaceString;
		currentPosition = foundPosition + searchString.length();
	}

	if (currentPosition != 0)
		inputLine = result.append(inputLine, currentPosition, inputLine.length() - currentPosition);
}
void Replace(ifstream &input, ofstream &output, const string &searchString, const string &replaceString)
{
	size_t numberOfReplacements = 0;
	string currentLine;
	while (getline(input, currentLine))
	{
		ReplaceSubString(currentLine, searchString, replaceString);
		output << currentLine;
		if (!input.eof())
			output << endl;
	}
}
bool IsFileSaved(ofstream &outputFile)
{
	if (!outputFile.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}
int main(int argc, char *argv[])
{
	if (!IsValidArgumentsCount(argc))
		return 1;

	if (!IsSearchStringNotEmpty(argv[3]))
		return 1;

	ifstream input(argv[1]);
	ofstream output(argv[2]);
	if (!AreFilesOpened(input, output))
		return 1;

	Replace(input, output, argv[3], argv[4]);

	if (!IsFileSaved(output))
		return 1;

	return 0;
}

