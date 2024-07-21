#include <bits/stdc++.h>
using namespace std;
int x[100005], y[100005], w[100005], n;

struct Seg {
    int tree[400005];
    void update(int node, int s, int e, int idx, int val) {
        if (s > idx || idx > e) return;
        if (s == e) {
            tree[node] = val;
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, idx, val);
        update(node << 1 | 1, m + 1, e, idx, val);
        tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
    }

    int query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return max(query(node << 1, s, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
    }
} seg;

int sz[100005], dep[100005], par[100005], top[100005], in[100005], out[100005];
vector<int> g[100005];
vector<int> adj[100005];

void dfs(int now = 1, int prev = 0) {
    for (auto next: adj[now]) {
        if (next == prev) continue;
        g[now].push_back(next);
        dfs(next, now);
    }
}

void dfs1(int now = 1) {
    sz[now] = 1;
    for (auto &next: g[now]) {
        dep[next] = dep[now] + 1; par[next] = now;
        dfs1(next);
        sz[now] += sz[next];
        if (sz[next] > sz[g[now][0]]) swap(next, g[now][0]);
    }
}

int pv;
void dfs2(int now = 1) {
    in[now] = ++pv;
    for (auto next: g[now]) {
        top[next] = (next == g[now][0] ? top[now] : next);
        dfs2(next);
    }
    out[now] = pv;
}

void update(int idx, int val) {
    if (dep[x[idx]] < dep[y[idx]]) swap(x[idx], y[idx]);
    seg.update(1, 1, n, in[x[idx]], val);
}

int query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret = max(ret, seg.query(1, 1, n, in[st], in[a]));
        a = par[st];
    }
    if (in[a] > in[b]) swap(a, b);
    ret = max(ret, seg.query(1, 1, n, in[a] + 1, in[b]));
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> x[i] >> y[i] >> w[i];
        adj[x[i]].push_back(y[i]);
        adj[y[i]].push_back(x[i]);
    }
    top[1] = 1;
    dfs(); dfs1(); dfs2();

    for (int i = 1; i < n; i++) {
        update(i, w[i]);
    }
    int q; cin >> q;
    while (q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) update(a, b);
        else cout << query(a, b) << "\n";
    }
}