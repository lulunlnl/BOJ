#include "bits/stdc++.h"
#define int long long
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
    Edge(): Edge(-1, -1, 0) {}
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    bool operator < (const Edge &O) {
        return w < O.w;
    }
};

struct Planet {
    int cor[3], idx;
    Planet() {}
    Planet(int x, int y, int z, int idx) : idx(idx) {
        cor[0] = x, cor[1] = y, cor[2] = z;
    }
    int operator - (Planet &a) {
        int ret = 1e9;
        for (int i = 0; i < 3; i++) ret = min(ret, abs(cor[i] - a.cor[i]));
        return ret;
    }
};

Planet arr[100005];

signed main() {
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y, z; cin >> x >> y >> z;
        arr[i] = Planet(x, y, z, i);
    }
    vector<Edge> E(3*N-3);
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        sort(arr, arr+N, [&](Planet &a, Planet &b) {
            return a.cor[i] < b.cor[i];
        });
        for (int j = 0; j < N-1; j++) {
            E[cnt] = Edge(arr[j].idx, arr[j+1].idx, arr[j+1]-arr[j]);
            cnt++;
        }
    }
    sort(E.begin(), E.end());
    UnionFind UF;
    UF.init(3*N);
    int ret = 0;
    for (int i = 0; i < 3*N-3; i++) {
        if (UF.merge(E[i].u, E[i].v)) {
            ret += E[i].w;
        }
    }
    cout << ret << "\n";
}