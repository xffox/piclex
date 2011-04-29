#ifndef SENTENCE_H
#define SENTENCE_H

#include <vector>
#include <string>

#include "Symbol.h"

namespace search
{
typedef std::vector<Symbol> Sentence;

Sentence sentence(const std::string &str);
std::string makeString(const Sentence &sentence);
std::string makeString(const Sentence &sentence,
        size_t begin, size_t end);
}

#endif//SENTENCE_H
