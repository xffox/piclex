#include "IndexToken.h"

namespace search
{
IndexToken::IndexToken(DocId docId, const Term &term)
    :mDocId(docId), mTerm(term)
{
}

DocId IndexToken::getDocId() const
{
    return mDocId;
}

const Term &IndexToken::getTerm() const
{
    return mTerm;
}

}
