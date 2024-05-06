#include <bits/stdc++.h>
using namespace std;
int tree[400005];

int update(int node, int s, int e, int idx, int val) {
    if (idx < s || idx > e) return tree[node];
    if (s == e) return tree[node] = val;
    int m = s + e >> 1;
    return tree[node] = update(node << 1, s, m, idx, val) + update(node << 1 | 1, m + 1, e, idx, val);
}

int query(int node, int s, int e, int val) {
    if (s == e) return s;
    int m = s + e >> 1;
    if (val >= tree[node << 1 | 1]) return query(node << 1, s, m, val - tree[node << 1 | 1]);
    else return query(node << 1 | 1, m + 1, e, val);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) update(1, 0, n - 1, i, 1);
    vector<int> ans(n), a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = n - 1; i >= 0; i--) {
        int t = query(1, 0, n - 1, a[i]);
        update(1, 0, n - 1, t, 0);
        ans[t] = i;
    }
    for (int i = 0; i < n; i++) cout << ans[i] + 1 << " ";
}