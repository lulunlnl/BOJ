#include "bits/stdc++.h"
using namespace std;

struct UnionFind {
    vector<int> par, sz;

    void init(int N) {
        par.resize(N+1);
        sz.resize(N+1);
        for (int i = 0; i <= N; i++) par[i] = i, sz[i] = 1;
    }

    int find(int v) {
        return (v == par[v]) ? v : (par[v] = find(par[v]));
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        par[u] = v;
        sz[v] += sz[u]; sz[u] = sz[v];
        return true;
    }
};

struct Edge {
    int u, v, w;
    Edge():Edge(-1, -1, 0) {}
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    bool operator < (const Edge &O) {
        return w < O.w;
    }
};

void solve(int N, int M) {
    UnionFind UF;
    UF.init(N);
    vector<Edge> E(M);
    int sum = 0;
    for (int i = 0; i < M; i++) {
        int x, y, z; cin >> x >> y >> z; sum += z;
        E[i] = Edge(x, y, z);
    }
    sort(E.begin(), E.end());
    for (int i = 0; i < M; i++) {
        if (UF.merge(E[i].u, E[i].v)) {
            sum -= E[i].w;
        }
    }
    cout << sum << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        int N, M; cin >> N >> M;
        if (M == 0 && N == 0) break;
        solve(N, M);
    }
}