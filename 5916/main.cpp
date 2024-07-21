#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Seg {
    ll tree[400005], lazy[400005];

    void push(int node, int s, int e) {
        if (!lazy[node]) return;
        tree[node] += (e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void update(int node, int s, int e, int l, int r, ll val) {
        push(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[node] += val;
            push(node, s, e);
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, l, r, val);
        update(node << 1 | 1, m + 1, e, l, r, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    ll query(int node, int s, int e, int l, int r) {
        push(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
    }
} seg;

vector<int> adj[100005], g[100005];
int dep[100005], sz[100005], in[100005], par[100005], top[100005];
int n, m;

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
}

void update(int a, int b) {
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        seg.update(1, 1, n, in[st], in[a], 1);
        a = par[st];
    }
    if (in[a] > in[b]) swap(a, b);
    seg.update(1, 1, n, in[a] + 1, in[b], 1);
}

ll query(int a, int b) {
    ll ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret += seg.query(1, 1, n, in[st], in[a]);
        a = par[st];
    }
    if (in[a] > in[b]) swap(a, b);
    ret += seg.query(1, 1, n, in[a] + 1, in[b]);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    top[1] = 1;
    dfs(); dfs1(); dfs2();
    while (m--) {
        char op; int u, v;
        cin >> op >> u >> v;
        if (op == 'P') update(u, v);
        else cout << query(u, v) << "\n";
    }
}