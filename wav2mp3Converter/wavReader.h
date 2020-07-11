#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

struct wavHeader
{
    char     riff_[4];
    uint32_t riffSize_;
    char     wave_[4];
    char     fmt_[4];
    uint32_t fmtSize_;
    uint16_t audioFormat_;
    uint16_t numberOfChannels_;
    uint32_t samplesPerSecond_;
    uint32_t bytesPerSecond_;
    uint16_t blockAlignment_;
    uint16_t bitsPerSample_;
    char     data_[4];
    uint32_t dataSize_;

    bool isOk() const;
};

class wavReader
{
public:
    wavReader(const std::string& _path);

    bool isOk() const noexcept { return isOk_; }

    int numberOfChannels() const noexcept { return header_.numberOfChannels_; }
    int sampleRate() const noexcept { return header_.samplesPerSecond_; }
    int bitsPerSample() const noexcept { return header_.bitsPerSample_; }
    int dataSize() const noexcept { return header_.dataSize_; }

    const std::vector<short>& samples() const noexcept { return samples_; }

private:
    std::ifstream input_;
    wavHeader header_;
    std::vector<short> samples_;
    bool isOk_ = false;
};