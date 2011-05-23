#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <memory>

#include "TreeNode.h"
#include "TreeIterator.h"

namespace search
{
class TreeInternalError: public base::BaseException
{
};

//TODO: bush not tree?
//TODO: iterator belong check
//TODO: exception handling
//TODO: comparison
//TODO: copy 
template<class T>
class Tree
{
public:
    typedef TreeIterator<T> Iterator;

public:
    Tree();
    ~Tree();

    const TreeIterator<T> root();

    void insert(TreeIterator<T> &iter, const T &data);

    void appendChild(TreeIterator<T> &iter, const T &data);
    void insertChild(TreeIterator<T> &iter, const T &data,
            size_t childIndex);
    void insertChildsParent(TreeIterator<T> &iter, const T &data,
            size_t childIndex, size_t childsCount);

    void erase(TreeIterator<T> &iter);

    void clear();

private:

private:
    TreeNode<T> *mRoot;
};

template<class T>
Tree<T>::Tree()
    :mRoot(NULL)
{
}

template<class T>
Tree<T>::~Tree()
{
    if(mRoot)
        mRoot->deleteSubtree();
}

template<class T>
const TreeIterator<T> Tree<T>::root()
{
    return TreeIterator<T>(mRoot);
}

template<class T>
void Tree<T>::insert(TreeIterator<T> &iter, const T &data)
{
    TreeNode<T> *node = iter.getNode();
    TreeNode<T> *parent = iter.getParent();

    std::auto_ptr<TreeNode<T> > newNode(new TreeNode<T>(data));

    if(node)
    {
        newNode->appendChild(node);
    }

    if(parent)
    {
        newNode->setParent(parent);

        if(node)
        {
            size_t index = 0;
            try
            {
                index = parent->getChildIndex(node);
            }
            catch(base::NotFoundError &e)
            {
                throw TreeInternalError();
            }

            parent->removeChild(index);
            parent->insertChild(newNode.get(), index);
        }
        else
        {
            parent->appendChild(newNode.get());
        }
    }
    else
    {
        mRoot = newNode.get();
    }

    iter.setParent(newNode.release());
}

template<class T>
void Tree<T>::appendChild(TreeIterator<T> &iter, const T &data)
{
    if(iter.isEnd())
        throw BeyondEndError();

    TreeNode<T> *node = iter.getNode();
    assert(node);

    insertChild(iter, data, node->getChilds().size());
}

template<class T>
void Tree<T>::insertChild(TreeIterator<T> &iter, const T &data,
        size_t childIndex)
{
    if(iter.isEnd())
        throw BeyondEndError();

    TreeNode<T> *node = iter.getNode();
    assert(node);

    if(childIndex > node->getChilds().size())
        throw base::OutOfBoundError(childIndex, node->getChilds().size() + 1);

    std::auto_ptr<TreeNode<T> > newNode(new TreeNode<T>(data));

    newNode->setParent(node);
    node->insertChild(newNode.get(), childIndex);

    newNode.release();
}

template<class T>
void Tree<T>::insertChildsParent(TreeIterator<T> &iter, const T &data,
        size_t childIndex, size_t childsCount)
{
    if(iter.isEnd())
        throw BeyondEndError();

    TreeNode<T> *node = iter.getNode();
    assert(node);

    if(childIndex >= node->getChilds().size() ||
            childIndex + childsCount > node->getChilds().size())
        throw base::OutOfBoundError(std::max(childIndex,
                    node->getChilds().size()), node->getChilds().size());

    typename TreeNode<T>::Nodes childs(node->getChilds().begin() + childIndex,
            node->getChilds().begin() + childIndex + childsCount);

    std::auto_ptr<TreeNode<T> > newNode(new TreeNode<T>(data));

    newNode->setParent(node);
    newNode->appendChilds(childs);
    node->removeChilds(childIndex, childsCount);
    node->insertChild(newNode.get(), childIndex);

    newNode.release();
}

template<class T>
void Tree<T>::erase(TreeIterator<T> &iter)
{
    if(iter.isEnd())
        throw BeyondEndError();

    TreeNode<T> *node = iter.getNode();
    assert(node);
    TreeNode<T> *parent = iter.getParent();

    if(parent != NULL)
    {
        size_t index = 0;
        try
        {
            index = parent->getChildIndex(node);
        }
        catch(base::NotFoundError &e)
        {
            throw TreeInternalError();
        }

        parent->removeChild(index);

        typename TreeNode<T>::Nodes childs(node->getChilds().begin(),
                node->getChilds().end());
        parent->insertChilds(childs, index);

        iter.setNode(parent);
        iter.setParent(parent->getParent());
    }
    else
    {
        if(node->getChilds().size() == 1)
        {
            mRoot = node->getChilds()[0];
        }
        else if(node->getChilds().size() == 0)
        {
            mRoot = NULL;
        }
        else
        {
            //TODO: fix exception
            throw BeyondEndError();
        }

        iter.setNode(mRoot);
        iter.setParent(NULL);
    }

    delete node;
}

template<class T>
void Tree<T>::clear()
{
    if(mRoot)
    {
        mRoot->deleteSubtree();
        mRoot = NULL;
    }
}

}

#endif//TREE_H
