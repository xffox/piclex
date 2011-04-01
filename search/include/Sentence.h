#ifndef SENTENCE_H
#define SENTENCE_H

#include <vector>
#include <string>

#include "Symbol.h"

namespace search
{
typedef std::vector<Symbol> Sentence;

Sentence sentence(const std::string &str);
}

#endif//SENTENCE_H
