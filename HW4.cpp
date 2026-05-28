#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Node {
    int   data, index;
    Node *left, *right, *parent;
    Node(int val, int idx) : data(val), index(idx), left(nullptr), right(nullptr), parent(nullptr) {}
};

struct Heap {
    Node *root, **nodes;
    int   size;
    Heap(int cap) : root(nullptr), size(cap) { nodes = new Node*[cap]; }
    ~Heap() { 
        del(root); 
        delete[] nodes; 
    }
    void del(Node* n) { 
        if (!n) return; 
        del(n->left); 
        del(n->right); 
        delete n; 
    }
};

Heap* build(int* arr, int n) {
    Heap* h = new Heap(n);
    for (int i = 0; i < n; i++) h->nodes[i] = new Node(arr[i], i+1);
    for (int i = 0; i < n; i++) {
        int l = 2*i+1, r = 2*i+2;
        if (l < n) { h->nodes[i]->left  = h->nodes[l]; h->nodes[l]->parent = h->nodes[i]; }
        if (r < n) { h->nodes[i]->right = h->nodes[r]; h->nodes[r]->parent = h->nodes[i]; }
    }
    h->root = h->nodes[0];
    return h;
}

void printArray(Heap* h, int heapSize = -1) {
    if (heapSize < 0) heapSize = h->size;
    cout << "  Mang  : [ ";
    for (int i = 0; i < h->size; i++) {
        if (i < heapSize) cout << h->nodes[i]->data;
        else              cout << "(" << h->nodes[i]->data << ")";
        if (i < h->size-1) cout << ", ";
    }
    cout << " ]\n  Index : [ ";
    for (int i = 0; i < h->size; i++) {
        cout << setw((int)to_string(h->nodes[i]->data).size()) << (i+1);
        if (i < h->size-1) cout << ", ";
    }
    cout << " ]\n";
}

void heapify(Heap* h, Node* nd, int sz) {
    if (!nd || nd->index > sz) return;
    Node* largest = nd;
    if (nd->left  && nd->left->index  <= sz && nd->left->data  > largest->data) largest = nd->left;
    if (nd->right && nd->right->index <= sz && nd->right->data > largest->data) largest = nd->right;
    if (largest != nd) {
        swap(nd->data, largest->data);
        heapify(h, largest, sz);
    }
}

void heapSort(int* arr, int n, const string& name) {
    cout << "  " << name << "\n";
    Heap* h = build(arr, n);

    cout << "\n[BAN DAU]\n";
    printArray(h);

    cout << "\n[GIAI DOAN 1: XAY MAX-HEAP]\n";
    for (int i = n/2-1; i >= 0; i--) {
        Node* nd = h->nodes[i];
        Node* largest = nd;
        if (nd->left  && nd->left->index  <= n && nd->left->data  > largest->data) largest = nd->left;
        if (nd->right && nd->right->index <= n && nd->right->data > largest->data) largest = nd->right;
        if (largest != nd) {
            heapify(h, nd, n);
            cout << "\n  Heapify nut [" << nd->index << "]\n";
            printArray(h);
        }
    }

    cout << "\n[MAX-HEAP XONG] goc=" << h->root->data << "\n";
    printArray(h);

    cout << "\n[GIAI DOAN 2: SAP XEP]\n";
    for (int sz = n; sz > 1; sz--) {
        swap(h->nodes[0]->data, h->nodes[sz-1]->data);
        if (sz-1 > 1) {
            heapify(h, h->nodes[0], sz-1);
            cout << "\n  Heapify nut [1]\n";
            printArray(h, sz-1);
        }
    }

    cout << "\n[KET QUA]\n";
    printArray(h);
    cout << string(56, ' ') << "\n";
    delete h;
}

int main() {
    int t1[] = {11, 54, 32, 105, 38, 78, 208, 16, 84, 17, 39, 15};
    heapSort(t1, 12, "CAY 1: {11,54,32,105,38,78,208,16,84,17,39,15}");

    int t2[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    heapSort(t2, 9,  "CAY 2: {32,51,27,83,96,11,45,75,66}");
    return 0;
}