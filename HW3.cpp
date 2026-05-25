#include <iostream>
#include <string>
using namespace std;

const int N    = 8;
const int MAXS = 256;
const string NIL = "";
string vals[N + 1] = {"", "a", "b", "c", "d", "e", "f", "g", "h"};

//  CẤU TRÚC NODE 
struct Node {
    string val;
    Node  *left;
    Node  *right;

    Node(string v) {
        val   = v;
        left  = nullptr;
        right = nullptr;
    }
};

//  CẤU TRÚC CÂY TUẦN TỰ 
struct SeqTree {
    string arr[MAXS];

    SeqTree() {
        for (int i = 0; i < MAXS; i++) {
            arr[i] = NIL;
        }
    }
};

//  HÀM DUYỆT - TUẦN TỰ
void SeqTrc(const SeqTree &T, int i) {
    if (i >= MAXS || T.arr[i] == NIL) {
        return;
    }
    cout << T.arr[i] << " ";
    SeqTrc(T, 2 * i);
    SeqTrc(T, 2 * i + 1);
}

void SeqGiua(const SeqTree &T, int i) {
    if (i >= MAXS || T.arr[i] == NIL) {
        return;
    }
    SeqGiua(T, 2 * i);
    cout << T.arr[i] << " ";
    SeqGiua(T, 2 * i + 1);
}

void SeqSau(const SeqTree &T, int i) {
    if (i >= MAXS || T.arr[i] == NIL) {
        return;
    }
    SeqSau(T, 2 * i);
    SeqSau(T, 2 * i + 1);
    cout << T.arr[i] << " ";
}

//  HÀM DUYỆT - MÓC NỐI
void LkTrc(Node *r) {
    if (r == nullptr) {
        return;
    }
    cout << r->val << " ";
    LkTrc(r->left);
    LkTrc(r->right);
}

void LkGiua(Node *r) {
    if (r == nullptr) {
        return;
    }
    LkGiua(r->left);
    cout << r->val << " ";
    LkGiua(r->right);
}

void LkSau(Node *r) {
    if (r == nullptr) {
        return;
    }
    LkSau(r->left);
    LkSau(r->right);
    cout << r->val << " ";
}

void deleteTree(Node *&r) {
    if (r == nullptr) {
        return;
    }
    deleteTree(r->left);
    deleteTree(r->right);
    delete r;
    r = nullptr;
}

//  IN KẾT QUẢ
void printSeqTree(const SeqTree &T, const string &name) {
    cout << "\nTuan tu: " << name << "\n";
    cout << "Mang: [ ";
    for (int i = 1; i < MAXS; i++) {
        if (T.arr[i] != NIL) {
            cout << "i" << i << ":" << T.arr[i] << " ";
        }
    }
    cout << "]\n";
    cout << "Truoc: ";
    SeqTrc(T, 1);
    cout << "\n";
    cout << "Giua: ";
    SeqGiua(T, 1);
    cout << "\n";
    cout << "Sau: ";
    SeqSau(T, 1);
    cout << "\n";
}

void printLinkedTree(Node *root, const string &name) {
    cout << "\nMoc noi: " << name << "\n";
    cout << "Truoc: ";
    LkTrc(root);
    cout << "\n";
    cout << "Giua: ";
    LkGiua(root);
    cout << "\n";
    cout << "Sau: ";
    LkSau(root);
    cout << "\n";
}

//  XÂY DỰNG CÂY TUẦN TỰ
SeqTree build_seqdaydu() {
    SeqTree T;
    for (int i = 1; i <= N; i++) {
        T.arr[i] = vals[i];
    }
    return T;
}

SeqTree build_seqlechtrai() {
    SeqTree T;
    int pos = 1;
    for (int k = 1; k <= N; k++) {
        T.arr[pos] = vals[k];
        pos = 2 * pos;
    }
    return T;
}

SeqTree build_seqlechphai() {
    SeqTree T;
    int pos = 1;
    for (int k = 1; k <= N; k++) {
        T.arr[pos] = vals[k];
        pos = 2 * pos + 1;
    }
    return T;
}

SeqTree build_seqzigzac() {
    SeqTree T;
    int  pos    = 1;
    bool goLeft = true;
    for (int k = 1; k <= N; k++) {
        T.arr[pos] = vals[k];
        if (goLeft) {
            pos = 2 * pos;
        } else {
            pos = 2 * pos + 1;
        }
        goLeft = !goLeft;
    }
    return T;
}

//  XÂY DỰNG CÂY MÓC NỐI
Node* build_lkdaydu() {
    Node *nd[N + 1];
    for (int i = 1; i <= N; i++) {
        nd[i] = new Node(vals[i]);
    }
    for (int i = 1; i <= N; i++) {
        if (2 * i     <= N) nd[i]->left  = nd[2 * i];
        if (2 * i + 1 <= N) nd[i]->right = nd[2 * i + 1];
    }
    return nd[1];
}

Node* build_lklechtrai() {
    Node *root = new Node(vals[1]);
    Node *cur  = root;
    for (int k = 2; k <= N; k++) {
        cur->left = new Node(vals[k]);
        cur       = cur->left;
    }
    return root;
}

Node* build_lklechphai() {
    Node *root = new Node(vals[1]);
    Node *cur  = root;
    for (int k = 2; k <= N; k++) {
        cur->right = new Node(vals[k]);
        cur        = cur->right;
    }
    return root;
}

Node* build_lkzigzac() {
    Node *root  = new Node(vals[1]);
    Node *cur   = root;
    bool goLeft = true;
    for (int k = 2; k <= N; k++) {
        Node *child = new Node(vals[k]);
        if (goLeft) {
            cur->left  = child;
        } else {
            cur->right = child;
        }
        cur     = child;
        goLeft  = !goLeft;
    }
    return root;
}

Node* buildExprTree() {
    Node *root   = new Node("-");
    Node *divN   = new Node("/");
    Node *powN   = new Node("^");
    Node *plus1  = new Node("+");
    Node *dN     = new Node("d");
    Node *minus2 = new Node("-");
    Node *gN     = new Node("g");
    Node *mul1   = new Node("*");
    Node *cN     = new Node("c");
    Node *mul2   = new Node("*");
    Node *hN     = new Node("h");
    Node *aN     = new Node("a");
    Node *bN     = new Node("b");
    Node *eN     = new Node("e");
    Node *fN     = new Node("f");
    root->left   = divN;
    root->right  = powN;
    divN->left   = plus1;
    divN->right  = dN;
    powN->left   = minus2;
    powN->right  = gN;
    plus1->left  = mul1;
    plus1->right = cN;
    minus2->left  = mul2;
    minus2->right = hN;
    mul1->left  = aN;
    mul1->right = bN;
    mul2->left  = eN;
    mul2->right = fN;
    return root;
}

void exprInOrder(Node *r, bool isRoot) {
    if (r == nullptr) {
        return;
    }
    bool isOp = (r->val == "+" || r->val == "-" ||
                 r->val == "*" || r->val == "/" || r->val == "^");
    if (isOp && !isRoot) {
        cout << "(";
    }
    exprInOrder(r->left,  false);
    cout << r->val;
    exprInOrder(r->right, false);
    if (isOp && !isRoot) {
        cout << ")";
    }
}


int main() {
    cout << "  LUU TRU TUAN TU\n";

    SeqTree T1 = build_seqdaydu();
    printSeqTree(T1, "Cay day du");

    SeqTree T2 = build_seqlechtrai();
    printSeqTree(T2, "Cay lech trai");

    SeqTree T3 = build_seqlechphai();
    printSeqTree(T3, "Cay lech phai");

    SeqTree T4 = build_seqzigzac();
    printSeqTree(T4, "Cay zigzag");

    cout << "  LUU TRU MOC NOI\n";

    Node *r1 = build_lkdaydu();
    printLinkedTree(r1, "Cay day du");
    deleteTree(r1);

    Node *r2 = build_lklechtrai();
    printLinkedTree(r2, "Cay lech trai");
    deleteTree(r2);

    Node *r3 = build_lklechphai();
    printLinkedTree(r3, "Cay lech phai");
    deleteTree(r3);

    Node *r4 = build_lkzigzac();
    printLinkedTree(r4, "Cay zigzag");
    deleteTree(r4);

    cout << "  CAY BIEU THUC: (a*b+c)/d - (e*f-h)^g\n";
    Node *expr = buildExprTree();

    cout << "Truoc (prefix ): ";
    LkTrc(expr);
    cout << "\n";

    cout << "Giua  (infix  ): ";
    exprInOrder(expr, true);
    cout << "\n";

    cout << "Sau   (postfix): ";
    LkSau(expr);
    cout << "\n";

    deleteTree(expr);

    return 0;
}