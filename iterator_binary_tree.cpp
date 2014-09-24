using namespace std;

struct TreeNode {
   int val;
   TreeNode *left, *right;
   TreeNode(int x): val(x), left(NLLL), right(NULL) {}
};

templeate <typname T>
class Iterator<T> {
public:
    bool hasNext() {}
    T next() {}
    void Reset() {}
};

enum traversalMethod {INORDER, PREORDER, POSTORDER};

class BinaryTreeIterator : public Iterator {

    BinaryTreeIterator (TreeNode *root, traversalMethod method) {
        rootBack = root;
        mtd = method;
        initialzation(root);
    }

    void Reset() {
        stk.clear();
        initialzation(rootBack);
    }
   
    bool hasNext() {
        return !stk.empty();
    }
   
    TreeNode *next() {
        if (!hasNext()) {
            return NULL;
        }

        TreeNode *res = stk.top();
        stk.pop();

        switch(mtd) {       
            case INORDER:
                initialzation (res->right);
            case PREODER:
                if (res->right) {
                    stk.push(res->right);
                }
                if (res->left) {
                    stk.push(res->left);
                }
            case POSTODER:
                if (!stk.empty()) {
                    TreeNode *peak = stk.top();
                    if (res != peak->right) {
                        initialzation (peak->right);
                    }
                }
        }
        return res;
    }

    private: 
        void initialzation(TreeNode *cur) {
            swicth(mtd) {
                case INORDER: 
                    while (cur != NULL) {
                        stk.push(cur);
                        cur = cur->left;
                    }
                case PREORDER: 
                    if(cur != NULL) {
                        stk.push(cur);
                    }      
                case POSTORDER: 
                    while(cur != NULL) {
                        stk.push(cur);
                        if (cur->left) {
                            cur = cur->left;
                        } else {
                            cur = cur->right;
                        }                        
                    }
            }
        }

       stack<TreeNode *> stk;
       TreeNode *rootBack;
       traversalMethod mtd;
};