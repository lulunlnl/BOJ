#include <bits/stdc++.h>
using namespace std;
typedef unsigned int ll;

struct Seg {
    ll tree[2000005], lazy[2000005][2];

    void push(int node, int s, int e) {
        if (lazy[node][0] == 1 && lazy[node][1] == 0) return;
        tree[node] = lazy[node][0] * tree[node] + (e - s + 1) * lazy[node][1];
        if (s != e) {
            for (auto child: {node << 1, node << 1 | 1}) {
                lazy[child][0] *= lazy[node][0];
                lazy[child][1] = lazy[node][0] * lazy[child][1] + lazy[node][1];
            }
        }
        lazy[node][0] = 1, lazy[node][1] = 0;
    }

    void update(int node, int s, int e, int l, int r, ll a, ll b) {
        push(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[node][0] *= a;
            lazy[node][1] = a * lazy[node][1] + b;
            push(node, s, e);
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, l, r, a, b);
        update(node << 1 | 1, m + 1, e, l, r, a, b);
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

vector<int> adj[500005], g[500005];
int sz[500005], dep[500005], par[500005], top[500005], in[500005], out[500005];
int n, q;

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
        dep[next] = dep[now] + 1;
        par[next] = now;
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

void update(int u, int v, ll a, ll b) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        seg.update(1, 1, n, in[st], in[u], a, b);
        u = par[st];
    }
    if (in[u] > in[v]) swap(u, v);
    seg.update(1, 1, n, in[u], in[v], a, b);
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
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    top[1] = 1;
    dfs(); dfs1(); dfs2();

    while (q--) {
        int op, x, y; ll v;
        cin >> op;
        if (op == 1) {
            cin >> x >> v;
            seg.update(1, 1, n, in[x], out[x], 1, v);
        }
        else if (op == 2) {
            cin >> x >> y >> v;
            update(x, y, 1, v);
        }
        else if (op == 3) {
            cin >> x >> v;
            seg.update(1, 1, n, in[x], out[x], v, 0);
        }
        else if (op == 4) {
            cin >> x >> y >> v;
            update(x, y, v, 0);
        }
        else if (op == 5) {
            cin >> x;
            cout << seg.query(1, 1, n, in[x], out[x]) << "\n";
        }
        else {
            cin >> x >> y;
            cout << query(x, y) << "\n";
        }
    }
}