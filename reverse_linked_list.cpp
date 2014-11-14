/*
Reversing linked list iteratively and recursively
http://leetcode.com/2010/04/reversing-linked-list-iteratively-and.html
*/

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

/* Iteratively */
void reverseLL(ListNode *&head) {
    if (!head) {
        return;
    }
    ListNode *pre = NULL;
    ListNode *cur = head;
    while(cur) {
        ListNode *next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    head = pre;
}

/* Recursively */
void reverseLL(ListNode *&head) {
    if (!head) {
        return;
    }
    ListNode *rest = head->next;
    if (!rest) {
        return;
    }
    reverseLL(rest);
    head->next->next = head;
    head->next = NULL;
    head = rest;
}