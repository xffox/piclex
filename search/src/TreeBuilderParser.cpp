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
            (*treeIter).getBeginPosition(),
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

class CompareHeadAndCompletePos
{
public:
    CompareHeadAndCompletePos(const Symbol &head, size_t completePosition)
        :mHead(head), mCompletePosition(completePosition)
    {
    }

    bool operator()(const Parser::State &state) const
    {
        return state.getHead() == mHead &&
            state.getCompletePosition() == mCompletePosition;
    }

private:
    Symbol mHead;
    size_t mCompletePosition;
};

Parser::State TreeBuilderParser::findState(const Symbol &head,
        size_t completePosition) const
{
    return findState(CompareHeadAndCompletePos(head, completePosition));
}

class CompareHeadAndOriginPosAndCompletePos
{
public:
    CompareHeadAndOriginPosAndCompletePos(const Symbol &head,
            size_t originPosition, size_t completePosition)
        :mHead(head), mOriginPosition(originPosition)
        ,mCompletePosition(completePosition)
    {
    }

    bool operator()(const Parser::State &state) const
    {
        return state.getHead() == mHead &&
            state.getOriginPosition() == mOriginPosition &&
            state.getCompletePosition() == mCompletePosition;
    }

private:
    Symbol mHead;
    size_t mOriginPosition;
    size_t mCompletePosition;
};

Parser::State TreeBuilderParser::findState(const Symbol &head,
        size_t originPosition, size_t completePosition) const
{
    return findState(CompareHeadAndOriginPosAndCompletePos(head,
                originPosition, completePosition));
}

}
