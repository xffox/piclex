#include "Sentence.h"

namespace search
{
Sentence sentence(const std::string &str)
{
    //TODO: optimize

    Sentence s;
    for(size_t i = 0; i < str.size(); ++i)
        s.push_back(Symbol(str[i]));
    return s;
}
}
