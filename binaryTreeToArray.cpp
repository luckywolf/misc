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
	convertDFSRe(res, root, 0);
  return res;
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
    	cout << res[i] << endl;
    }
    return 0;
}
