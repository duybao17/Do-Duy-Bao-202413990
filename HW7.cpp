#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int V = 11;
string ten[V] = {"Ha Noi","Son Tay","Hoa Binh","Phu Ly","Hung Yen","Hai Duong","Hai Phong","Uong Bi","Bac Ninh","Bac Giang","Thai Nguyen"};

int canh[][3] = {
    {0,5,1},{5,4,2},{4,3,3},{0,3,4},{0,2,5},
    {0,1,6},{0,10,7},{0,8,8},{8,9,9},{9,7,10},
    {8,7,11},{7,6,12},{5,6,13}
};
const int E = 13;

int mat[V][V];

void buildMatrix() {
    for (int k = 0; k < E; k++) {
        mat[canh[k][0]][canh[k][1]] = canh[k][2];
        mat[canh[k][1]][canh[k][0]] = canh[k][2];
    }
}

void bfsMatrix(int s) {
    bool vis[V] = {};
    queue<int> q;
    vis[s] = true; q.push(s);
    cout << "BFS (Matrix): ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << ten[u];
        for (int v = 0; v < V; v++)
            if (mat[u][v] && !vis[v]) { vis[v] = true; q.push(v); }
        if (!q.empty()) cout << " -> ";
    }
    cout << "\n";
}

struct Node { int dinh, w; Node* next; };
Node* lst[V];

void buildList() {
    for (int k = 0; k < E; k++) {
        int u = canh[k][0], v = canh[k][1], w = canh[k][2];
        lst[u] = new Node{v, w, lst[u]};
        lst[v] = new Node{u, w, lst[v]};
    }
}

void bfsList(int s) {
    bool vis[V] = {};
    queue<int> q;
    vis[s] = true; q.push(s);
    cout << "BFS (List):   ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << ten[u];
        for (Node* c = lst[u]; c; c = c->next)
            if (!vis[c->dinh]) { vis[c->dinh] = true; q.push(c->dinh); }
        if (!q.empty()) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    buildMatrix(); 
    bfsMatrix(0);
    buildList();   
    bfsList(0);
}