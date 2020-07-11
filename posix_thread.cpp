#include "posix_thread.h"

posix_thread::posix_thread(thread_func _f)
    : func_(_f)
{
    pthread_create(&thread_, nullptr, &posix_thread::wrapper, this);
}

void posix_thread::join() const
{
    pthread_join(thread_, nullptr);
}

void* posix_thread::wrapper(void* arg)
{
    auto thrd = reinterpret_cast<posix_thread*>(arg);
    thrd->func_();
    return 0;
}