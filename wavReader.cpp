#include "wavReader.h"

#include <fstream>

bool wavHeader::isOk() const
{
    return
        std::string(riff_, sizeof(riff_)) == "RIFF" &&
        std::string(wave_, sizeof(wave_)) == "WAVE" &&
        std::string(fmt_, sizeof(fmt_)) == "fmt " &&
        std::string(data_, sizeof(data_)) == "data" &&
        audioFormat_ == 1 && // PCM only
        (numberOfChannels_ == 1 || numberOfChannels_ == 2) && // mono and stereo
        (bitsPerSample_ == 8 || bitsPerSample_ == 16 || bitsPerSample_ == 24 || bitsPerSample_ == 32);
}


wavReader::wavReader(const std::string& _path)
    : input_(_path, std::ios_base::in | std::ios_base::binary)
{
    if (!input_.is_open())
        return;

    if (!input_.read(reinterpret_cast<char*>(&header_), sizeof(header_)))
        return;

    if (!header_.isOk())
        return;

    const auto bytesPerSample = header_.bitsPerSample_ / 8;
    const auto numberOfSamples = header_.dataSize_ / bytesPerSample;
    if (header_.dataSize_ != sizeof(short) * numberOfSamples)
        return;

    std::vector<short> samples;
    samples.resize(numberOfSamples);
    if (!input_.read(reinterpret_cast<char*>(samples.data()), header_.dataSize_))
        return;

    std::swap(samples, samples_);
    isOk_ = true;
}
