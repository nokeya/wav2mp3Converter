#pragma once

#include <string>
#include <vector>

std::vector<std::string> getFiles(const std::string& _path);
std::string replaceExtension(const std::string& _file);