#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
	if (argumensCount != 5)
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
size_t ReplaceSubString(const string &inputLine, const string &searchString, const string &replaceString, ofstream &output)
{
	size_t foundPosition = inputLine.find(searchString, 0);
	if (foundPosition == inputLine.npos)
	{
		output << inputLine;
		return 0;
	}
		
	size_t currentPosition = 0, numberOfReplacements = 0;
	string result;
	while (foundPosition != inputLine.npos)
	{
		result.append(inputLine, currentPosition, foundPosition - currentPosition);
		result += replaceString;
		currentPosition = foundPosition + searchString.length();
		foundPosition = inputLine.find(searchString, currentPosition);
		++numberOfReplacements;
	}
	output << result.append(inputLine, currentPosition, inputLine.length() - currentPosition);

	return numberOfReplacements;
}
void Replace(ifstream &input, ofstream &output, const string &searchString, const string &replaceString)
{
	size_t numberOfReplacements = 0;
	string currentLine;
	while (getline(input, currentLine))
	{
		numberOfReplacements += ReplaceSubString(currentLine, searchString, replaceString, output);
		if (!input.eof())
			output << endl;
	}
	cout << "Number of replacements: " << numberOfReplacements << "\n";
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

