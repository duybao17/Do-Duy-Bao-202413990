#include <iostream>
#include <climits>
 using namespace std;

const int V = 11;
string ten[V] = {"Ha Noi","Son Tay","Hoa Binh","Phu Ly","Hung Yen","Hai Duong","Hai Phong","Uong Bi","Bac Ninh","Bac Giang","Thai Nguyen"};
int canh[][3] = {{0,5,1},{5,4,2},{4,3,3},{0,3,4},{0,2,5},{0,1,6},{0,10,7},{0,8,8},{8,9,9},{9,7,10},{8,7,11},{7,6,12},{5,6,13}};
const int E = 13;
int mat[V][V];

void build() {
    for (int k = 0; k < E; k++) {
        mat[canh[k][0]][canh[k][1]] = canh[k][2];
        mat[canh[k][1]][canh[k][0]] = canh[k][2];
    }
}

void inDuong(int s, int t, int truoc[]) {
    int path[V], n = 0, cur = t;
    while (cur != -1) { path[n++] = cur; cur = truoc[cur]; }
    for (int i = n - 1; i >= 0; i--) cout << ten[path[i]] << (i ? " -> " : "\n");
}

void dfs(int u, int t, bool vis[], int truoc[], bool &found) {
    vis[u] = true;
    if (u == t) { found = true; return; }
    for (int v = 0; v < V && !found; v++)
        if (mat[u][v] && !vis[v]) { truoc[v] = u; dfs(v, t, vis, truoc, found); }
}

void dijkstra(int s, int t) {
    int dist[V], truoc[V]; bool vis[V] = {};
    for (int i = 0; i < V; i++) { dist[i] = INT_MAX; truoc[i] = -1; }
    dist[s] = 0;
    for (int i = 0; i < V; i++) {
        int u = -1, best = INT_MAX;
        for (int j = 0; j < V; j++) if (!vis[j] && dist[j] < best) { best = dist[j]; u = j; }
        vis[u] = true;
        for (int v = 0; v < V; v++)
            if (mat[u][v] && dist[u] + mat[u][v] < dist[v]) { dist[v] = dist[u] + mat[u][v]; truoc[v] = u; }
    }
    cout << "Duong di ngan nhat (" << dist[t] << "): ";
    inDuong(s, t, truoc);
}

int main() {
    build();
    int start = 0, target = 6;

    bool vis[V] = {}, found = false; int truoc[V]; for (int i = 0; i < V; i++) truoc[i] = -1;
    dfs(start, target, vis, truoc, found);
    cout << "Duong di (DFS): ";
    inDuong(start, target, truoc);

    dijkstra(start, target);
}