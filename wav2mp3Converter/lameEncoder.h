#pragma once

#include <string>

class lameEncoder
{
public:
    lameEncoder(
        const std::string& _outputPath, 
        int _numberOfChannels, 
        int _sampleRate,
        int _bitsPerSample,
        int _dataSize);
};