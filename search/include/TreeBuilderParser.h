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
    State findState(const Symbol &head, size_t originPosition,
            size_t completePosition) const;

    template<class Predicate>
    State findState(Predicate pred) const;

private:
    ParseTree mParseTree;
};

template<class Predicate>
Parser::State TreeBuilderParser::findState(Predicate pred) const
{
    std::vector<States>::const_iterator statesQueueIter = 
        getStatesQueue().begin();
    States::const_iterator statesIter;
    for(; statesQueueIter != getStatesQueue().end(); ++statesQueueIter)
        for(statesIter = statesQueueIter->begin();
                statesIter != statesQueueIter->end(); ++statesIter)
            if(pred(*statesIter))
                return *statesIter;
    throw base::NotFoundError();
}

}

#endif//TREE_BUILDER_PARSER_H
