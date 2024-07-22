#include <bits/stdc++.h>
using namespace std;
int n;

struct Seg {
    int tree[400005];
    void update(int node, int s, int e, int idx, int val) {
        if (idx > e || idx < s) return;
        if (s == e) {
            tree[node] = val;
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, idx, val);
        update(node << 1 | 1, m + 1, e, idx, val);
        tree[node] = min(tree[node << 1], tree[node << 1 | 1]);
    }

    int query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 1e9;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return min(query(node << 1, s, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
    }
} seg;

vector<int> adj[100005], g[100005];
int dep[100005], par[100005], sz[100005], in[100005], top[100005], c[100005], rev[100005];

void dfs(int now = 1, int prev = 0) {
    for (auto next: adj[now]) {
        if (next == prev) continue;
        g[now].push_back(next);
        dfs(next, now);
    }
}

void dfs1(int now) {
    sz[now] = 1;
    for (auto &next: g[now]) {
        dep[next] = dep[now] + 1;
        par[next] = now;
        dfs1(next);
        sz[now] += sz[next];
        if (sz[next] > sz[g[now][0]]) swap(next, g[now][0]);
    }
}

int pv;
void dfs2(int now) {
    in[now] = ++pv;
    rev[in[now]] = now;
    for (auto next: g[now]) {
        top[next] = (next == g[now][0] ? top[now] : next);
        dfs2(next);
    }
}

void update(int v) {
    if (!c[v]) {
        c[v] = 1;
        seg.update(1, 1, n, in[v], in[v]);
    }
    else {
        c[v] = 0;
        seg.update(1, 1, n, in[v], 1e9);
    }
}

int query(int v) {
    int ret = 1e9;
    while (top[v] != top[1]) {
        int st = top[v];
        ret = min(ret, seg.query(1, 1, n, in[st], in[v]));
        v = par[st];
    }
    ret = min(ret, seg.query(1, 1, n, in[1], in[v]));
    if (ret == 1e9) return -1;
    return rev[ret];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    top[1] = 1;
    dfs(); dfs1(1); dfs2(1);
    for (int i = 1; i <= n; i++) seg.update(1, 1, n, in[i], 1e9);
    int m; cin >> m;
    while (m--) {
        int op, v;
        cin >> op >> v;
        if (op == 1) update(v);
        else cout << query(v) << "\n";
    }
}