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
    if (!lazy1[node] && lazy2[node] == INF) return;
    if (lazy2[node] == INF) {
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
    lazy1[node] = 0;
    lazy2[node] = INF;
}

Node query(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l) return {INF, -INF, 0};
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return merge(query(node << 1, s, m, l, r), query(node << 1 | 1, m+1, e, l, r));
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

void div(int node, int s, int e, int l, int r, double d) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        if (floor((tree[node].mn / d)) == floor((tree[node].mx / d))) {
            lazy2[node] = floor((tree[node].mn / d));
            push(node, s, e);
            return;
        }
        if (tree[node].mn + 1 == tree[node].mx) {
            lazy1[node] = floor((tree[node].mx / d)) - tree[node].mx;
            push(node, s, e);
            return;
        }
    }
    int m = s + e >> 1;
    div(node << 1, s, m, l, r, d);
    div(node << 1 | 1, m+1, e, l, r, d);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N >> Q;
    fill(lazy2, lazy2+MAX, INF);
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        add(1, 0, N-1, i, i, x);
    }
    while (Q--) {
        int op, l, r; cin >> op >> l >> r;
        if (op == 1) {
            ll v; cin >> v;
            add(1, 0, N-1, l, r, v);
        }
        else if (op == 2) {
            double d; cin >> d;
            div(1, 0, N-1, l, r, d);
        }
        else if (op == 3) cout << query(1, 0, N-1, l, r).mn << "\n";
        else cout << query(1, 0, N-1, l, r).sum << "\n";
    }
}