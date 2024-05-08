#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr ll mod = 1e9;
int par[100005];
ll sz[100005];

int find(int x) {
    return x == par[x] ? x : par[x] = find(par[x]);
}

bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return 0;
    par[v] = u;
    sz[u] += sz[v];
    sz[v] = 0;
    return 1;
}

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    iota(par, par + n + 1, 0);
    fill(sz, sz + n + 1, 1);
    vector<array<int, 3>> edge;
    ll sum = 0;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        edge.push_back({c, a, b});
        sum += c;
    }
    sort(edge.begin(), edge.end(), greater<>());
    ll ans = 0;
    for (auto [w, u, v]: edge) {
        u = find(u), v = find(v);
        if (u != v) {
            ans += sum * sz[u] % mod * sz[v] % mod;
            ans %= mod;
            merge(u, v);
        }
        sum -= w;
    }
    cout << ans;
}