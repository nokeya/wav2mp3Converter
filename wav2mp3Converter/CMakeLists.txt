# CMakeList.txt : CMake project for wav2mp3Converter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (wav2mp3Converter "main.cpp"  "fileUtils.cpp" "fileUtils.h")

# TODO: Add tests and install targets if needed.
