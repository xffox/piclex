#include "TreeBuilderParser.h"

#include "Tree.h"

namespace search
{
TreeBuilderParser::TreeBuilderParser()
{
}

TreeBuilderParser::TreeBuilderParser(const Grammar &grammar)
    :Parser(grammar)
{
}

TreeBuilderParser::~TreeBuilderParser()
{

}

TreeBuilderParser::ParseTree &TreeBuilderParser::
        getParseTree()
{
    return mParseTree;
}

void TreeBuilderParser::rewrite()
{
    mParseTree.clear();

    ParseTree::Iterator treeIter = mParseTree.root();
    mParseTree.insert( treeIter, ParseNode(getGrammar().getStartSymbol(),
                0, getStr().size()) );
    treeIter.up();

    rewrite(treeIter);
}

void TreeBuilderParser::resetRewrite()
{
    mParseTree.clear();
}

void TreeBuilderParser::rewrite(ParseTree::Iterator treeIter)
{
    if((*treeIter).getSymbol().isTerminal())
        return;

    State state = findState((*treeIter).getSymbol(),
            (*treeIter).getBeginPosition() + (*treeIter).getSize());
    size_t position = state.getCompletePosition();
    const Rule &rule = state.getRule();
    size_t rulePosition = rule.getBodyLength();
    ParseTree::Iterator downTreeIter;
    while(rulePosition > 0)
    {
        assert(position >= state.getOriginPosition());

        if(rule.getBody(rulePosition-1).isNonterminal())
        {
            State childState = findState(rule.getBody(rulePosition-1),
                    position);
            mParseTree.insertChild(treeIter, ParseNode(childState.getHead(),
                        childState.getOriginPosition(),
                        childState.getCompletePosition() -
                        childState.getOriginPosition()), 0);

            position = childState.getOriginPosition();

            downTreeIter = treeIter;
            downTreeIter.down(0);
            rewrite(downTreeIter);
        }
        else
        {
            --position;
        }

        --rulePosition;
    }
}

Parser::State TreeBuilderParser::findState(const Symbol &head,
        size_t completePosition) const
{
    std::vector<States>::const_iterator statesQueueIter = 
        getStatesQueue().begin();
    States::const_iterator statesIter;
    for(; statesQueueIter != getStatesQueue().end(); ++statesQueueIter)
        for(statesIter = statesQueueIter->begin();
                statesIter != statesQueueIter->end(); ++statesIter)
            if(statesIter->getHead() == head &&
                    statesIter->getCompletePosition() == completePosition)
                return *statesIter;
    throw base::NotFoundError();
}

}