#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int V = 11;
string ten[V] = {"Ha Noi","Son Tay","Hoa Binh","Phu Ly","Hung Yen",
                 "Hai Duong","Hai Phong","Uong Bi","Bac Ninh","Bac Giang","Thai Nguyen"};

struct Canh { int u, v, w; };
Canh canh[] = {
    {0,5,1},{5,4,2},{4,3,3},{0,3,4},{0,2,5},
    {0,1,6},{0,10,7},{0,8,8},{8,9,9},{9,7,10},
    {8,7,11},{7,6,12},{5,6,13}
};
const int E = 13;

int cha[V];
int find(int x) { return cha[x] == x ? x : cha[x] = find(cha[x]); }

void kruskal() {
    Canh e[E];
    copy(canh, canh + E, e);
    sort(e, e + E, [](Canh a, Canh b) { return a.w < b.w; });

    for (int i = 0; i < V; i++) cha[i] = i;

    cout << "KRUSKAL " << endl;
    int tongTrongSo = 0;
    for (int i = 0; i < E; i++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (find(u) != find(v)) {
            cha[find(u)] = find(v);
            tongTrongSo += w;
            cout << ten[u] << " - " << ten[v] << endl;
        }
    }
    cout << "Tong trong so MST: " << tongTrongSo << endl;
}

int mat[V][V];

void prim(int start) {
    for (int k = 0; k < E; k++)
        mat[canh[k].u][canh[k].v] = mat[canh[k].v][canh[k].u] = canh[k].w;

    bool inMST[V] = {};
    int key[V], truoc[V];
    for (int i = 0; i < V; i++) { key[i] = INT_MAX; truoc[i] = -1; }
    key[start] = 0;

    cout << "PRIM " << endl;
    int tongTrongSo = 0;

    for (int count = 0; count < V; count++) {
        int u = -1, best = INT_MAX;
        for (int i = 0; i < V; i++)
            if (!inMST[i] && key[i] < best) best = key[u = i];

        inMST[u] = true;
        if (truoc[u] != -1) {
            cout << ten[truoc[u]] << " - " << ten[u] << endl;
            tongTrongSo += key[u];
        }

        for (int v = 0; v < V; v++)
            if (mat[u][v] && !inMST[v] && mat[u][v] < key[v]) {
                key[v] = mat[u][v];
                truoc[v] = u;
            }
    }
    cout << "Tong trong so MST: " << tongTrongSo << endl;
}

int main() {
    kruskal();
    prim(2);
}