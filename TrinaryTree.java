/**
 * Implement insert and delete in a tri-nary tree.
 * A tri-nary tree is much like a binary tree but with three child nodes for each parent 
 * instead of two -- with the left node being values less than the parent, the right node values 
 * greater than the parent, and the middle nodes values equal to the parent.
 */
public class TrinaryTree {

    // Define a trinary tree's node
    static class TreeNode {
        private int val;  // Node's value
        private TreeNode left, right, middle;  // Represent left, right, middle node
        public TreeNode(int v){
            this.val = v;
        }
    }

    private TreeNode root; // root of TrinaryTree
    
    public TrinaryTree(){
        root = null;
    }
    
    public void insert(int v){
        root = insert(root, v);
    }
    
    /**
     * Internal method to insert a node into the tree
     * @param node Root of trinary tree
     * @param v Value of the inserted node
     * @return New root of the trinary after insertion
     */
    private TreeNode insert(TreeNode node, int v){
        if (node == null){
            node = new TreeNode(v);
        } else if(node.val > v){
            node.left = insert(node.left, v);
        } else if(node.val < v) {
            node.right = insert(node.right, v);
        } else {
            node.middle = insert(node.middle, v);
        }
        return node;        
    }
    
    public void delete(int v){
        root = delete(root, v);
    }
    /**
     * Internal method to delete a node from the tree, if there are duplicates, delete the lowest one
     * @param node start node
     * @param v Value of the inserted node
     * @return updated start node after deletion or null if not found
     */
    private TreeNode delete(TreeNode node, int v){
        if (node == null){ // Can't find the node, return
            return null; 
        } else if (node.val > v){
            node.left = delete(node.left, v);
        } else if (node.val < v){
            node.right = delete(node.right, v);        
        } else {
            if (node.middle != null){ // delete last node in the middle node list
                TreeNode lastMiddle = node;
                while (lastMiddle.middle != null && lastMiddle.middle.middle != null) {
                    lastMiddle = lastMiddle.middle;
                }
                lastMiddle.middle = null;
            } else { // delete node itself
                if (node.right == null){
                    return node.left;
                }
                if (node.left == null){
                    return node.right;
                }
                TreeNode temp = node;
                node = findLeftmost(temp.right);
                node.right = deleteLeftmost(temp.right);
                node.left = temp.left;
            }
        }
        return node;
    }
    
    /**
     * Internal method to find the leftmost node
     * @param node start node to search
     * @return leftmost node
     */
    private TreeNode findLeftmost(TreeNode node){
        if (node.left == null){           
            return node;
        } else {
            return findLeftmost(node.left);
        }
    }
    
    /**
     * Internal method to delete the leftmost node
     * @param node Start node to search
     * @return updated start node
     */
    private TreeNode deleteLeftmost(TreeNode node){
        if (node.left == null){           
            return node.right;
        }
        node.left = deleteLeftmost(node.left);
        return node;
    }
    
    /**
     * Internal method to print a subtree in sorted order.
     * @param node the node that roots the subtree.
     */
    private void printTree(TreeNode node) {
        if (node != null) {
            printTree(node.left);
            TreeNode mid = node;
            while (mid != null) {
                System.out.print(mid.val + " ");
                mid = mid.middle;  
            }
            printTree(node.right);
        }
    }
    
    /**
      * Print the tree contents in sorted order.
      */
    public void printTree() {
        if (root == null) {
            System.out.println( "Empty tree" );
        } else {
            printTree(root);
            System.out.println();
        }
    }
    
    public static void main(String[]args){
        TrinaryTree tree = new TrinaryTree();
        int[] num = {5, 4, 9, 5, 7, 2, 2};
        tree.printTree();
        for (int i = 0; i < num.length; i++){
            tree.insert(num[i]);            
        }
        System.out.println("After insertion:");
        tree.printTree();
        
        //delete a node doesn't exist
        tree.delete(1);
        System.out.println("After node 1 (not existed) is deleted:");
        tree.printTree();
        
        //delete one of duplicates
        tree.delete(5);
        System.out.println("After node 5 is deleted:");
        tree.printTree();
        tree.delete(2);
        System.out.println("After node 2 is deleted:");
        tree.printTree();
        //delete the node has both children
        tree.delete(5);
        System.out.println("After node 5 is deleted:");
        tree.printTree();
        //delete the node only has left child
        tree.delete(4);
        System.out.println("After node 4 is deleted:");
        tree.printTree();
        //delete leaf node
        tree.delete(2);
        System.out.println("After node 2 is deleted:");
        tree.printTree();
        tree.delete(9);
        System.out.println("After node 9 is deleted:");
        tree.printTree();
        //delete single node
        tree.delete(7);
        System.out.println("After node 7 is deleted:");
        tree.printTree();
        //delete a node from an empty tree
        tree.delete(2);
        System.out.println("After node 2 (not existed) is deleted:");
        tree.printTree();
    }
}