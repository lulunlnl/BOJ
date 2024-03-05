#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
constexpr ll INF = 2e18;
constexpr int MAX = 100005;
int N, Q;

struct Node {
    ll lmx, rmx, mx, sum;
    Node() {lmx = rmx = mx = sum = 0;}
    Node(ll lmx, ll rmx, ll mx, ll sum): lmx(lmx), rmx(rmx), mx(mx), sum(sum) {}
    Node operator + (const Node& node) const{
        return {max<ll>({lmx, sum + node.lmx, 0}), max<ll>({node.rmx, node.sum + rmx, 0}),
                max<ll>({mx, node.mx, rmx + node.lmx, 0}), sum + node.sum};
    }
    void set(ll v) {lmx = rmx = mx = max<ll>(v, 0); sum = v;}
};

ll arr[MAX];

struct SegTree {
    Node tree[1 << 20];
    ll lazy[1 << 20];

    void update_lazy(int node, int s, int e) {
        if (lazy[node] == -INF) return;
        tree[node].set((e-s+1)*lazy[node]);
        if (s != e) {
            lazy[node*2] = lazy[node];
            lazy[node*2+1] = lazy[node];
        }
        lazy[node] = -INF;
    }

    void update(int node, int s, int e, int l, int r, ll v) {
        update_lazy(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[node] = v;
            update_lazy(node, s, e);
            return;
        }
        int m = s + e >> 1;
        update(node*2, s, m, l, r, v);
        update(node*2+1, m+1, e, l, r, v);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    Node query(int node, int s, int e, int l, int r) {
        update_lazy(node, s, e);
        if (r < s || e < l) return Node();
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node*2, s, m, l, r) + query(node*2+1, m+1, e, l, r);
    }
};

ll sz[MAX], dep[MAX], par[MAX], top[MAX], in[MAX], out[MAX];
vector<ll> g[MAX], adj[MAX];
ll s[MAX], e[MAX];

struct HLD {
    int chk[MAX], pv;
    SegTree seg;

    void init() {
        fill(seg.lazy, seg.lazy+(1<<20), -INF);
        top[1] = 1;
        dfs(); dfs1(); dfs2();
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

    void update(int a, int b, ll val) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            int st = top[a];
            seg.update(1, 1, N, in[st], in[a], val);
            a = par[st];
        }
        if (dep[a] > dep[b]) swap(a, b);
        seg.update(1, 1, N, in[a], in[b], val);
    }

    ll query(int a, int b) {
        Node left, right;
        if (in[a] > in[b]) swap(a, b);
        while (top[a] != top[b]) {
            if (dep[top[a]] > dep[top[b]]) {
                int st = top[a];
                left = seg.query(1, 1, N, in[st], in[a]) + left;
                a = par[st];
            }
            else {
                int st = top[b];
                right = seg.query(1, 1, N, in[st], in[b]) + right;
                b = par[st];
            }
        }
        if (dep[a] > dep[b]) left = seg.query(1, 1, N, in[b], in[a]) + left;
        else right = seg.query(1, 1, N, in[a], in[b]) + right;
        swap(left.lmx, left.rmx);
        return (left + right).mx;
    }
} hld;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < N-1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    hld.init();
    for (int i = 1; i <= N; i++) hld.update(i, i, arr[i]);
    cin >> Q;
    while (Q--) {
        int op, u, v; cin >> op >> u >> v;
        if (op == 1) {
            cout << hld.query(u, v) << "\n";
        }
        else {
            ll w; cin >> w;
            hld.update(u, v, w);
        }
    }
}