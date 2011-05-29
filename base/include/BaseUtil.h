#ifndef BASE_UTIL_H
#define BASE_UTIL_H

#include <vector>
#include <set>

namespace base
{
template<class T>
void vectorToSet(std::set<T> &out, const std::vector<T> &in)
{
    out.clear();

    typename std::vector<T>::const_iterator inIter = in.begin();
    for(; inIter != in.end(); ++inIter)
        out.insert(*inIter);
}

}

#endif//BASE_UTIL_H
