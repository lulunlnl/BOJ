#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int MAX = 100005;
vector<int> g[MAX];
int in[MAX], out[MAX], pv;

void dfs(int v) {
    in[v] = ++pv;
    for (auto next: g[v]) {
        dfs(next);
    }
    out[v] = pv;
}

ll lazy[4*MAX], tree[4*MAX];
void push(int node, int s, int e) {
    if (!lazy[node]) return;
    tree[node] = (e - s + 1) * (lazy[node] == 1 ? 1 : 0);
    if (s != e) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
    }
    lazy[node] = 0;
}

void seg_update(int node, int s, int e, int l, int r, ll val) {
    push(node, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        lazy[node] = val;
        push(node, s, e);
        return;
    }
    int m = s + e >> 1;
    seg_update(node << 1, s, m, l, r, val);
    seg_update(node << 1 | 1, m + 1, e, l, r, val);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

ll query(int node, int s, int e, int l, int r) {
    push(node, s, e);
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        if (i == 1) continue;
        g[x].push_back(i);
    }
    dfs(1);
    seg_update(1, 1, N, in[1], out[1], 1);
    cin >> M;
    while (M--) {
        int op, i; cin >> op >> i;
        if (op == 1) seg_update(1, 1, N, in[i]+1, out[i], 1);
        else if (op == 2) seg_update(1, 1, N, in[i]+1, out[i], -1);
        else cout << query(1, 1, N, in[i]+1, out[i]) << "\n";
    }
}