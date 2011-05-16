#ifndef INDEX_MAKE_H
#define INDEX_MAKE_H

#include <vector>

#include "SearchDefines.h"
#include "InvertedIndex.h"

namespace search
{
class IndexToken;
class DocIdReader;
class DocProcessor;

class IndexMaker
{
public:
    IndexMaker(const DocIdReader *docIdReader,
            const DocProcessor *docProcessor);
    virtual ~IndexMaker();

    void index(const std::vector<DocId> &docIds); 

    const InvertedIndex &getIndex() const;

protected:
    const DocIdReader *getDocIdReader() const;
    const DocProcessor *getDocProcessor() const;

private:
    //TODO: use set instead of vector
    virtual void tokenize(std::vector<IndexToken> &tokens,
            const std::vector<DocId> &docIds) = 0;
    virtual void makeIndex(InvertedIndex &index,
            const std::vector<IndexToken> &tokens) = 0;

private:
    InvertedIndex mIndex;

    const DocIdReader *mDocIdReader;
    const DocProcessor *mDocProcessor;
};

}

#endif//INDEX_MAKE_H
