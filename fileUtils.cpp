#include "fileUtils.h"
#include "platform.h"

#ifdef _WIN32
#include "dirent/dirent.h"
#else
#include <sys/stat.h>
#include <dirent.h>
#endif

#include <algorithm>

namespace
{
    enum class pathType
    {
        invalid,

        folder,
        file,
    };

    static pathType getPathType(const std::string& _path)
    {
        struct stat fs;
        if (stat(_path.c_str(), &fs) == 0)
        {
            if (S_ISDIR(fs.st_mode))
                return pathType::folder;
            else if (S_ISREG(fs.st_mode))
                return pathType::file;
        }
        return pathType::invalid;
    }

    const std::string wavExt = ".wav";
    const std::string mp3Ext = ".mp3";
}

std::vector<std::string> getFiles(const std::string& _path)
{
    std::vector<std::string> result;

    const auto type = getPathType(_path);
    if (type == pathType::folder)
    {
        const auto addSlash = _path.back() != platform::slash();
        if (DIR* d = opendir(_path.c_str()))
        {
            dirent* de;
            while ((de = readdir(d)) != nullptr)
            {
                std::string name(de->d_name);

                if (name == "." || name == ".." || name.size() <= wavExt.size())
                    continue;

                auto ext = name.substr(name.size() - 4);
                std::transform(ext.begin(), ext.end(), ext.begin(), [](char c) { return std::tolower(c); });
                if (ext != wavExt)
                    continue;

                auto fullPath = _path;
                if (addSlash)
                    fullPath += platform::slash();
                fullPath += name;

                if (getPathType(fullPath) == pathType::file)
                    result.emplace_back(std::move(fullPath));
            }
            closedir(d);
        }
    }
    else if (type == pathType::file)
    {
        result.emplace_back(_path);
    }

    return result;
}

std::string replaceExtension(const std::string& _file)
{
    return _file.substr(0, _file.size() - wavExt.size()) + mp3Ext;
}
