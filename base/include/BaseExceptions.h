#ifndef BASE_EXCEPTIONS_H
#define BASE_EXCEPTIONS_H

namespace base
{
class BaseException
{
};

class OutOfBoundError: public BaseException
{
public:
    OutOfBoundError(size_t index, size_t length)
        :mIndex(index), mLength(length)
    {
    }

    size_t getIndex() const
    {
        return mIndex;
    }

    size_t getLength() const
    {
        return mLength;
    }

private:
    size_t mIndex;
    size_t mLength;
};

class NotFoundError: public BaseException
{
};

}

#endif//BASE_EXCEPTIONS_H
