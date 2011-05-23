#ifndef CLONABLE_H
#define CLONABLE_H

namespace base
{
template<class T>
class Clonable
{
public:
    virtual ~Clonable(){}

    virtual T *clone() const = 0;
};

}

#endif//CLONABLE_H
