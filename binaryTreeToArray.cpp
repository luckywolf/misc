/* convert the linked list representation of a binary tree to 
the array representation
*/

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int maxn = 100;
struct TreeNode{
    int val;
    TreeNode *left, *right;
    TreeNode(int x = -1): val(x), left(NULL), right(NULL) {}
};
TreeNode *p, node[maxn];
int cnt;

void init(){
    p = NULL;
    memset(node, '\0', sizeof(node));
    cnt = 0;
}
void create_minimal_tree(TreeNode* &head, int a[], int start, int end){
    if(start <= end){
        int mid = (start + end) >> 1;
        node[cnt].val = a[mid];
        head = &node[cnt++];
        create_minimal_tree(head->left, a, start, mid-1);
        create_minimal_tree(head->right, a, mid+1, end);
    }
}

void convertDFSRe(vector<int> &res, TreeNode* root, int index) {
    if (root) {
        res[index] = root->val;
        if (root->left) {
            convertDFSRe(res, root->left, 2 * index + 1);
        }
        if (root->right) {
            convertDFSRe(res, root->right, 2 * index + 2);
        }
    }
}

vector<int> convert(TreeNode* root, int height){
    vector<int> res(1 << height);
    // if starting with index 1
    // leftChildIndex = 2 * parentIndex, rightChildIndex = 2 * parentIndex + 1
    // parentIndex = childIndex / 2;
    // if starting with index 0
    // leftChildIndex = 2 * parentIndex + 1, rightChildIndex = 2 * parentIndex + 2
    //  parentIndex = (childIndex - 1) / 2;
    convertDFSRe(res, root, 0); 
    return res;
}

// using array instead of vector
void convertDFSRe_2(int *res2, TreeNode* root, int index) {
    if (root) {
        res2[index] = root->val;
        if (root->left) {
            convertDFSRe_2(res2, root->left, 2 * index + 1);
        }
        if (root->right) {
            convertDFSRe_2(res2, root->right, 2 * index + 2);
        }
    }
}
int *convert_2(TreeNode* root, int height){
    int *res2 = new int[1 << height];
		// memset(myarray, 0, sizeof(myarray)); // for automatically-allocated arrays
    // memset(myarray, 0, N*sizeof(*myarray)); // for heap-allocated arrays, where N is the number of elements
		memset(res2, 0, (1 << height) * sizeof(res2)); // important
    convertDFSRe_2(res2, root, 0); 
    return res2;
}


int main(){
    int a[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };
    init();
    TreeNode *head = NULL;
    create_minimal_tree(head, a, 0, 9);
    int height = 4;
    vector<int> res = convert(head, height);
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << "  ";
    }
    cout << endl;
    
    int *res2 = convert_2(head, height);
    for (int i = 0; i < (1 << height); ++i) {
        cout << res2[i] << "  ";
    }
    cout << endl;
    return 0;
}
