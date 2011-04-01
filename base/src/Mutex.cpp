#include "Mutex.h"

namespace base
{
Mutex::Mutex()
{
    int errorCode = pthread_mutex_init(&mMutexObject, NULL);
    if(errorCode != 0)
        throw InternalMutexError(errorCode);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mMutexObject);
}

void Mutex::lock()
{
    int errorCode = pthread_mutex_lock(&mMutexObject);
    if(errorCode != 0)
        throw InternalMutexError(errorCode);
}

void Mutex::unlock()
{
    int errorCode = pthread_mutex_unlock(&mMutexObject);
    if(errorCode != 0)
        throw InternalMutexError(errorCode);
}
}
