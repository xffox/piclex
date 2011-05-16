#include "SearchEngineFactory.h"

#if 0
#include "SimpleSearchEngine.h"
#endif
#include "MockSearchEngine.h"

namespace gui
{
SearchEngine *createSearchEngine()
{
    return new MockSearchEngine;
}
}
