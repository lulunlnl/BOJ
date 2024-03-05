#include "bits/stdc++.h"
using namespace std;
constexpr int MAX = 200005;
int sz[MAX], dep[MAX], par[MAX], top[MAX], in[MAX], out[MAX];
vector<int> g[MAX], adj[MAX];
int s[MAX], e[MAX];

struct SegTree {
    int tree[1 << 19];
    int sz = 1 << 18;

    void update(int x, int v) {
        x |= sz; tree[x] = v;
        while (x >>= 1) {
            tree[x] = (tree[x << 1] & tree[x << 1 | 1]);
        }
    }

    int query(int l, int r) {
        l |= sz, r |= sz;
        int ret = 1;
        while (l <= r) {
            if (l & 1) ret &= tree[l++];
            if (~r & 1) ret &= tree[r--];
            l >>= 1, r >>= 1;
        }
        return ret;
    }
};

struct HLD {
    int chk[MAX], pv;
    SegTree seg;

    void init() {
        top[1] = 1;
        dfs1(); dfs2();
    }

    void dfs(int v = 1) {
        chk[v] = 1;
        for (auto &i: adj[v]) {
            if (chk[i]) continue;
            g[v].push_back(i);
            dfs(i);
        }
    }

    void dfs1(int v = 1) {
        sz[v] = 1;
        for (auto &i: g[v]) {
            dep[i] = dep[v] + 1; par[i] = v;
            dfs1(i); sz[v] += sz[i];
            if (sz[i] > sz[g[v][0]]) swap(i, g[v][0]);
        }
    }

    void dfs2(int v = 1) {
        in[v] = ++pv;
        for (auto &i: g[v]) {
            top[i] = (i == g[v][0]) ? top[v] : i;
            dfs2(i);
        }
        out[v] = pv;
    }

    void update(int u, int v, int val) {
        if (dep[u] < dep[v]) swap(u, v);
        seg.update(in[u], val);
    }

    int query(int a, int b) {
        int ret = 1;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            int st = top[a];
            ret &= seg.query(in[st], in[a]);
            a = par[st];
        }
        if (dep[a] > dep[b]) swap(a, b);
        ret &= seg.query(in[a] + 1, in[b]);
        return ret;
    }
} hld;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N >> Q;
    for (int i = 2; i <= N; i++) {
        int a; cin >> a;
        par[i] = a;
        g[a].push_back(i);
    }
    hld.init();
    for (int i = 2; i <= N; i++) hld.update(i, par[i], 1);

    while (Q--) {
        int op, a, b;
        cin >> a >> b >> op;
        int ans = hld.query(a, b);
        if (ans) cout << "YES\n";
        else cout << "NO\n";
        if (op) {
            if (ans) hld.update(a, par[a], 0);
            else hld.update(b, par[b], 0);
        }
    }
}