#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <vector>

namespace search
{

template<class T>
class TreeNode
{
public:
    ~TreeNode();

public:
    T mData;
    std::vector<TreeNode<T>*> mChilds;
};

template<class T>
TreeNode<T>::~TreeNode()
{
    while(mChilds.size())
    {
        delete mChilds.back();
        mChilds.pop_back();
    }
}

}

#endif//TREE_NODE_H
