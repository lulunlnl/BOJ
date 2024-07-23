#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int tree[800005];

    void init() {
        for (int i = 0; i < 800005; i++) tree[i] = 0;
    }

    void update(int node, int s, int e, int idx, int val) {
        if (idx < s || idx > e) return;
        if (s == e) {
            tree[node] += val;
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, idx, val);
        update(node << 1 | 1, m + 1, e, idx, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    int query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
    }
} seg;

void solve() {
    int n, m; cin >> n >> m;
    seg.init();
    vector<int> idx(n + 1);
    for (int i = 1; i <= n; i++) {
        idx[i] = m + i;
        seg.update(1, 1, m + n, idx[i], 1);
    }
    int now = m;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        cout << seg.query(1, 1, m + n, 1, idx[x] - 1) << " ";
        seg.update(1, 1, m + n, idx[x], -1);
        idx[x] = now--;
        seg.update(1, 1, m + n, idx[x], 1);
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}