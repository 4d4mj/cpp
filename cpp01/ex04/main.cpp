#include <iostream>
#include <fstream>
#include <string>

void replaceInFile(const std::string &filename, const std::string &s1, const std::string &s2)
{
	// Open the input file
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		std::cerr << "Error: Could not open file." << std::endl;
		return;
	}

	// Read file content into a string
	std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
	inputFile.close();

	// Replace occurrences of s1 with s2 manually
	size_t pos = 0;
	while ((pos = content.find(s1, pos)) != std::string::npos)
	{
		content.erase(pos, s1.length());
		content.insert(pos, s2);
		pos += s2.length();
	}

	// Write the modified content to a new file
	std::ofstream outputFile(filename + ".replace");
	if (!outputFile.is_open())
	{
		std::cerr << "Error: Could not create output file." << std::endl;
		return;
	}
	outputFile << content;
	outputFile.close();
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	replaceInFile(filename, s1, s2);

	return 0;
}
