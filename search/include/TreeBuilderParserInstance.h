#ifndef TREE_BUILDER_PARSER_INSTANCE_H
#define TREE_BUILDER_PARSER_INSTANCE_H

#include "ParserInstance.h"
#include "Tree.h"
#include "ParseNode.h"

namespace search
{

class TreeBuilderParserInstance: public ParserInstance
{
    typedef Tree<ParseNode> ParseTree;
public:
    TreeBuilderParserInstance(const Grammar &grammar, const std::string &str);
    virtual ~TreeBuilderParserInstance();

    //TODO: make const
    ParseTree &getParseTree();

private:
    virtual void rewrite();

    void rewrite(ParseTree::Iterator treeIter);

    State findState(const Symbol &head, size_t completePosition) const;

private:
    ParseTree mParseTree;
};

}

#endif//TREE_BUILDER_PARSER_INSTANCE_H
