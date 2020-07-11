#include "wavReader.h"

#include <fstream>

bool wavHeader::isOk() const
{
    return
        std::string(riff_, sizeof(riff_)) == "RIFF" &&
        std::string(wave_, sizeof(wave_)) == "WAVE" &&
        std::string(fmt_, sizeof(fmt_)) == "fmt " &&
        std::string(data_, sizeof(data_)) == "data" &&
        audioFormat_ == 1 && 
        (numberOfChannels_ == 1 || numberOfChannels_ == 2) &&
        (bitsPerSample_ == 8 || bitsPerSample_ == 16 || bitsPerSample_ == 24 || bitsPerSample_ == 32);
}


wavReader::wavReader(const std::string& _path)
    : input_(_path, std::ios_base::in | std::ios_base::binary)
{
    if (input_.is_open())
    {
        if (input_.read(reinterpret_cast<char*>(&header_), sizeof(header_)))
            isOk_ = header_.isOk();
    }        
}

bool wavReader::isOk() const
{
    return isOk_;
}