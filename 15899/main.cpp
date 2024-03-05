#include "bits/stdc++.h"
#define all(v) v.begin(), v.end()
using namespace std;
const int MAX = 200005, MOD = 1e9+7;
int in[MAX], out[MAX], arr[MAX], color[MAX];
vector<int> tree[4*MAX], g[MAX];

void dfs(int v, int par) {
    static int pv = 0;
    in[v] = ++pv; arr[pv] = color[v];
    for (auto next: g[v]) {
        if (next != par) dfs(next, v);
    }
    out[v] = pv;
}

void init(int node, int s, int e) {
    if (s == e) {
        tree[node].push_back(arr[s]);
        return;
    }
    int m = s + e >> 1;
    init(node << 1, s, m);
    init(node << 1 | 1, m+1, e);
    tree[node].resize(tree[node << 1].size() + tree[node << 1 | 1].size());
    merge(all(tree[node << 1]), all(tree[node << 1 | 1]), tree[node].begin());
}

int query(int node, int s, int e, int l, int r, int k) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return upper_bound(all(tree[node]), k) - tree[node].begin();
    int m = s + e >> 1;
    return query(node << 1, s, m, l, r, k) + query(node << 1 | 1, m+1, e, l, r, k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, C; cin >> N >> M >> C;
    for (int i = 1; i <= N; i++) {
        cin >> color[i];
    }
    for (int i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0);
    init(1, 1, N);
    long long ret = 0;
    while (M--) {
        int v, c; cin >> v >> c;
        ret += query(1, 1, N, in[v], out[v], c);
        ret %= MOD;
    }
    cout << ret << "\n";
}