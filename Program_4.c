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
struct Node* insert(struct Node *root, int x) {
    if (root == NULL)
    return create(x);
    if (x < root->data)
    root->left = insert(root->left, x);
    else if (x > root->data)
    root->right = insert(root->right, x);
    return root;
}
struct Node* search(struct Node *root, int x) {
    if (!root || root->data == x)
    return root;
    if (x < root->data)
    return search(root->left, x);
    return search(root->right, x);
}
struct Node* minNode(struct Node *root) {
    while (root->left)
    root = root->left;
    return root;
}
struct Node* deleteNode(struct Node *root, int x) {
    struct Node *t;
    if (!root)
    return NULL;
    if (x < root->data)
    root->left = deleteNode(root->left, x);
    else if (x > root->data)
    root->right = deleteNode(root->right, x);
    else {
        if (!root->left) {
            t = root->right;
            free(root);
            return t;
        }
        if (!root->right) {
            t = root->left;
            free(root);
            return t;
        }
        t = minNode(root->right);
        root->data = t->data;
        root->right = deleteNode(root->right, t->data);
    }
    return root;
}
void inorder(struct Node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int main() {
    struct Node *root = NULL;
    int a[] = {50, 30, 70, 20, 40, 60, 80};
    int i;
    for (i = 0; i < 7; i++)
    root = insert(root, a[i]);
    printf("BST: ");
    inorder(root);
    printf("\nSearch 40: ");
    printf(search(root, 40) ? "Found" : "Not Found");
    root = deleteNode(root, 30);
    printf("\nAfter deletion: ");
    inorder(root);
    return 0;
}
