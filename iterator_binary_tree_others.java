/*
https://github.com/luckywolf/misc/blob/master/tree_serialization.cpp
Write an iterator for binary tree. 
*/

struct NODE {
    int val;
    NODE* pLft;
    NODE* pRgt;
 
    NODE(int n) : val(n), pLft(NULL), pRgt(NULL) {}
};

/*
Here is the inorder iterator.
*/

class BinaryTreeIterator {

public:
    void iterconstruct(NODE* root) { 
       buildIter(root);
     
    }
 
    NODE *Next() {
        if (stk.empty()) return NULL;
 
        NODE* ret = stk.top();
        stk.pop();
 
        BuildIter(ret->pRgt);
 
        return ret;
    }
 
private:
    void buildIter(NODE* node) {
        while (node != NULL) {
        
            stk.push(node);
            node = node->pLft;
        }
    }

    stack<NODE*> stk;
   
};

/*
http://n00tc0d3r.blogspot.com/2013/08/implement-iterator-for-binarytree-iii.html?view=flipcard


Implement Post-order Iterator for Binary Tree

Suppose the data structure for a Tree node is as follows:
*/
public class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}
Provide an implementation of the following interface: 
public interface PostOrderBinaryTreeIterator extends Iterator<Integer> { 
  /** Returns the next integer a in the post-order traversal of the given binary tree.
   * For example, given a binary tree below,
   *       4
   *      / \
   *     2   6
   *    / \ / \
   *   1  3 5  7
   * the outputs will be 1, 3, 2, 5, 7, 6, 4. 
   */ 
  public Integer next(); 

  /** Return true if traversal has not finished; otherwise, return false. */ 
  public boolean hasNext();
}
/*
Solution

A straightforward way is, as we discussed in previous post, to traverse the tree with mirrorred pre-order, i.e. root-right-left, and store all of them in a stack. Then next() just need to pop nodes out from the stack.

By doing that, it requires O(n) extra spaces since pre-process stores all nodes in the tree.

Alternatively, we can do it on the fly somehow.
Initially, we find the first leaf that is going to be visited first and store all intermediate nodes in a stack;
Each time we pop out a node from the stack, we check whether it is the left child of the current top of the stack. If so, repeat the step above on the right sub-tree of the current top.
We only need to check whether current is left of top since if it is right, we know top will be the next-to-be-popped node and thus no need to do anything.
*/
 public class PostOrderBinaryTreeIteratorImpl implements PostOrderBinaryTreeIterator {  
   Stack<TreeNode> stack = new Stack<TreeNode>();  
   
   /** find the first leaf in a tree rooted at cur and store intermediate nodes */  
   private void findNextLeaf(TreeNode cur) {  
     while (cur != null) {  
       stack.push(cur);  
       if (cur.left != null) {  
         cur = cur.left;  
       } else {  
         cur = cur.right;  
       }  
     }  
   }  
   
   /** Constructor */  
   public PostOrderBinaryTreeIterator(TreeNode root) {  
     findNextLeaf(root);  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public boolean hasNext() {  
     return !stack.isEmpty();  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public Integer next() {  
     if (!hasNext()) {  
       throw new NoSuchElementException("All nodes have been visited!");  
     }  
   
     TreeNode res = stack.pop();  
     if (!stack.isEmpty()) {  
       TreeNode top = stack.peek();  
       if (res == top.left) {  
         findNextLeaf(top.right); // find next leaf in right sub-tree 
       }  
     }  
   
     return res.val;  
   }  
   
   @Override  
   public void remove() {  
     throw new UnsupportedOperationException("remove() is not supported.");  
   }  
 }  

/* 
This iterator takes extra spaces for the queue, which is O(h) at worst case, where h is the height of the tree.

With this iterator in hand, an post-order traversal of a binary tree can be implemented as follows.
 public ArrayList<Integer> postorderTraversal(TreeNode root) {  
   PostOrderBinaryTreeIterator iterator = new PostOrderBinaryTreeIteratorImpl(root);  
   ArrayList<Integer> results = new ArrayList<Integer>();  
   while (iterator.hasNext()) {  
     results.add(iterator.next());  
   }  
   return results;  
 }
*/
 
/*
 http://n00tc0d3r.blogspot.com/2013/07/big-data-count-occurrences.html?view=flipcard
 
 Implement Pre-order Iterator for Binary Tree

Suppose the data structure for a Tree node is as follows:
*/
public class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}
Provide an implementation of the following interface: 
public interface PreOrderBinaryTreeIterator extends Iterator<Integer> { 
  /** Returns the next integer a in the pre-order traversal of the given binary tree.
   * For example, given a binary tree below,
   *       4
   *      / \
   *     2   6
   *    / \ / \
   *   1  3 5  7
   * the outputs will be 4, 2, 1, 3, 6, 5, 7. 
   */ 
  public Integer next(); 

  /** Return true if traversal has not finished; otherwise, return false.
   */ 
  public boolean hasNext();
}

/*
Solution

The idea is slightly different from we discussed in previous post.

In previous post, we visit left nodes on the way to get to the left-most one. But in an iterator, given a top node in the stack, it is not easy to tell whether the left node of the top one has been visited or not. We can make it work by adding flags. But there are a better way to do that.

The reason why we need to keep previous nodes is that when we complete the left sub-tree, we can go to the right sub-tree. That said, what we actually need to keep track are right nodes.

We can use Stack and handle the process more naturally. Each time when we visit a node, we push its right and left children into the stack so that we can access left subtree first and then right subtree. More specifically, we use ArrayDeque which a "resizable-array implementation of the Deque interface". It provides amortized constant time operations such as add, poll, push, and pop, etc.
*/

 public class PreOrderBinaryTreeIteratorImpl implements PreOrderBinaryTreeIterator {  
   Stack<TreeNode> stack = new ArrayDeque<TreeNode>();  
   
   /** Constructor */  
   public PreOrderBinaryTreeIterator(TreeNode root) {  
     if (root != null) {  
       stack.push(root); // add to end of queue 
     }  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public boolean hasNext() {  
     return !stack.isEmpty();  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public Integer next() {  
     if (!hasNext()) {  
       throw new NoSuchElementException("All nodes have been visited!");  
     }  
   
     TreeNode res = stack.pop(); // retrieve and remove the head of queue 
     if (res.right != null) stack.push(res.right);  
     if (res.left != null) stack.push(res.left);  
   
     return res.val;  
   }  
   
   @Override  
   public void remove() {  
     throw new UnsupportedOperationException("remove() is not supported.");  
   }  
 }  

/* 
This iterator takes extra spaces for the stack, which is O(h) at worst case, where h is the height of the tree.

With this iterator in hand, an pre-order traversal of a binary tree can be implemented as follows.
 public ArrayList<Integer> preorderTraversal(TreeNode root) {  
   PreOrderBinaryTreeIterator iterator = new PreOrderBinaryTreeIteratorImpl(root);  
   ArrayList<Integer> results = new ArrayList<Integer>();  
   while (iterator.hasNext()) {  
     results.add(iterator.next());  
   }  
   return results;  
 }
 */
 
/*
http://n00tc0d3r.blogspot.com/2013/07/big-data-count-occurrences.html?view=flipcard 
Implement In-order Iterator for Binary Tree

Suppose the data structure for a Tree node is as follows:
*/
public class TreeNode {
  int val;
  TreeNode left;
  TreeNode right;
  TreeNode(int x) { val = x; }
}
Provide an implementation of the following interface: 
public interface InOrderBinaryTreeIterator extends Iterator<Integer> { 
  /** Returns the next integer a in the in-order traversal of the given binary tree.
   * For example, given a binary tree below,
   *       4
   *      / \
   *     2   6
   *    / \ / \
   *   1  3 5  7
   * the outputs will be 1, 2, 3, 4, 5, 6, 7. 
   */ 
  public Integer next(); 

  /** Return true if traversal has not finished; otherwise, return false.
   */ 
  public boolean hasNext();
}
/*
Solution

The idea is still the same as we discussed in previous post):
Find the left-most node of the root and store previous left children in a stack;
Pop up the top node from the stack;
If it has a right child, find the lef-most node of the right child and store left children in the stack.
*/
 public class InOrderBinaryTreeIteratorImpl implements InOrderBinaryTreeIterator {  
   Stack<TreeNode> stack = new Stack<TreeNode>();  
   
   /** Push node cur and all of its left children into stack */  
   private void pushLeftChildren(TreeNode cur) {  
     while (cur != null) {  
       stack.push(cur);  
       cur = cur.left;  
     }  
   }  
   
   /** Constructor */  
   public InOrderBinaryTreeIterator(TreeNode root) {  
     pushLeftChildren(root);  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public boolean hasNext() {  
     return !stack.isEmpty();  
   }  
   
   /** {@inheritDoc} */  
   @Override  
   public Integer next() {  
     if (!hasNext()) {  
       throw new NoSuchElementException("All nodes have been visited!");  
     }  
   
     TreeNode res = stack.pop();  
     pushLeftChildren(res.right);  
   
     return res.val;  
   }  
   
   @Override  
   public void remove() {  
     throw new UnsupportedOperationException("remove() is not supported.");  
   }  
 }  
/*
This iterator takes extra spaces for the stack, which is O(h) at worst case, where h is the height of the tree.

With this iterator in hand, an in-order traversal of a binary tree can be implemented as follows.
 public ArrayList<Integer> inorderTraversal(TreeNode root) {  
   InOrderBinaryTreeIterator iterator = new InOrderBinaryTreeIteratorImpl(root); 
   ArrayList<Integer> results = new ArrayList<Integer>();
   while (iterator.hasNext()) {   
     results.add(iterator.next());  
   }   
   return results;    
 }
*/
 
 
 
