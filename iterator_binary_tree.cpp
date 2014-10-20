using namespace std;

struct TreeNode{
   int val;
   TreeNode *left, *right;
   TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

template <typname T>
class Iterator {
public:
    void Reset();
    bool hasNext();
    T next();
};

enum traversalMethod {INORDER, PREORDER, POSTORDER};

class BinaryTreeIterator : public Iterator<TreeNode *> {
public:
    BinaryTreeIterator(TreeNode *root, traversalMethod method = INORDER) {
        _root = root;
        _method = method;
        initialzation(_root);
    }

    void Reset() {
        _stk.clear();
        initialization(_root);
    }
   
    bool hasNext() {
        return !_stk.empty();
    }
   
    TreeNode *next() {
        if (!hasNext()) {
            return NULL;
        }

        TreeNode *res = _stk.top();
        _stk.pop();
        switch(_method) {       
            case PREORDER:
                if (res->right) {
                    _stk.push(res->right);
                }
                if (res->left) {
                    _stk.push(res->left);
                }
                break;
            case POSTORDER:
                if (!_stk.empty()) {
                    TreeNode *peek = _stk.top();
                    if (res != peek->right) {
                        initialization(peek->right);
                    }
                }
                break;
            default:  // INORDER
                initialization(res->right);
                break;
        }
        return res;
    }

private: 
    stack<TreeNode *> _stk;
    TreeNode *_root;
    traversalMethod _method;

    void initialization(TreeNode *cur) {
        swicth(_method) {
            case PREORDER: 
                if (cur != NULL) {
                    _stk.push(cur);
                }
                break;
            case POSTORDER: 
                while (cur != NULL) {
                    _stk.push(cur);
                    if (cur->left) {
                        cur = cur->left;
                    } else {
                        cur = cur->right;
                    }                        
                }
                break;
            default:  // INORDER
                while (cur != NULL) {
                    _stk.push(cur);
                    cur = cur->left;
                }
                break;
            }
        }
    }
};
