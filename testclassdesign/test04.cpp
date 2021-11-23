/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-09 14:47:26
 * @LastEditTime : 2021-08-09 15:25:42
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testclassdesign/test04.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */
#include <iostream>
#include <string>

class TreeNode
{
private:
    std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;

public:
    TreeNode() : value(""), count(0), left(nullptr), right(nullptr) {}
    TreeNode(std::string v, int c) : value(v), count(c), left(nullptr), right(nullptr) {}
    TreeNode(const TreeNode &treeNode) : value(treeNode.value), count(treeNode.count), left(&*treeNode.left), right(&*treeNode.right) {}
    TreeNode &operator=(const TreeNode &rhs)
    {
        value = rhs.value;
        count = rhs.count;
        auto newleft = new TreeNode(*rhs.left);
        delete left;
        left = newleft;
        auto newright = new TreeNode(*rhs.right);
        delete right;
        right = newright;
        return *this;
    }
    ~TreeNode()
    {
        if (left)
        {
            delete left;
            left = nullptr;
        }
        if (right)
        {
            delete right;
            right = nullptr;
        }
    }
    void print() const
    {
        std::cout << "value = " << value << ", count = " << count;
        // << ", left -> " << (left != nullptr ? *left : ) << ", right -> " << (right != nullptr ? *right : "");
    }
};

class BinStrTree
{
private:
    TreeNode *root;

public:
    BinStrTree() = default;
    BinStrTree(TreeNode &treeNode) : root(&treeNode) {}
    BinStrTree(const BinStrTree &binStrTree) : root(&*binStrTree.root) {}
    BinStrTree &operator=(const BinStrTree &rhs)
    {
        auto newroot = new TreeNode(*root);
        delete root;
        root = newroot;
        return *this;
    }
    ~BinStrTree()
    {
        if (root)
        {
            delete root;
            root = nullptr;
        }
    }
};

int main(int argc, char const *argv[])
{
    TreeNode NUL, A("a", 1);
    BinStrTree tree;
    A.print();

    return 0;
}
