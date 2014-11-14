/*
Find the second max in BST.

http://stackoverflow.com/questions/11425352/second-max-in-bst
*/

struct TreeNode{
    int val;
    TreeNode *left, *right, *parent;
    TreeNode(int x = -1): val(x), left(NULL), right(NULL), parent(NULL) {}
};

TreeNode *findRightmostNode(TreeNode *&root) {
    TreeNode *res = root;
    while (res->right != NULL) {
        res = res->right;
    }
    return res;
}

/*
Recursively, and use parent pointer
*/
TreeNode *findSecondMaxInBST(TreeNode *root) {
    if (root->right != NULL) {
        // The check above establishes that the rightmost node has a parent
        return findRightmostNode(root->right)->parent;
    else if (root->left != NULL) {
        // Root is the rightmost node; find the largest node among the remaining ones
        return findRightmostNode(root->left)
    } else {
        // The tree has only a root and no other nodes
        return NULL
    }
}

/*
Iteratively, without parent pointer
*/
TreeNode *findSecondMaxInBST_2(TreeNode *root) {
    TreeNode *res = NULL;
    TreeNode *par = NULL;
    TreeNode *cur = root;
    while (cur->right != NULL) {
        par = cur;
        cur = cur->right;
    }
    if (cur->left != NULL) {
        cur = cur->left;
        while (cur->right != NULL) {
            cur = cur->right;
        }
        secondMax = cur;
    } else if (par != NULL) {
        secondMax = par; // BST has at least two nodes
    }
    return secondMax;
}
