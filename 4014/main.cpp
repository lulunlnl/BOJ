#include "bits/stdc++.h"
#define ft first
#define sd second
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, K; cin >> N >> M >> K;
    vector<pair<int, int>> R, B;
    UF U1, U2; U1.init(N); U2.init(N);
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        if (c) R.push_back({a, b});
        else B.push_back({a, b});
    }
    vector<pair<int, int>> ans;
    for (auto &e: R) U1.merge(e.ft, e.sd);
    for (auto &e: B) {
        if (U1.merge(e.ft, e.sd)) {
            U2.merge(e.ft, e.sd);
            ans.push_back({e.ft, e.sd});
        }
    }
    for (auto &e: B) {
        if (ans.size() == K) break;
        if (U2.merge(e.ft, e.sd)) ans.push_back({e.ft, e.sd});
    }
    if (ans.size() != K) {
        cout << "no solution" << "\n";
        return 0;
    }
    for (auto &e: ans) {
        cout << e.ft << " " << e.sd << " 0\n";
    }
    for (auto &e: R) {
        if (U2.merge(e.ft, e.sd)) {
            cout << e.ft << " " << e.sd << " 1\n";
        }
    }
}