#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll INF = 2e18;
const int MAX = 1 << 17 + 1;

struct Node {
    ll mn, mx, sum;
};

ll lazy1[4*MAX], lazy2[4*MAX];
// lazy1: x add, lazy2: 모든 값을 x로
Node tree[4*MAX];

Node merge(Node a, Node b) {
    return {min<ll>(a.mn, b.mn), max<ll>(a.mx, b.mx), a.sum+b.sum};
}

void push(int node, int s, int e) {
    if (!lazy1[node] && !lazy2[node]) return;
    if (lazy2[node] == 0) {
        tree[node].mn += lazy1[node];
        tree[node].mx += lazy1[node];
        tree[node].sum += (e-s+1) * lazy1[node];
        if (s != e) {
            lazy1[node << 1] += lazy1[node];
            lazy1[node << 1 | 1] += lazy1[node];
        }
    }
    else {
        tree[node].mn = tree[node].mx = lazy1[node] + lazy2[node];
        tree[node].sum = (e-s+1) * (lazy1[node] + lazy2[node]);
        if (s != e) {
            lazy1[node << 1] = lazy1[node];
            lazy2[node << 1] = lazy2[node];
            lazy1[node << 1 | 1] = lazy1[node];
            lazy2[node << 1 | 1] = lazy2[node];
        }
    }
    lazy1[node] = lazy2[node] = 0;
}

ll query(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node].sum;
    int m = s + e >> 1;
    return query(node << 1, s, m, l, r) + query(node << 1 | 1, m+1, e, l, r);
}

void add(int node, int s, int e, int l, int r, ll v) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        lazy1[node] += v;
        push(node, s, e);
        return;
    }
    int m = s + e >> 1;
    add(node << 1, s, m, l, r, v);
    add(node << 1 | 1, m+1, e, l, r, v);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

void root(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        if ((ll)sqrt(tree[node].mn) == (ll)sqrt(tree[node].mx)) {
            lazy2[node] = (ll)sqrt(tree[node].mn);
            push(node, s, e);
            return;
        }
        if (tree[node].mn + 1 == tree[node].mx) {
            lazy1[node] = (ll)sqrt(tree[node].mx) - tree[node].mx;
            push(node, s, e);
            return;
        }
    }
    int m = s + e >> 1;
    root(node << 1, s, m, l, r);
    root(node << 1 | 1, m+1, e, l, r);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    for (int i = 1; i <= N; i++) {
        ll x; cin >> x;
        add(1, 1, N, i, i, x);
    }
    cin >> M;
    while (M--) {
        int op, l, r; cin >> op >> l >> r;
        if (op == 1) {
            ll v; cin >> v;
            add(1, 1, N, l, r, v);
        }
        else if (op == 2) root(1, 1, N, l, r);
        else cout << query(1, 1, N, l, r) << "\n";
    }
}