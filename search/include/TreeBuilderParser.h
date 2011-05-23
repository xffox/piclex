#ifndef TREE_BUILDER_PARSER_H
#define TREE_BUILDER_PARSER_H

#include "Parser.h"
#include "Tree.h"
#include "ParseNode.h"

namespace search
{

class TreeBuilderParser: public Parser
{
    typedef Tree<ParseNode> ParseTree;
public:
    TreeBuilderParser();
    TreeBuilderParser(const Grammar &grammar);
    virtual ~TreeBuilderParser();

    //TODO: make const
    ParseTree &getParseTree();

private:
    virtual void rewrite();
    virtual void resetRewrite();

    void rewrite(ParseTree::Iterator treeIter);

    State findState(const Symbol &head, size_t completePosition) const;

private:
    ParseTree mParseTree;
};

}

#endif//TREE_BUILDER_PARSER_H
