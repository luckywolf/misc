/*
http://cs-technotes.blogspot.com/2010/12/lowest-common-ancestor-of-two-nodes-in_09.html?view=sidebar
find the lowest common ancestor of two nodes in a binary tree
In binary search tree, all values in the left subtree is samller than the node, and all values in the right subtree 
is larger than the node, so we can find the lowest common ancestor  in binary search tree by comparing the values.
The first node which has value between (a,b] is their lowest common ancestor.

However, in binary tree,there is no such characteristic. We need to search all paths from root to these two nodes.  There are two 
situation:
1) node a is in the left subtree of current node, and node b is in the right subtree of current node, obviously current node will 
the be lowest common ancestor
2) node a and node b are in the same side. If they are both in the left subtree, we could search the lowest common ancestor from 
the left node of current node; if they are both in the right subtree, we could search the lowest common ancestor from the right 
node of current node.
*/
//find the lowest common ancestor of a and b in a binary tree
BTNode* lowestCommonAncestorinBT(BTNode* root, int a, int b )
{
    if(root == NULL) {
        return NULL;
    }
    if(root->val == a || root->val == b) {
        return root;
    } else{
        BTNode* left = lowestCommonAncestorinBT(root->left, a, b);
        BTNode* right = lowestCommonAncestorinBT(root->right, a, b);
        if(left && right) { //one node is in the left and the other is in the right
            return root;
        } else { //both in left or both in right
            return left ? left : right; //if both in the left,return left
        }
    }
}
