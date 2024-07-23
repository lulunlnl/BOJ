#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int l, r, val;
};

int head[100005];
vector<Node> tree(2);

void init() {
    tree.resize(2);
    tree[1] = {0, 0, 0};
    fill(head, head + 100005, 0);
    head[0] = 1;
}

void seg_init(int node, int s, int e) {
    if (s == e) return;
    int m = s + e >> 1;
    tree.push_back({0, 0, 0});
    tree[node].l = tree.size() - 1;
    seg_init(tree[node].l, s, m);
    tree.push_back({0, 0, 0});
    tree[node].r = tree.size() - 1;
    seg_init(tree[node].r, m + 1, e);
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

int query(int node, int s, int e, int l, int r) {
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node].val;
    int m = s + e >> 1;
    return query(tree[node].l, s, m, l, r) + query(tree[node].r, m + 1, e, l, r);
}

void solve() {
    init();
    seg_init(1, 1, 100001);
    int n, m; cin >> n >> m;
    vector<int> yidx[100005];
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        x++; y++;
        yidx[x].push_back(y);
    }
    for (int i = 1; i <= 100001; i++) {
        if (head[i] == 0) {
            tree.push_back({tree[head[i - 1]].l, tree[head[i - 1]].r, tree[head[i - 1]].val});
            head[i] = tree.size() - 1;
        }
        for (auto y: yidx[i]) {
            tree[head[i]].val += 1;
            update(head[i], 1, 100001, y, 1);
        }
    }
    ll ret = 0;
    while (m--) {
        int l, r, b, t; cin >> l >> r >> b >> t;
        l++; r++; b++; t++;
        ret += query(head[r], 1, 100001, b, t) - query(head[l - 1], 1, 100001, b, t);
    }
    cout << ret << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}