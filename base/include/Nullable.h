#ifndef NULLABLE_H
#define NULLABLE_H

#include "BaseExceptions.h"

namespace base
{
class NullException: public BaseException
{
};

template<class T>
class Nullable
{
public:
    Nullable();
    Nullable(const T &value);

    T &getValue();
    const T &getValue() const;

    bool isNull() const;

    static const Nullable<T> &Null();

private:
    T mValue;
    bool mNulled;

    static const Nullable<T> null;
};

template<class T>
Nullable<T>::Nullable()
    :mNulled(true)
{
}

template<class T>
Nullable<T>::Nullable(const T &value)
    :mValue(value), mNulled(false)
{
}

template<class T>
T &Nullable<T>::getValue()
{
    if(!mNulled)
        return mValue;
    throw NullException();
}

template<class T>
const T &Nullable<T>::getValue() const
{
    return const_cast<Nullable<T>*>(this)->getValue();
}

template<class T>
bool Nullable<T>::isNull() const
{
    return mNulled;
}

template<class T>
const Nullable<T> &Nullable<T>::Null()
{
    return null;
}

template<class T>
const Nullable<T> Nullable<T>::null = Nullable<T>();

}

#endif//NULLABLE_H
