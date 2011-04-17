#include "TreeBuilderParserInstance.h"

#include "Tree.h"

namespace search
{

TreeBuilderParserInstance::TreeBuilderParserInstance(const Grammar &grammar,
        const std::string &str)
    :ParserInstance(grammar, str)
{

}

TreeBuilderParserInstance::~TreeBuilderParserInstance()
{

}

void TreeBuilderParserInstance::processRewrite(size_t position, size_t ruleIndex)
{
}

}
