#include <bits/stdc++.h>
using namespace std;
const int MAX = 500005;
const int inf = 1e9;
int tree[4 * MAX];

int update(int node, int s, int e, int idx, int val) {
    if (idx < s || idx > e) return tree[node];
    if (s == e) return tree[node] = val;
    int m = s + e >> 1;
    return tree[node] = min(update(node << 1, s, m, idx, val), update(node << 1 | 1, m + 1, e, idx, val));
}

int query(int node, int s, int e, int l, int r) {
    if (r < s || e < l) return inf;
    if (l <= s && e <= r) return tree[node];
    int m = s + e >> 1;
    return min(query(node << 1, s, m, l, r), query(node << 1 | 1, m + 1, e, l, r));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<array<int, 3>> arr(n + 1);
    for (int i = 1; i <= n; i++) { int x; cin >> x; arr[x][0] = i; }
    for (int i = 1; i <= n; i++) { int x; cin >> x; arr[x][1] = i; }
    for (int i = 1; i <= n; i++) { int x; cin >> x; arr[x][2] = i; }
    sort(arr.begin() + 1, arr.end());
    for (int i = 1; i <= n; i++) update(1, 1, n, i, inf);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (query(1, 1, n, 1, arr[i][1] - 1) > arr[i][2]) ans++;
        update(1, 1, n, arr[i][1], arr[i][2]);
    }
    cout << ans << "\n";
}