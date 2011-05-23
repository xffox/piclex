#ifndef BASE_EXCEPTIONS_H
#define BASE_EXCEPTIONS_H

#include <cstddef>

namespace base
{
class BaseException
{
};

class OutOfBoundError: public BaseException
{
public:
    OutOfBoundError(size_t index, size_t bound)
        :mIndex(index), mBound(bound)
    {
    }

    size_t getIndex() const
    {
        return mIndex;
    }

    size_t getBound() const
    {
        return mBound;
    }

private:
    size_t mIndex;
    size_t mBound;
};

class NotFoundError: public BaseException
{
};

class InvalidArgument: public BaseException
{
};

//! Some programming error
/*!
 * InfernalError)
 */
class InternalError: public BaseException
{
};

}

#endif//BASE_EXCEPTIONS_H
