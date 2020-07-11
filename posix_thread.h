#pragma once

#include "pthread.h"

#include <functional>

class posix_thread
{
public:
    using thread_func = std::function<void()>;
    posix_thread(thread_func _f);

    void join() const;

private:
    static void* wrapper(void* arg);

private:
    pthread_t thread_;
    thread_func func_;
};