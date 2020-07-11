#pragma once

#include "lame.h"

#include <string>
#include <array>
#include <fstream>
#include <vector>

class lameEncoder
{
public:
    lameEncoder(
        const std::string& _outputPath, 
        int _numberOfChannels, 
        int _sampleRate,
        int _bitsPerSample,
        int _dataSize);

    ~lameEncoder();

    void encodeMono(const std::vector<short>& _samples);
    void encodeStereo(std::vector<short> _samples);

    bool isOk() const noexcept { return isOk_; }

private:
    lame_t lame_;
    std::ofstream output_;
    bool isOk_ = false;
};