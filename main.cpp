#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <mutex>

#include "fileUtils.h"
#include "platform.h"
#include "posix_thread.h"
#include "wavReader.h"
#include "lameEncoder.h"

static std::vector<std::string> files;

std::string getNextFile()
{
    std::string file;
    {
        static std::mutex filesMtx;
        std::lock_guard<std::mutex> lock(filesMtx);

        if (!files.empty())
        {
            file = std::move(files.back());
            files.pop_back();
        }
    }
    return file;
}

static void sync(std::function<void()> _func)
{
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    _func();
}

static void convertFile(const std::string& _inFile, const std::string& _outFile)
{
    wavReader reader(_inFile);
    if (!reader.isOk())
    {
        sync([&_inFile]() { std::cout << "skipping invalid file " << _inFile << std::endl; });
        return;
    }

    lameEncoder encoder(_outFile, reader.numberOfChannels(), reader.sampleRate(), reader.bitsPerSample(), reader.dataSize());
    if (!encoder.isOk())
    {
        sync([&_inFile]() { std::cout << "LAME init error for " << _inFile << std::endl; });
        return;
    }

    if (reader.numberOfChannels() == 1)
        encoder.encodeMono(reader.samples());
    else
        encoder.encodeStereo(reader.samples());
}

static void processFiles()
{
    const auto coreCount = std::min(int(files.size()), platform::coreCount());

    std::vector<posix_thread> threads;
    threads.reserve(coreCount);
    for (auto i = 0; i < coreCount; ++i)
    {
        threads.emplace_back([]()
        {
            while (true)
            {
                const auto file = getNextFile();
                if (file.empty())
                    return;
                   
                sync([&file]() { std::cout << "processing " << file << std::endl; });
                convertFile(file, replaceExtension(file));
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

    processFiles();

    std::cout << "done" << std::endl;
    return 0;
}
