#include "SearcherFactory.h"

#include "SimpleSearcher.h"

namespace gui
{
Searcher *createSearcher()
{
    return new SimpleSearcher;
}
}
