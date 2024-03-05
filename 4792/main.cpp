#include "bits/stdc++.h"
using namespace std;

struct UF {
    vector<int> par, sz;
    void init(int N) {
        par.resize(N+1); sz.resize(N+1);
        for (int i = 0; i <= N; i++) par[i] = i, sz[i] = 1;
    }
    int find(int v) {
        return (v == par[v]) ? v : (par[v] = find(par[v]));
    }
    bool merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        par[u] = v; sz[v] += sz[u];
        sz[u] = sz[v];
        return true;
    }
};


struct Edge {
    int u, v, c;
};

int solve() {
    int N, M, K; cin >> N >> M >> K;
    if (!N && !M && !K) return -1;
    vector<Edge> E; UF uf;
    uf.init(N+1);
    for (int i = 0; i < M; i++) {
        char c; int u, v, color;
        cin >> c >> u >> v;
        color = c == 'R' ? 0 : 1;
        E.push_back({u, v, color});
    }
    sort(E.begin(), E.end(), [&] (Edge a, Edge b) {
        return a.c < b.c;
    });
    int mn = 0, mx = 0;
    for (int i = 0; i < M; i++) {
        if (uf.merge(E[i].u, E[i].v)) {
            mn += E[i].c;
        }
    }
    uf.init(N+1);
    for (int i = M-1; i >= 0; i--) {
        if (uf.merge(E[i].u, E[i].v)) {
            mx += E[i].c;
        }
    }
    if (mn <= K && K <= mx) cout << "1\n";
    else cout << "0\n";
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        if (solve() == -1) break;
    }
}