#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include "TreeNode.h"
#include "BaseExceptions.h"
#include "TreeVisitor.h"

namespace search
{
class BeyondEndError: public base::BaseException
{
};

template<class T>
class Tree;

//TODO: fix friends
template<class T>
class TreeIterator
{
    friend class Tree<T>;
public:
    TreeIterator();

    void down(size_t childIndex);
    void up();

    size_t getChildsCount() const;

    bool isEnd() const;
    bool isRoot() const;

    T &operator*();
    const T &operator*() const;

    void accept(TreeVisitor<T> *visitor) const;

private:
    TreeIterator(TreeNode<T> *node);

    void changeNode(TreeNode<T> *node);

    TreeNode<T> *getParent();
    void setParent(TreeNode<T> *parent);

    TreeNode<T> *getNode();
    void setNode(TreeNode<T> *node);

private:
    TreeNode<T> *mNode;
    TreeNode<T> *mParent;
};

template<class T>
TreeIterator<T>::TreeIterator()
    :mNode(NULL), mParent(NULL)
{
}

template<class T>
TreeIterator<T>::TreeIterator(TreeNode<T> *node)
    :mNode(node), mParent(node?node->getParent():NULL)
{
}

template<class T>
void TreeIterator<T>::down(size_t childIndex)
{
    if(mNode == NULL)
        throw BeyondEndError();

    mParent = mNode;

    if(childIndex < mNode->getChilds().size())
        mNode = mNode->getChilds()[childIndex];
    else
        mNode = NULL;
}

template<class T>
void TreeIterator<T>::up()
{
    if(mParent == NULL)
        throw BeyondEndError();

    mNode = mParent;
    mParent = mNode->getParent();
}

template<class T>
size_t TreeIterator<T>::getChildsCount() const
{
    if(isEnd())
        throw BeyondEndError();
    return mNode->getChilds().size();
}

template<class T>
bool TreeIterator<T>::isEnd() const
{
    return mNode == NULL;
}

template<class T>
bool TreeIterator<T>::isRoot() const
{
    return mParent == NULL;
}

template<class T>
T &TreeIterator<T>::operator*()
{
    if(isEnd())
        throw BeyondEndError();
    return mNode->getData();
}

template<class T>
const T &TreeIterator<T>::operator*() const
{
    return const_cast<TreeIterator*>(this)->operator*();
}

template<class T>
void TreeIterator<T>::accept(TreeVisitor<T> *visitor) const
{
    if(!visitor)
        throw base::InvalidArgument();

    if(mNode)
    {
        visitor->visit(*this);

        TreeIterator<T> treeIterator;

        const typename TreeNode<T>::Nodes &childs = mNode->getChilds();
        typename TreeNode<T>::Nodes::const_iterator childIter = childs.begin();
        for(; childIter != childs.end(); ++childIter)
        {
            treeIterator.changeNode(*childIter);
            treeIterator.accept(visitor);
        }
    }
}

template<class T>
void TreeIterator<T>::changeNode(TreeNode<T> *node)
{
    mNode = node;
    mParent = node?node->getParent():NULL;
}

template<class T>
TreeNode<T> *TreeIterator<T>::getParent()
{
    return mParent;
}

template<class T>
void TreeIterator<T>::setParent(TreeNode<T> *parent)
{
    mParent = parent;
}

template<class T>
TreeNode<T> *TreeIterator<T>::getNode()
{
    return mNode;
}

template<class T>
void TreeIterator<T>::setNode(TreeNode<T> *node)
{
    mNode = node;
}

}

#endif//TREE_ITERATOR_H
