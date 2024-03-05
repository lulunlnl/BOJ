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

struct SegTree {
    ll lazy[4*MAX], tree[4*MAX];
    void push(int node, int s, int e) {
        if (!lazy[node]) return;
        tree[node] += (e - s + 1) * lazy[node];
        if (s != e) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    void seg_update(int node, int s, int e, int l, int r, ll diff) {
        push(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            lazy[node] += diff;
            push(node, s, e);
            return;
        }
        int m = s + e >> 1;
        seg_update(node << 1, s, m, l, r, diff);
        seg_update(node << 1 | 1, m + 1, e, l, r, diff);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    ll query(int node, int s, int e, int l, int r) {
        push(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
    }
} up, down;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int x; cin >> x;
        if (i == 1) continue;
        g[x].push_back(i);
    }
    dfs(1);

    bool flag = 0;
    while (M--) {
        int op, i; ll w;
        cin >> op;
        if (op == 1) {
            cin >> i >> w;
            if (!flag) down.seg_update(1, 1, N, in[i], out[i], w);
            else up.seg_update(1, 1, N, in[i], in[i], w);
        }
        else if (op == 2) {
            cin >> i;
            cout << down.query(1, 1, N, in[i], in[i]) + up.query(1, 1, N, in[i], out[i]) << "\n";
        }
        else flag ^= 1;
    }
}