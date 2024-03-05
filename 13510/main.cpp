#include "bits/stdc++.h"
using namespace std;
const int MAX = 100005;
int sz[MAX], dep[MAX], par[MAX], top[MAX], in[MAX], out[MAX];
vector<int> g[MAX];
vector<int> adj[MAX];
int chk[MAX], pv, s[MAX], e[MAX], we[MAX];

struct Seg {
    int tree[1 << 18];
    int sz = 1 << 17;

    void update(int x, int v) {
        x |= sz; tree[x] = v;
        while (x >>= 1) {
            tree[x] = max(tree[x << 1], tree[x << 1 | 1]);
        }
    }

    int query(int l, int r) {
        l |= sz, r |= sz;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret = max(ret, tree[l++]);
            if (~r & 1) ret = max(ret, tree[r--]);
            l >>= 1, r >>= 1;
        }
        return ret;
    }
} seg;

void dfs(int v = 1) {
    chk[v] = 1;
    for (auto i: adj[v]) {
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

void update(int idx, int val) {
    if (dep[s[idx]] < dep[e[idx]]) swap(s[idx], e[idx]);
    seg.update(in[s[idx]], val);
}

int query(int a, int b) {
    int ret = 0;
    while (top[a] != top[b]) {
        if (dep[top[a]] < dep[top[b]]) swap(a, b);
        int st = top[a];
        ret = max(ret, seg.query(in[st], in[a]));
        a = par[st];
    }
    if (dep[a] > dep[b]) swap(a, b);
    ret = max(ret, seg.query(in[a] + 1, in[b]));
    return ret;
}

int main(void) {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b, w; cin >> a >> b >> w;
        s[i] = a, e[i] = b, we[i] = w;
        adj[a].push_back(b); adj[b].push_back(a);
    }
    top[1] = 1;
    dfs(); dfs1(); dfs2();

    for (int i = 1; i < N; i++) {
        update(i, we[i]);
    }

    cin >> Q;
    while (Q--) {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) update(a, b);
        else cout << query(a, b) << "\n";
    }
}