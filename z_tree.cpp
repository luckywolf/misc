/*
http://yoshiyukiaoyagi.wordpress.com/2012/06/23/trinary-tree-in-java/
*/

package TrinaryTree;

public class TrinaryTree {

    //Main function
  public static void main(String[] args)
  {
      //Sample tree values rooted at 5
      int Values[] = {5, 4, 9, 5, 7, 2, 2};

      //Create Tree
      TrinaryTree tree = new TrinaryTree();

      //Populate tree
      tree.Populate(Values, 7);

  }

  //Define a tree node
  static class Node
  {
      //Left is less than node value
      Node left;
      //Middle is equal to node value
      Node middle;
      //Right is greater than node value
      Node right;

      //Node value
      int value;

      //Constructor
      public Node(int value)
      {
          this.value = value;
      }
  }

  //Populate method: receives an
  //array of integers along with
  //its size (n)
  public void Populate(int A[], int n)
  {
      //Tree rooted at the first
      //element of the array
      Node root = new Node(A[0]);

      //Insert values into the tree
      for (int i = 1; i < n; i++)
      {
          Insert(root, A[i]);
      }

      //Print tree
      Print(root);

  }

  //Insert a node into the tree
  public void Insert(Node node, int value)
  {
      //If the value to be inserted
      //is less than node value then
      //we either inserts it as the
      //left child if it does not exist
      //or recursively call the insert
      //on the left child if it does exist
      if (value < node.value)
      {
          //Left child exist
          if (node.left != null)
          {
              Insert(node.left, value);
          }
          //Left child does not exist
          //so create it
          else
          {
              node.left = new Node(value);
          }
      }
      //Same reasoning as above but for right
      else if (value > node.value)
      {
          if (node.right != null)
          {
              Insert(node.right, value);
          }
          else
          {
              node.right = new Node(value);
          }
      }
      //Same reasoning as above but for middle
      else
      {
          if (node.middle != null)
          {
              Insert(node.middle, value);
          }
          else
          {
              node.middle = new Node(value);
          }
      }
  }

  public Node Delete(Node node, int value)
  {
      if (node.value > value)
      {
          node.left = Delete(node.left, value);
      }
      else if(node.value < value)
      {
          node.right = Delete(node.right, value);
      }
      else
      {
          if (node.middle != null)
          {
              node.middle = Delete(node.middle, value);
          }
          else if(node.right != null)
          {
              int min = minimum(node.right).value;
              node.value = min;
              node.right = Delete(node.right, min);
          }
          else
          {
              node = node.left;
          }
      }
      return node;
  }

  protected Node minimum(Node node)
  {
      if(node != null)
      {
          while (node.left != null)
          {
              return minimum(node.left);
          }
      }

      return node;
  }

  //Recursive method to print the
  //whole tree
  public void Print(Node root)
  {
      if (root != null)
      {
          System.out.println("Node value : " + root.value);
          Print(root.left);
          Print(root.middle);
          Print(root.right);
      }
  }
}

/*
http://code.activestate.com/recipes/578825-tri-nary-tree-insertion-and-deletion/?in=lang-cpp
*/

/*
 *
 * Implement insert and delete in a tri-nary tree
 *
 */


#include <iostream>

// data structure of Tri-Nary tree node
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *middle;
  TreeNode *right;
  TreeNode(int value):
    val(value), left(NULL), middle(NULL), right(NULL) {}
};

// data structure of Tri-Nary tree
class Tri_Nary_Tree {
  private:
    TreeNode *root;
    void insertNode(TreeNode *node, int value);
    TreeNode* deleteNode(TreeNode *node, int value);
    TreeNode* findSuccessor(TreeNode *node);
  public:
    Tri_Nary_Tree():root(NULL) {}
    void insertNode(int value);
    void deleteNode(int value);
};

void Tri_Nary_Tree::insertNode(int value) {
  if (root == NULL)
    root = new TreeNode(value);
  else
    insertNode(root, value);
}

void Tri_Nary_Tree::insertNode(TreeNode *node, int value) {
  if (node->val < value) {
    if (node->right)
      insertNode(node->right, value);
    else
      node->right = new TreeNode(value);
  }
  else if (node->val > value) {
    if (node->left)
      insertNode(node->left, value);
    else
      node->left = new TreeNode(value);
  }
  else {
    if (node->middle)
      insertNode(node->middle, value);
    else
      node->middle = new TreeNode(value);
  }
}

inline void Tri_Nary_Tree::deleteNode(int value) {
  root = deleteNode(root, value);
}

TreeNode* Tri_Nary_Tree::deleteNode(TreeNode *node, int value) {

  if (node == NULL)
    return node;

  if (node->val == value) {
    // three child nodes are all NULL
    if (node->left == NULL && node->right == NULL && node->middle == NULL) {
      delete node;
      return NULL;
    }
    if (node->middle) {
      node->middle = deleteNode(node->middle, value);
    }
    else {
      if (node->left && node->right) {  // both left and right exist
        TreeNode *successor_node = findSuccessor(node->right);
        node->val = successor_node->val;
        node->right = deleteNode(node->right, successor_node->val);
      }
      else if (node->left) {    // right child is empty
        TreeNode *new_node = node->left;
        delete node;
        return new_node;
      }
      else {                   // left child is empty
        TreeNode *new_node = node->right;
        delete node;
        return new_node;
      }
    }
  }
  else if (node->val < value)
    node->right = deleteNode(node->right, value);
  else
    node->left = deleteNode(node->left, value);

  return node;
}

// find the successor (in inorder traversal) in right child
TreeNode* Tri_Nary_Tree::findSuccessor(TreeNode *node) {
  if (node->left == NULL)
    return node;
  else
    return findSuccessor(node->left);
}

/*

*/

/**
* Implement insert and delete in a trinary tree.
*
*/
public class TrinaryTree {

    /**
     * define a trinary tree's node
     *
     */
    static class TreeNode{
        public int val;  // node's value
        public TreeNode left, right, mid;  // represent left, right, middle 
node
        public TreeNode(int v){
            this.val = v;
            left = null;
            right = null;
            mid = null;
        }
    }

    TreeNode root;
    
    public TrinaryTree(){
        root = null;
    }
    
    public void insert(int v){
        root = insert(root, v);
    }
    
    /**
     * insert a node into the tree
     * @param node
     * @param v
     * @return
     */
    public TreeNode insert(TreeNode node, int v){
        if(node == null){
            node = new TreeNode(v);
            System.out.println("Insert node "+v);
        } else {
            if(node.val > v){
                node.left = insert(node.left,v);
            } else if(node.val < v) {
                node.right = insert(node.right,v);
            } else {
                node.mid = insert(node.mid,v);
            }
        }
        return node;        
    }
    
    public void delete(int v){
        root = delete(root,v);
    }
    /**
     * delete a node from the tree, if there are duplicates, delete the 
lowest one
     * @param node
     * @param v
     * @return
     */
    public TreeNode delete(TreeNode node, int v){
        //can't find the node, return
        if(node == null){
            System.out.println("Can not find node "+v);
            return null; 
        } else if(node.val > v){
            node.left = delete(node.left,v);
        } else if(node.val < v){
            node.right = delete(node.right,v);        
        } else {
            if(node.mid != null){
                node.mid = delete(node.mid,v);
            } else if(node.right != null){
                node.val = findMin(node.right);
                node.right = delete(node.right,node.val);
            } else {
                System.out.println("Delete node "+node.val);
                node = node.left;
            }
        }
        return node;
    }
    
    /**
     * find the leftmost(minimum) node and delete it
     * @param node
     * @return
     */
    public int findMin(TreeNode node){
        if(node.left == null){
            int v = node.val;            
            return v;
        } else {
            return findMin(node.left);
        }
    }
    
    public static void main(String[]args){
        TrinaryTree tree = new TrinaryTree();
        int[] num = {5,4,9,5,7,2,2};
        for(int i = 0; i < num.length; i++){
            tree.insert(num[i]);            
        }
        
        //delete a node doesn't exist
        tree.delete(1);
        
        //delete one of duplicates
        tree.delete(5);
        tree.delete(2);
        //delete the node has both children
        tree.delete(5);
        //delete the node only has left child
        tree.delete(4);
        //delete leaf node
        tree.delete(2);
        tree.delete(9);
        //delete single node
        tree.delete(7);
        
        //delete a node from an empty tree
        tree.delete(2);
    }
}