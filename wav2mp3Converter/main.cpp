#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "fileUtils.h"
#include "platform.h"

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

class thread1;

static void processFiles()
{
    const auto coreCount = std::min(int(files.size()), platform::coreCount());

    std::vector<thread1> threads;
    threads.reserve(coreCount);
    for (auto i = 0; i < coreCount; ++i)
    {
        threads.emplace_back([]()
        {
            while (true)
            {
                auto file = getNextFile();
                if (file.empty())
                    return;

                std::cout << "processing " << file << std::endl;
                convertFile(file);
            }
        });
    }

    for (const auto& t : threads)
        t.join();
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

    for (const auto& f : files)
        std::cout << f << std::endl;

    processFiles();

    std::cout << "done" << std::endl;
    return 0;
}
