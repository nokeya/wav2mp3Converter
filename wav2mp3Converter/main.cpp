#include <iostream>
#include <vector>
#include <string>

static std::vector<std::string> files;
static std::string getNextFile()
{
	std::string file;

	{
		if (!files.empty())
		{
			file = std::move(files.back());
			files.pop_back();
		}
	}

	return file;
}

static std::vector<std::string> getFiles(const char* _folder)
{
	return {};
}

static void processFiles()
{

}

int main(int _argc, char** _argv)
{
	if (_argc < 2)
	{
		std::cout << "no folder provided" << std::endl;
		return 1;
	}

	files = getFiles(_argv[1]);
	if (files.empty())
	{
		std::cout << "no WAV files found" << std::endl;
		return 1;
	}

	processFiles();

	std::cout << "done" << std::endl;
	return 0;
}
