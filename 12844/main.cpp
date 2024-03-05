#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

ll init(vll &arr, vll &tree, int node, int s, int e) {
    if (s == e) return tree[node] = arr[s];
    int m = s + e >> 1;
    return tree[node] = init(arr, tree, node*2, s, m) ^ init(arr, tree, node*2+1, m+1, e);
}

void update_lazy(vll &tree, vll &lazy, int node, int s, int e) {
    if (!lazy[node]) return;
    tree[node] ^= ((e - s + 1) % 2) * lazy[node];
    if (s != e) {
        lazy[node*2] ^= lazy[node];
        lazy[node*2+1] ^= lazy[node];
    }
    lazy[node] = 0;
}

void update_range(vll &tree, vll &lazy, int node, int s, int e, int l, int r, ll diff) {
    update_lazy(tree, lazy, node, s, e);
    if (l > e || r < s) return;
    if (l <= s && e <= r) {
        tree[node] ^= ((e - s + 1) % 2) * diff;
        if (s != e) {
            lazy[node*2] ^= diff;
            lazy[node*2+1] ^= diff;
        }
        return;
    }
    int m = s + e >> 1;
    update_range(tree, lazy, node*2, s, m, l, r, diff);
    update_range(tree, lazy, node*2+1, m+1, e, l, r, diff);
    tree[node] = tree[node*2] ^ tree[node*2+1];
}

ll query(vll &tree, vll &lazy, int node, int s, int e, int l, int r) {
    update_lazy(tree, lazy, node, s, e);
    if (l > e || r < s) return 0;
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return query(tree, lazy, node*2, s, m, l, r) ^ query(tree, lazy, node*2+1, m+1, e, l, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    int h = (int)ceil(log2(N)) + 1;
    int sz = 1 << h;
    vll arr(N), tree(sz), lazy(sz);
    for (int i = 0; i < N; i++) cin >> arr[i];
    init(arr, tree, 1, 0, N-1);
    cin >> M;
    while (M--) {
        int op, a, b; ll c;
        cin >> op >> a;
        if (op == 1) {
            cin >> b >> c;
            update_range(tree, lazy, 1, 0, N-1, a, b, c);
        }
        else cout << query(tree, lazy, 1, 0, N-1, a, a) << "\n";
    }
}