#ifndef TREE_VISITOR_H
#define TREE_VISITOR_H

namespace search
{
template<class T>
class TreeIterator;

template<class T>
class TreeVisitor
{
public:
    virtual ~TreeVisitor(){}

    virtual void visit(const TreeIterator<T> &iterator) = 0;
};

}

#endif//TREE_VISITOR_H
