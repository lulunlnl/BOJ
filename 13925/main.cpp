#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAX = 100005;
const int MOD = 1e9 + 7;
ll arr[MAX], tree[4*MAX], lazy[4*MAX][2];

ll init(int node, int s, int e) {
    if (s == e) return tree[node] = arr[s];
    int m = s + e >> 1;
    return tree[node] = (init(node*2, s, m) + init(node*2+1, m+1, e)) % MOD;
}

void update_lazy(int node, int s, int e) {
    if (lazy[node][0] == 1 && lazy[node][1] == 0) return;
    tree[node] = lazy[node][0] * tree[node] + (e-s+1) * lazy[node][1];
    tree[node] %= MOD;
    if (s != e) {
        for (auto child: {node*2, node*2+1}) {
            lazy[child][0] *= lazy[node][0];
            lazy[child][0] %= MOD;
            lazy[child][1] = lazy[node][0] * lazy[child][1] + lazy[node][1];
            lazy[child][1] %= MOD;
        }
    }
    lazy[node][0] = 1, lazy[node][1] = 0;
}

void update_range(int node, int s, int e, int l, int r, ll a, ll b) {
    update_lazy(node, s, e);
    if (l > e || r < s) return;
    if (l <= s && e <= r) {
        lazy[node][0] *= a; lazy[node][0] %= MOD;
        lazy[node][1] = a * lazy[node][1] + b; lazy[node][1] %= MOD;
        update_lazy(node, s, e);
        return;
    }
    int m = s + e >> 1;
    update_range(node*2, s, m, l, r, a, b);
    update_range(node*2+1, m+1, e, l, r, a, b);
    tree[node] = (tree[node*2] + tree[node*2+1]) % MOD;
}

ll query(int node, int s, int e, int l, int r) {
    update_lazy(node, s, e);
    if (l > e || r < s) return 0;
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return (query(node*2, s, m, l, r) + query(node*2+1, m+1, e, l, r)) % MOD;
}

void out(int N) {
    for (int i = 1; i <= N; i++) {
        cout << query(1, 1, N, i, i) << " ";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    init(1, 1, N);
    for (int i = 0; i < 4*MAX; i++) lazy[i][0] = 1, lazy[i][1] = 0;
    cin >> M;
    out(N);
    while (M--) {
        int op, x, y; ll v;
        cin >> op >> x >> y;
        if (op <= 3) cin >> v;
        if (op == 1) update_range(1, 1, N, x, y, 1, v);
        else if (op == 2) update_range(1, 1, N, x, y, v, 0);
        else if (op == 3) update_range(1, 1, N, x, y, 0, v);
        else cout << query(1, 1, N, x, y) << "\n";
        out(N);
    }
}