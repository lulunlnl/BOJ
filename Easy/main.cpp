#include <bits/stdc++.h>
using namespace std;
const int MAX = 2000000;

int tree[4 * MAX + 5];

void update(int node, int s, int e, int idx, int val) {
    if (idx < s || idx > e) return;
    if (s == e) {
        tree[node] += val;
        return;
    }
    int m = s + e >> 1;
    update(node << 1, s, m, idx, val);
    update(node << 1 | 1, m + 1, e, idx, val);
    tree[node] = tree[node << 1] + tree[node << 1 | 1];
}

int query(int node, int s, int e, int k) {
    if (s == e) return s;
    int m = s + e >> 1;
    if (k <= tree[node << 1]) return query(node << 1, s, m, k);
    else return query(node << 1 | 1, m + 1, e, k - tree[node << 1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    while (n--) {
        int op, v;
        cin >> op >> v;
        if (op == 1) update(1, 1, MAX, v, 1);
        else {
            int t = query(1, 1, MAX, v);
            cout << t << "\n";
            update(1, 1, MAX, t, -1);
        }
    }
}