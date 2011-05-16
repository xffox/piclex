#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <map>
#include <vector>
#include <string>

#include "SearchDefines.h"

namespace search
{
typedef std::vector<DocId> Postings;

class InvertedIndex
{
    typedef std::map<Term, Postings> Index;

public:
    InvertedIndex &operator+=(const InvertedIndex &that);

    InvertedIndex &operator&=(const InvertedIndex &that);

    void insert(const Term &term, DocId id);

    const Postings &getPostings(const Term &term) const;

    size_t getFrequency(const Term &term) const;

    size_t getSize() const;

    void clear();

private:
    Index mIndex;

    static const Postings emptyPostings;
};

Postings operator&(const Postings &left, const Postings &right);
bool isContain(const Postings &postings, DocId id);

}

#endif//INVERTED_INDEX_H
