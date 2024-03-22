#include "bits/stdc++.h"
using namespace std;

struct UF {
    vector<int> par, sz;
    void init(int n) {
        par.resize(n+1);
        sz.resize(n+1);
        iota(par.begin(), par.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }
    int find(int u) {
        return u == par[u] ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        par[v] = u;
        sz[u] += sz[v];
        sz[v] = sz[u];
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    vector<int> c(n+1);
    UF uf;
    uf.init(n+1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        uf.merge(a, b);
    }
    for (int i = 1; i <= n; i++) {
        if (uf.par[i] != i) {
            c[uf.find(i)] += c[i];
            c[i] = 0;
        }
    }
    vector<vector<int>> dp(n+1, vector<int>(k+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < k; j++) {
            if (uf.sz[i] > j) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-uf.sz[i]] + c[i]);
        }
    }
    cout << dp[n][k-1] << "\n";
}