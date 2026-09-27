#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *left, *right;
};
struct Node* create(int x) {
    struct Node *n = malloc(sizeof(struct Node));
    n->data = x;
    n->left = n->right = NULL;
    return n;
}
void preorder(struct Node *root) {
    struct Node *stack[20];
    int top = -1;
    if (!root)
    return;
    stack[++top] = root;
    while (top != -1) {
        struct Node *p = stack[top--];
        printf("%d ", p->data);
        if (p->right)
        stack[++top] = p->right;
        if (p->left)
        stack[++top] = p->left;
    }
}
void inorder(struct Node *root) {
    struct Node *stack[20];
    int top = -1;
    struct Node *p = root;
    while (p || top != -1) {
        while (p) {
            stack[++top] = p;
            p = p->left;
        }
        p = stack[top--];
        printf("%d ", p->data);
        p = p->right;
    }
}
void postorder(struct Node *root) {
    struct Node *s1[20], *s2[20];
    int t1 = -1, t2 = -1;
    if (!root)
    return;
    s1[++t1] = root;
    while (t1 != -1) {
        struct Node *p = s1[t1--];
        s2[++t2] = p;
        if (p->left)
        s1[++t1] = p->left;
        if (p->right)
        s1[++t1] = p->right;
    }
    while (t2 != -1)
    printf("%d ", s2[t2--]->data);
}
int main() {
    struct Node *root = create(1);
    root->left = create(2);
    root->right = create(3);
    root->left->left = create(4);
    root->left->right = create(5);
    printf("Pre-order: ");
    preorder(root);
    printf("\nIn-order: ");
    inorder(root);
    printf("\nPost-order: ");
    postorder(root);
    return 0;
}
