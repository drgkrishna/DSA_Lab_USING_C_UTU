#include <stdio.h>
#include <stdlib.h>
#define T 3
struct Node {
    int keys[2 * T - 1];
    struct Node *child[2 * T];
    int n;
    int leaf;
};
struct Node* createNode(int leaf) {
    struct Node *node = malloc(sizeof(struct Node));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; i++)
        node->child[i] = NULL;
    return node;
}
void traverse(struct Node *root) {
    int i;
    if (!root)
        return;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->child[i]);
}
struct Node* search(struct Node *root, int key) {
    int i = 0;
    if (!root)
        return NULL;
    while (i < root->n && key > root->keys[i])
        i++;
    if (i < root->n && root->keys[i] == key)
        return root;
    if (root->leaf)
        return NULL;
    return search(root->child[i], key);
}
void splitChild(struct Node *x, int i) {
    struct Node *y = x->child[i];
    struct Node *z = createNode(y->leaf);
    int j;
    z->n = T - 1;
    for (j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];
    if (!y->leaf)
        for (j = 0; j < T; j++)
            z->child[j] = y->child[j + T];
    y->n = T - 1;
    for (j = x->n; j >= i + 1; j--)
        x->child[j + 1] = x->child[j];
    x->child[i + 1] = z;
    for (j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];
    x->keys[i] = y->keys[T - 1];
    x->n++;
}
void insertNonFull(struct Node *x, int key) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && x->keys[i] > key) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > key)
            i--;
        i++;
        if (x->child[i]->n == 2 * T - 1) {
            splitChild(x, i);
            if (key > x->keys[i])
                i++;
        }
        insertNonFull(x->child[i], key);
    }
}
struct Node* insert(struct Node *root, int key) {
    if (!root)
        return NULL;
    if (root->n == 2 * T - 1) {
        struct Node *s = createNode(0);
        s->child[0] = root;
        splitChild(s, 0);
        int i = (s->keys[0] < key) ? 1 : 0;
        insertNonFull(s->child[i], key);
        return s;
    }
    insertNonFull(root, key);
    return root;
}
int findKey(struct Node *x, int key) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < key)
        idx++;
    return idx;
}
int getPred(struct Node *x, int idx) {
    struct Node *cur = x->child[idx];
    while (!cur->leaf)
        cur = cur->child[cur->n];
    return cur->keys[cur->n - 1];
}
int getSucc(struct Node *x, int idx) {
    struct Node *cur = x->child[idx + 1];
    while (!cur->leaf)
        cur = cur->child[0];
    return cur->keys[0];
}
void borrowFromPrev(struct Node *x, int idx) {
    struct Node *child = x->child[idx];
    struct Node *sibling = x->child[idx - 1];
    int i;
    for (i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf)
        for (i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];
    child->keys[0] = x->keys[idx - 1];
    if (!child->leaf)
        child->child[0] = sibling->child[sibling->n];
    x->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n++;
    sibling->n--;
}
void borrowFromNext(struct Node *x, int idx) {
    struct Node *child = x->child[idx];
    struct Node *sibling = x->child[idx + 1];
    int i;
    child->keys[child->n] = x->keys[idx];
    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];
    x->keys[idx] = sibling->keys[0];
    for (i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];
    if (!sibling->leaf)
        for (i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    child->n++;
    sibling->n--;
}
void merge(struct Node *x, int idx) {
    struct Node *child = x->child[idx];
    struct Node *sibling = x->child[idx + 1];
    int i;
    child->keys[T - 1] = x->keys[idx];
    for (i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];
    if (!child->leaf)
        for (i = 0; i <= sibling->n; i++)
            child->child[i + T] = sibling->child[i];
    for (i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];
    for (i = idx + 2; i <= x->n; i++)
        x->child[i - 1] = x->child[i];
    child->n += sibling->n + 1;
    x->n--;
    free(sibling);
}
void fill(struct Node *x, int idx) {
    if (idx != 0 && x->child[idx - 1]->n >= T)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->child[idx + 1]->n >= T)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx - 1);
    }
}
void removeFromLeaf(struct Node *x, int idx) {
    for (int i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];
    x->n--;
}
void removeKey(struct Node *x, int key);
void removeFromNonLeaf(struct Node *x, int idx) {
    int key = x->keys[idx];
    if (x->child[idx]->n >= T) {
        int pred = getPred(x, idx);
        x->keys[idx] = pred;
        removeKey(x->child[idx], pred);
    } else if (x->child[idx + 1]->n >= T) {
        int succ = getSucc(x, idx);
        x->keys[idx] = succ;
        removeKey(x->child[idx + 1], succ);
    } else {
        merge(x, idx);
        removeKey(x->child[idx], key);
    }
}
void removeKey(struct Node *x, int key) {
    int idx = findKey(x, key);
    if (idx < x->n && x->keys[idx] == key) {
        if (x->leaf)
            removeFromLeaf(x, idx);
        else
            removeFromNonLeaf(x, idx);
    } else {
        if (x->leaf)
            return;
        int flag = (idx == x->n);
        if (x->child[idx]->n < T)
            fill(x, idx);
        if (flag && idx > x->n)
            removeKey(x->child[idx - 1], key);
        else
            removeKey(x->child[idx], key);
    }
}
struct Node* deleteKey(struct Node *root, int key) {
    if (!root)
        return NULL;
    removeKey(root, key);
    if (root->n == 0) {
        struct Node *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];
        free(tmp);
    }
    return root;
}
int main() {
    struct Node *root = createNode(1);
    int a[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int i;
    for (i = 0; i < 8; i++)
        root = insert(root, a[i]);
    printf("B-Tree (inorder) after insertion: ");
    traverse(root);
    printf("\n");
    printf("Search 6: %s\n", search(root, 6) ? "Found" : "Not Found");
    printf("Search 15: %s\n", search(root, 15) ? "Found" : "Not Found");
    root = deleteKey(root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");
    root = deleteKey(root, 30);
    printf("After deleting 30: ");
    traverse(root);
    printf("\n");
    return 0;
}
