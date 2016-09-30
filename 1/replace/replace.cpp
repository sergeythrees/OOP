#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool AreArgumentsTrue(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Wrong arguments amount\n"
		<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return false;
	}
	if (!(argv[1] && argv[2]))
	{
		cout << "Same file\n";
		return false;
	}
	if (strlen(argv[3]) == 0)
	{
		cout << "Search string length = 0\n";
		return false;
	}

	return true;
}
bool AreFilesOpen(fstream &inputFile, ofstream &outputFile)
{
	if (!inputFile.is_open())
	{
		cout << "Error with opening input file \n";
		return false;
	}

	if (!outputFile.is_open())
	{
		cout << "Error with opening output file \n";
		return false;
	}
	return true;
}
string ReplaceSubString(const string &inputLine, const string &searchString, const string &replaceString)
{
	size_t readPosition = 0, foundPosition = 0;
	string resultString;
	bool isFound = false;
	while ((foundPosition = inputLine.find(searchString, readPosition)) != inputLine.npos)
	{
		resultString.append(inputLine, readPosition, foundPosition - readPosition);
		resultString.append(replaceString);
		readPosition = foundPosition + searchString.length();
		isFound = true;
	}
	if (!isFound)
		return inputLine;

	if (readPosition < inputLine.length())
	{
		resultString.append(inputLine, readPosition, inputLine.length() - readPosition);
	}
	return resultString;
}
bool IsSearchStringReplace(fstream &inputFile, ofstream &outputFile, const string &searchString, const string &replaceString)
{
	string currentLine, resultLine;
	bool areSearchStringFound = false;
	while (getline(inputFile, currentLine))
	{
		if (currentLine != (resultLine = ReplaceSubString(currentLine, searchString, replaceString)))
		{
			outputFile << resultLine;
			if (!inputFile.eof())
				outputFile << endl;
			areSearchStringFound = true;
		}
			
	}
	return areSearchStringFound;
}
int main(int argc, char *argv[])
{
	if (!AreArgumentsTrue(argc, argv))
		return 1;
	fstream input(argv[1]);
	ofstream output(argv[2]);
	if (!AreFilesOpen(input, output))
		return 1;

	string searchString = argv[3], replaceString = argv[4];

	if (!IsSearchStringReplace(input, output, searchString, replaceString))
		cout << "String '" << searchString << "' hasn't been found.\n";
	
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}

