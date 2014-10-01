/*
http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
http://leetcode.com/2010/09/serializationdeserialization-of-binary.html
*/

#include <iostream>
#include <fstream>
using namespace std;

struct TreeNode {
    string val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string x) : val(x), left(NULL), right(NULL) {}
};

// void serialize(ofstream& outfile, TreeNode* current)
// {
    // if(current == NULL)
    // {
        // outfile << '#';
        // return;
    // }
    // outfile << current->val;
    // serialize(outfile, current->left);
    // serialize(outfile, current->right);
// }

// void deserialize(ifstream& infile, TreeNode*& current)
// {
    // char ch;
    // infile >> ch;
    // if(ch == '#')
        // return;
    // current = new TreeNode(int(ch));
    // deserialize(infile, current->left);
    // deserialize(infile, current->right);
// }

void serialize(vector<string> &strs, TreeNode* root) {
    if (root == NULL) {
        str.push_back("#");
        return;
    }
    strs.push_back(root->val);
    serialize(strs, root->left);
    serialize(strs, root->right);
}

TreeNode *deserialize(vector<string> &strs, int index) {
    // the last token should be "#", so we don't need to check index < strs.size()
    string token =  strs[index++];
    if( token == "#") { 
        return NULL;
    }
    TreeNode *res = new TreeNode(token);
    res->left = deserialize(strs, index);
    res->right = deserialize(strs, index);
    return res;
}
