# Batch WAV to MP3 converter  
Application is called with pathname as argument, e.g. `wav2mp3Converter.exe F:\MyWavCollection` all WAV-files contained directly in that folder are to be encoded to MP3

## Dependencies
* cmake
* dirent (included)
* pthreads_w32 (Windows only, included)
* LAME (included)

Made custom CMakeLists.txt for LAME library static build  
Tested with Microsft Visual Studio 2019 and GCC 9.3.0 (64bit)
