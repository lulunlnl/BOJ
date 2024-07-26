#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
int g;

struct Query {
    int s, e, idx;
    bool operator < (Query &O) {
        if (s / g != O.s / g) return s / g < O.s / g;
        return e < O.e;
    }
};

struct SegTree {
    int tree[1 << 19];
    int sz = 1 << 18;

    void update(int x, int v) {
        x |= sz; tree[x] += v;
        while (x >>= 1) {
            tree[x] = tree[x << 1] + tree[x << 1 | 1];
        }
    }

    int query(int l, int r) {
        l |= sz; r |= sz;
        int ret = 0;
        while (l <= r) {
            if (l & 1) ret += tree[l++];
            if (~r & 1) ret += tree[r--];
            l >>= 1; r >>= 1;
        }
        return ret;
    }
} seg;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    g = (int)sqrt(n);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];
    auto c = arr;
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    for (int i = 0; i < n; i++) c[i] = lower_bound(arr.begin(), arr.end(), c[i]) - arr.begin();

    vector<Query> Q;
    for (int i = 0; i < m; i++) {
        int s, e; cin >> s >> e;
        s--; e--;
        Q.push_back({s, e, i});
    }
    sort(Q.begin(), Q.end());

    vector<long long> ans(m);
    int l = 0, r = -1;
    long long ret = 0;
    for (auto [s, e, idx]: Q) {
        while (l > s) {
            ret += seg.query(0, c[--l] - 1);
            seg.update(c[l], 1);
        }
        while (l < s) {
            ret -= seg.query(0, c[l] - 1);
            seg.update(c[l++], -1);
        }
        while (r < e) {
            ret += seg.query(c[++r] + 1, n - 1);
            seg.update(c[r], 1);
        }
        while (r > e) {
            ret -= seg.query(c[r] + 1, n - 1);
            seg.update(c[r--], -1);
        }
        ans[idx] = ret;
    }
    for (int i = 0; i < m; i++) cout << ans[i] << "\n";
}