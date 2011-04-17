#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

//TODO: iterator?

namespace search
{

//TODO: bush not tree?
template<class T>
class Tree
{
public:
    Tree();
    ~Tree();

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
    delete mRoot;
}

}

#endif//TREE_H
