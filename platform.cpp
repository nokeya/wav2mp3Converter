#include "platform.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif 

namespace platform
{
    char slash()
    {
#ifdef _WIN32
        return '\\';
#endif 
        return '/';
    }

    int coreCount()
    {
#ifdef _WIN32
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        return sysinfo.dwNumberOfProcessors;
#else
        return sysconf(_SC_NPROCESSORS_ONLN);
#endif 
    }
}