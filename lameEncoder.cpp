#include "lameEncoder.h"



lameEncoder::lameEncoder(
    const std::string& _outputPath,
    int _numberOfChannels,
    int _sampleRate,
    int _bitsPerSample,
    int _dataSize)
	: lame_(lame_init())
	, output_(_outputPath, std::ios_base::out | std::ios_base::binary)
{
	if (!lame_ || output_.is_open())
		return;

	lame_set_quality(lame_, 5);

	if (lame_set_num_channels(lame_, _numberOfChannels) < 0)
		return;

	if (_numberOfChannels == 1)
		lame_set_mode(lame_, MONO);

	if (lame_set_in_samplerate(lame_, _sampleRate) < 0)
		return;

	lame_set_num_samples(lame_, _dataSize / (_numberOfChannels * (_bitsPerSample >> 3)));
	lame_set_write_id3tag_automatic(lame_, 1);

	if (lame_init_params(lame_) < 0)
		return;

	isOk_ = true;
}

lameEncoder::~lameEncoder()
{
	if (lame_)
		lame_close(lame_);
}

void lameEncoder::encodeMono(const std::vector<short>& _samples)
{
	std::vector<unsigned char> buffer;
	buffer.resize(_samples.size() * 5 / 4 + 7200);

	int encodedSize = lame_encode_buffer(
		lame_, 
		_samples.data(), 
		_samples.data(), 
		int(_samples.size()), 
		buffer.data(), 
		int(buffer.size()));

	if (encodedSize < 0)
		return;

	encodedSize += lame_encode_flush(lame_, buffer.data() + encodedSize, int(buffer.size() - encodedSize));
	output_.write(reinterpret_cast<char*>(buffer.data()), encodedSize);
}

void lameEncoder::encodeStereo(std::vector<short> _samples)
{
	std::vector<unsigned char> buffer;
	buffer.resize(_samples.size() * 5 / 4 + 7200);

	int encodedSize = lame_encode_buffer_interleaved(
		lame_, 
		_samples.data(), 
		int(_samples.size() / 2),
		buffer.data(), 
		int(buffer.size()));

	if (encodedSize < 0)
		return;

	encodedSize += lame_encode_flush(lame_, buffer.data() + encodedSize, int(buffer.size() - encodedSize));
	output_.write(reinterpret_cast<char*>(buffer.data()), encodedSize);
}