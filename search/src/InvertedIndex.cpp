#include "InvertedIndex.h"

namespace search
{
InvertedIndex &InvertedIndex::operator+=(const InvertedIndex &that)
{
    if(this == &that)
        return *this;

    Index::const_iterator termIter = that.mIndex.begin();
    Postings::const_iterator postingsIter;
    for(; termIter != that.mIndex.end(); ++termIter)
    {
        const Postings &postings = (*termIter).second;
        postingsIter = postings.begin();
        for(; postingsIter != postings.end(); ++postingsIter)
            insert((*termIter).first, *postingsIter);
    }

    return *this;
}

InvertedIndex &InvertedIndex::operator&=(const InvertedIndex &that)
{
    if(this == &that)
        return *this;

    std::vector<Term> eraseTerms;

    Index::iterator thisTermIter = mIndex.begin();
    Index::const_iterator thatTermIter;
    Postings::iterator thisPostingsIter;
    Postings::iterator thisPostingsEnd;
    Postings::const_iterator thatPostingsIter;
    Postings::const_iterator thatPostingsEnd;
    for(; thisTermIter != mIndex.end(); ++thisTermIter)
    {
        thatTermIter = that.mIndex.find((*thisTermIter).first);
        if(thatTermIter != that.mIndex.end())
        {
            thisPostingsIter = (*thisTermIter).second.begin();
            thisPostingsEnd = (*thisTermIter).second.end();
            thatPostingsIter = (*thatTermIter).second.begin();
            thatPostingsEnd = (*thatTermIter).second.end();

            while(thisPostingsIter != thisPostingsEnd &&
                    thatPostingsIter != thatPostingsEnd)
            {
                if(*thisPostingsIter == *thatPostingsIter)
                {
                    ++thisPostingsIter;
                    ++thatPostingsIter;
                }
                else if(*thisPostingsIter < *thatPostingsIter)
                {
                    thisPostingsIter = (*thisTermIter).second.erase(
                            thisPostingsIter);
                }
                else
                {
                    ++thatPostingsIter;
                }
            }
            (*thisTermIter).second.erase(thisPostingsIter, thisPostingsEnd);

            if((*thisTermIter).second.size() == 0)
                eraseTerms.push_back((*thisTermIter).first);
        }
        else
        {
            eraseTerms.push_back((*thisTermIter).first);
        }
    }

    //TODO: optimize
    std::vector<Term>::const_iterator eraseIter = eraseTerms.begin();
    for(; eraseIter != eraseTerms.end(); ++eraseIter)
        mIndex.erase(*eraseIter);

    return *this;
}

void InvertedIndex::insert(const Term &term, DocId id)
{
    Index::iterator termIter = mIndex.find(term);
    if(termIter != mIndex.end())
    {
        Postings &postings = (*termIter).second;

        Postings::iterator postingsIter = postings.begin();
        for(; postingsIter != postings.end() &&
                id > *postingsIter; ++postingsIter);
        if(postingsIter == postings.end() || id != *postingsIter)
            postings.insert(postingsIter, id);
    }
    else
    {
        //TODO: check for better way
        Postings postings;
        postings.push_back(id);

        mIndex[term] = postings;
    }
}

const Postings &InvertedIndex::getPostings(const Term &term) const
{
    Index::const_iterator termIter = mIndex.find(term);
    if(termIter != mIndex.end())
        return (*termIter).second;
    return emptyPostings;
}

size_t InvertedIndex::getFrequency(const Term &term) const
{
    Index::const_iterator termIter = mIndex.find(term);
    if(termIter != mIndex.end())
        return (*termIter).second.size();
    return 0;
}

size_t InvertedIndex::getSize() const
{
    return mIndex.size();
}

void InvertedIndex::clear()
{
    mIndex.clear();
}

Postings operator&(const Postings &left, const Postings &right)
{
    Postings result;

    Postings::const_iterator leftPostingsIter = left.begin();
    Postings::const_iterator leftPostingsEnd = left.end();
    Postings::const_iterator rightPostingsIter = right.begin();
    Postings::const_iterator rightPostingsEnd = right.end();

    while(leftPostingsIter != leftPostingsEnd &&
            rightPostingsIter != rightPostingsEnd)
    {
        if(*leftPostingsIter == *rightPostingsIter)
        {
            result.push_back(*leftPostingsIter);

            ++leftPostingsIter;
            ++rightPostingsIter;
        }
        if(*leftPostingsIter < *rightPostingsIter)
        {
            ++leftPostingsIter;
        }
        else
        {
            ++rightPostingsIter;
        }
    }

    return result;
}

bool isContain(const Postings &postings, DocId id)
{
    Postings::const_iterator iter = postings.begin();
    for(; iter != postings.end() && id >= *iter; ++iter)
        if(id == *iter)
            return true;
    return false;
}

const Postings InvertedIndex::emptyPostings;

}
