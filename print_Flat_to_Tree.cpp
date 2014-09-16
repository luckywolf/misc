/*
http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
http://leetcode.com/2010/09/serializationdeserialization-of-binary.html
*/

#include <iostream>
#include <fstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode * parent;
    TreeNode(int x, TreeNode) : val(x){}
};

void readFile(unordered_map<int, TreeNode *> &lookup, ifstream &fin)
{   
    pair<int, int> token;
    readNextLine(token, fin);
    int empVal = token->first;
    int mgrVal = token->second;
    TreeNode *empTreeNode, *mgrTreeNode;
    if (lookup.find(mgrVal) != lookup.end()) {
        mgrTreeNode = lookup[mgrVal];
    } else {
        mgrTreeNode = new TreeNode(mgrVal);
        lookup[mgrVal] = mgrTreeNode;
    }
    if (lookup.find(empVal) != lookup.end()) {
        empTreeNode = lookup[empVal];
    } else {
        empTreeNode = new TreeNode(empVal);
        lookup[empVal] = empTreeNode;
    }
    empTreeNode->parent = mgrTreeNode;
    mgrTreeNode->children.push_back(empTreeNode);
}

void findRoot(unordered_map<int, TreeNode *> &lookup, vector<TreeNode *> &rootVec) {
    for (unordered_map<int, TreeNode *>::iterator it = lookup.begin(); it != lookup.end(); ++it) {
        if (it->second->parent == NULL) {
            rootVec->push_back(it->second);
    }
}

void printTreeRe(TreeNode* root, level) {
    string padding(level, '\t');
    if (root) {
        cout << padding << root->val << endl;
    }
    for (int i = 0; i < root->children.size(); i++) {
        printTreeRe(root->children[i], level + 1);
    }
}

