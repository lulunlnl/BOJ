#include "bits/stdc++.h"
using namespace std;
typedef pair<int, int> pii;
const int MAX = 1 << 17;
int arr[MAX+3];
pii tree[4*MAX+5];

pii merge(pii a, pii b) {
    int t[4] = {a.first, a.second, b.first, b.second};
    sort(t, t+4);
    return {t[3], t[2]};
}

pii init(int node, int s, int e) {
    if (s == e) return tree[node] = {arr[s], 0};
    int m = s + e >> 1;
    return tree[node] = merge(init(node << 1, s, m), init(node << 1 | 1, m+1, e));
}

void update(int node, int s, int e, int idx, int val) {
    if (e < idx || s > idx) return;
    if (s == e) {
        tree[node] = {val, 0};
        return;
    }
    int m = s + e >> 1;
    update(node << 1, s, m, idx, val);
    update(node << 1 | 1, m+1, e, idx, val);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

pii query(int node, int s, int e, int l, int r) {
    if (r < s || e < l) return {0, 0};
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return merge(query(node << 1, s, m, l, r), query(node << 1 | 1, m+1, e, l, r));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    init(1, 1, N);
    cin >> M;
    while (M--) {
        int op, a, b; cin >> op >> a >> b;
        if (op == 1) update(1, 1, N, a, b);
        else {
            pii ans = query(1, 1, N, a, b);
            cout << ans.first + ans.second << "\n";
        }
    }
}