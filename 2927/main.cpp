#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Query {
    string op;
    int a, b;
};

struct UF {
    vector<int> par;

    void init(int n) {
        par.resize(n + 1);
        for (int i = 0; i <= n; i++) par[i] = i;
    }

    int find(int v) {
        return (v == par[v] ? v : (par[v] = find(par[v])));
    }

    bool merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        par[b] = a;
        return true;
    }
} uf;

struct Seg {
    ll tree[200005];

    void update(int node, int s, int e, int idx, ll val) {
        if (idx < s || idx > e) return;
        if (s == e) {
            tree[node] = val;
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, idx, val);
        update(node << 1 | 1, m + 1, e, idx, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    ll query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
    }
} seg;

vector<int> adj[30005], g[30005];
int sz[30005], dep[30005], par[30005], top[30005], in[30005];
int n;
ll v[30005];

void dfs(int now, int prev) {
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
    for (auto next: g[now]) {
        top[next] = (next == g[now][0] ? top[now] : next);
        dfs2(next);
    }
}

void update(int idx, ll val) {
    seg.update(1, 1, n, in[idx], val);
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
    ret += seg.query(1, 1, n, in[a], in[b]);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    uf.init(n);

    int m; cin >> m;
    vector<Query> Q;
    while (m--) {
        string op; int a, b;
        cin >> op >> a >> b;
        Q.push_back({op, a, b});
        if (op == "bridge") {
            if (uf.merge(a, b)) {
                adj[a].push_back(b);
                adj[b].push_back(a);
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        if (uf.merge(1, i)) {
            adj[1].push_back(i);
            adj[i].push_back(1);
        }
    }
    uf.init(n);

    top[1] = 1;
    dfs(1, 0); dfs1(1); dfs2(1);
    for (int i = 1; i <= n; i++) update(i, v[i]);

    for (auto [op, a, b]: Q) {
        if (op == "bridge") {
            if (uf.merge(a, b)) cout << "yes\n";
            else cout << "no\n";
        }
        else if (op == "penguins") update(a, b);
        else {
            if (uf.find(a) != uf.find(b)) cout << "impossible\n";
            else cout << query(a, b) << "\n";
        }
    }
}