#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r, val;
};

int head[100005];
vector<Node> tree(2);

vector<int> adj[100005], w(100005);
int dep[100005], par[100005][20], rev[100005], n;

void init(int node, int s, int e) {
    if (s == e) return;
    int m = s + e >> 1;
    tree.push_back({0, 0, 0});
    tree[node].l = tree.size() - 1;
    init(tree[node].l, s, m);
    tree.push_back({0, 0, 0});
    tree[node].r = tree.size() - 1;
    init(tree[node].r, m + 1, e);
}

void update(int node, int s, int e, int idx, int val) {
    if (s == e) return;
    int m = s + e >> 1;
    if (idx <= m) {
        int lidx = tree[node].l;
        tree.push_back({tree[lidx].l, tree[lidx].r, tree[lidx].val + val});
        tree[node].l = tree.size() - 1;
        update(tree[node].l, s, m, idx, val);
    }
    else {
        int ridx = tree[node].r;
        tree.push_back({tree[ridx].l, tree[ridx].r, tree[ridx].val + val});
        tree[node].r = tree.size() - 1;
        update(tree[node].r, m + 1, e, idx, val);
    }
}

int query(int n1, int n2, int n3, int n4, int s, int e, int k) {
    if (s == e) return s;
    int cnt = tree[tree[n1].l].val + tree[tree[n2].l].val - tree[tree[n3].l].val - tree[tree[n4].l].val;
    int m = s + e >> 1;
    if (k <= cnt) return query(tree[n1].l, tree[n2].l, tree[n3].l, tree[n4].l, s, m, k);
    else return query(tree[n1].r, tree[n2].r, tree[n3].r, tree[n4].r, m + 1, e, k - cnt);
}

void dfs(int now, int prev) {
    if (prev != 0) tree.push_back({tree[head[prev]].l, tree[head[prev]].r, tree[head[prev]].val});
    head[now] = tree.size() - 1;
    tree[head[now]].val += 1;
    update(head[now], 1, n, w[now], 1);
    for (auto next: adj[now]) {
        if (next == prev) continue;
        dep[next] = dep[now] + 1;
        par[next][0] = now;
        dfs(next, now);
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int diff = dep[a] - dep[b];
    for (int i = 0; diff; i++) {
        if (diff & 1) a = par[a][i];
        diff >>= 1;
    }
    if (a == b) return a;
    for (int i = 19; i >= 0; i--) {
        if (par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    }
    return par[a][0];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int m; cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i], w[i + 1] = arr[i];
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    auto real = w;
    for (int i = 0; i < n; i++) {
        w[i + 1] = lower_bound(arr.begin(), arr.end(), w[i + 1]) - arr.begin() + 1;
        rev[w[i + 1]] = i + 1;
    }
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    tree[1] = {0, 0, 0};
    head[0] = 1;
    init(1, 1, n);
    dfs(1, 0);
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }

    while (m--) {
        int x, y, k; cin >> x >> y >> k;
        int z = lca(x, y);
        int ret = query(head[x], head[y], head[z], (par[z][0] == 0 ? 0 : head[par[z][0]]), 1, n, k);
        cout << real[rev[ret]] << "\n";
    }
}