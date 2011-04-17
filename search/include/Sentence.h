#ifndef SENTENCE_H
#define SENTENCE_H

#include <vector>
#include <string>

#include "Symbol.h"

namespace search
{
typedef std::vector<Symbol> Sentence;

Sentence sentence(const std::string &str);
const std::string makeString(const Sentence &sentence);
}

#endif//SENTENCE_H
