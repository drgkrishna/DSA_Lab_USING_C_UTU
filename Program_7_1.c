#include <stdio.h>
#include <stdlib.h>
struct Node {
    int key, height;
    struct Node *left, *right;
};
int height(struct Node *n) {
    return n ? n->height : 0;
}
int max(int a, int b) {
    return a > b ? a : b;
}
struct Node* create(int key) {
    struct Node *n = malloc(sizeof(struct Node));
    n->key = key;
    n->height = 1;
    n->left = n->right = NULL;
    return n;
}
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *t = x->right;
    x->right = y;
    y->left = t;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *t = y->left;
    y->left = x;
    x->right = t;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
int balance(struct Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}
struct Node* insert(struct Node *root, int key) {
    int b;
    if (!root)
    return create(key);
    if (key < root->key)
    root->left = insert(root->left, key);
    else if (key > root->key)
    root->right = insert(root->right, key);
    else
    return root;
    root->height = max(height(root->left),
    height(root->right)) + 1;
    b = balance(root);
    if (b > 1 && key < root->left->key)
    return rightRotate(root);
    if (b < -1 && key > root->right->key)
    return leftRotate(root);
    if (b > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (b < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void inorder(struct Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
int main() {
    struct Node *root = NULL;
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 40);
    printf("AVL Tree: ");
    inorder(root);
    return 0;
}
