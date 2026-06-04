//                                          Giai thuat AVL
#include <iostream>
using namespace std;

struct Node {
    int data;
    int height;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* n = new Node;
    n->data = data;
    n->height = 1;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

int height(Node* n) {
    if (n == nullptr)
        return 0;
    return n->height;
}

void update_h(Node* n) {
    int l = height(n->left);
    int r = height(n->right);
    n->height = 1 + (l > r ? l : r);
}

int bf(Node* n) {
    if (n == nullptr)
        return 0;
    return height(n->left) - height(n->right);
}

Node* RR(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    x->right = y;
    y->left = T;
    update_h(y);
    update_h(x);
    return x;
}

Node* LR(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    update_h(x);
    update_h(y);
    return y;
}

Node* balance(Node* n) {
    update_h(n);
    int b = bf(n);

    // LL
    if (b > 1 && bf(n->left) >= 0)
        return RR(n);

    // LR
    if (b > 1 && bf(n->left) < 0) {
        n->left = LR(n->left);
        return RR(n);
    }

    // RR
    if (b < -1 && bf(n->right) <= 0)
        return LR(n);

    // RL
    if (b < -1 && bf(n->right) > 0) {
        n->right = RR(n->right);
        return LR(n);
    }

    return n;
}

Node* insert(Node* root, int data) {
    if (root == nullptr)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;
    return balance(root);
}

void printTree(Node* root, int space = 0, int gap = 5) {
    if (root == nullptr)
        return;
    space += gap;
    printTree(root->right, space);
    cout << endl;
    for (int i = gap; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->left, space);
}

int main() {
    int arr[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    int n = 9;
    Node* r = nullptr;

    for (int i = 0; i < n; i++) {
        r = insert(r, arr[i]);
        cout << "Insert " << arr[i] << ":\n";
        printTree(r);
        cout << "\n\n-------------------\n";
    }

    return 0;
}