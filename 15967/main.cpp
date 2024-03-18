#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAX = 1000005;
ll tree[4*MAX], lazy[4*MAX];

void push(int node, int s, int e) {
    if (!lazy[node]) return;
    tree[node] += (e-s+1) * lazy[node];
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
    update(node << 1 | 1, m+1, e, l, r, val);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

ll query(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return query(node << 1, s, m, l, r) + query(node << 1 | 1, m+1, e, l, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q1, q2; cin >> n >> q1 >> q2;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        update(1, 1, n, i, i, x);
    }
    q1 += q2;
    while (q1--) {
        int op, s, e;
        cin >> op >> s >> e;
        if (op == 1) {
            cout << query(1, 1, n, s, e) << "\n";
        }
        else {
            ll I; cin >> I;
            update(1, 1, n, s, e, I);
        }
    }
}