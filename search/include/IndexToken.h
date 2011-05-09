#ifndef INDEX_TOKEN_H
#define INDEX_TOKEN_H

#include "SearchDefines.h"

namespace search
{
class IndexToken
{
public:
    IndexToken(DocId docId, const Term &term);

    DocId getDocId() const;
    const Term &getTerm() const;

private:
    DocId mDocId;
    Term mTerm;
};
}

#endif//INDEX_TOKEN_H
