#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <vector>
#include <cassert>

#include "BaseExceptions.h"

namespace search
{

template<class T>
class TreeNode
{
public:
    typedef std::vector<TreeNode<T>*> Nodes;

public:
    TreeNode(const T &data);
    ~TreeNode();

    T &getData();
    const T &getData() const;

    TreeNode<T> *getParent();
    const TreeNode<T> *getParent() const;

    void setParent(TreeNode<T> *parent);

    void deleteSubtree();

    void appendChild(TreeNode<T> *child);
    void appendChilds(const Nodes &childs);
    void insertChild(TreeNode<T> *child, size_t childIndex);
    void insertChilds(const Nodes &childs, size_t childIndex);

    void removeChild(size_t childIndex);
    void removeChilds(size_t childIndex, size_t childsCount);

    const Nodes &getChilds() const;

    size_t getChildIndex(const TreeNode<T> *child);

private:
    T mData;

    TreeNode<T> *mParent;
    Nodes mChilds;
};

template<class T>
TreeNode<T>::TreeNode(const T &data)
    :mData(data), mParent(NULL)
{
}

template<class T>
TreeNode<T>::~TreeNode()
{
}

template<class T>
T &TreeNode<T>::getData()
{
    return mData;
}

template<class T>
TreeNode<T> *TreeNode<T>::getParent()
{
    return mParent;
}

template<class T>
const TreeNode<T> *TreeNode<T>::getParent() const
{
    return const_cast<TreeNode<T>*>(this)->getParent();
}

template<class T>
void TreeNode<T>::setParent(TreeNode<T> *parent)
{
    mParent = parent;
}

template<class T>
const T &TreeNode<T>::getData() const
{
    return const_cast<TreeNode<T>*>(this)->getData();
}

template<class T>
void TreeNode<T>::deleteSubtree()
{ 
    TreeNode<T> *node = NULL;
    while(mChilds.size())
    {
        node = mChilds.back();
        assert(node);
        node->deleteSubtree();

        mChilds.pop_back();
    }

    delete this;
}

template<class T>
void TreeNode<T>::appendChild(TreeNode<T> *child)
{
    insertChild(child, mChilds.size());
}

template<class T>
void TreeNode<T>::appendChilds(const Nodes &childs)
{
    insertChilds(childs, mChilds.size());
}

template<class T>
void TreeNode<T>::insertChild(TreeNode<T> *child, size_t childIndex)
{
    if(child == NULL)
        throw base::InvalidArgument();

    if(childIndex > mChilds.size())
        throw base::OutOfBoundError(childIndex, mChilds.size() + 1);

    mChilds.insert(mChilds.begin() + childIndex, child);
}

template<class T>
void TreeNode<T>::insertChilds(const Nodes &childs, size_t childIndex)
{
    if(childIndex > mChilds.size())
        throw base::OutOfBoundError(childIndex, mChilds.size() + 1);

    mChilds.insert(mChilds.begin() + childIndex, childs.begin(), childs.end());
}

template<class T>
void TreeNode<T>::removeChild(size_t childIndex)
{
    removeChilds(childIndex, 1);
}

template<class T>
void TreeNode<T>::removeChilds(size_t childIndex, size_t childsCount)
{
    if(childIndex >= mChilds.size() || childIndex + childsCount > mChilds.size())
        throw base::OutOfBoundError(std::max(childIndex, mChilds.size()),
                    mChilds.size());

    mChilds.erase(mChilds.begin() + childIndex, mChilds.begin() + childIndex + childsCount);
}

template<class T>
const typename TreeNode<T>::Nodes &TreeNode<T>::getChilds() const
{
    return mChilds;
}

template<class T>
size_t TreeNode<T>::getChildIndex(const TreeNode<T> *child)
{
    if(child == NULL)
        throw base::InvalidArgument();

    typename Nodes::const_iterator iter = mChilds.begin();
    for(; iter != mChilds.end(); ++iter)
        if(*iter == child)
            return iter - mChilds.begin();

    throw base::NotFoundError();
}

}

#endif//TREE_NODE_H
