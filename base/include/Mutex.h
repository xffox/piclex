#ifndef MUTEX_H
#define MUTEX_H

// linux impl
#include <pthread.h>

namespace base
{
class InternalMutexError
{
public:
    InternalMutexError(int errorCode)
        :mErrorCode(errorCode)
    {
    }

    int getErrorCode() const
    {
        return mErrorCode;
    }

private:
    int mErrorCode;
};

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
    // linux impl
    pthread_mutex_t mMutexObject;
};
}

#endif//MUTEX_H
