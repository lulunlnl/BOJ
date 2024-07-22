#include <bits/stdc++.h>
#define ft first
#define sd second
using namespace std;
typedef long long ll;

struct Node {
    ll lmx, rmx, mx, sum;
    Node() {lmx = rmx = mx = sum = 0;}
    Node(ll lmx, ll rmx, ll mx, ll sum): lmx(lmx), rmx(rmx), mx(mx), sum(sum) {}

    Node operator + (const Node& node) const {
        return {max(lmx, sum + node.lmx), max(node.rmx, rmx + node.sum), max({mx, node.mx, rmx + node.lmx}), sum + node.sum};
    };

    void add(int val) {lmx += val; rmx += val; mx += val; sum += val;}
};

struct Seg {
    Node tree[20005];

    void init() {
        for (int i = 0; i < 20005; i++) tree[i] = {0, 0, 0, 0};
    }

    void update(int node, int s, int e, int idx, ll val) {
        if (idx < s || idx > e) return;
        if (s == e) {
            tree[node].add(val);
            return;
        }
        int m = s + e >> 1;
        update(node << 1, s, m, idx, val);
        update(node << 1 | 1, m + 1, e, idx, val);
        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    Node query(int node, int s, int e, int l, int r) {
        if (r < s || e < l) return Node();
        if (l <= s && e <= r) return tree[node];
        int m = s + e >> 1;
        return query(node << 1, s, m, l, r) + query(node << 1 | 1, m + 1, e, l, r);
    }
} seg;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<pair<int, int>, ll>> arr(n);
    vector<int> x, y;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].ft.sd >> arr[i].ft.ft >> arr[i].sd;
        x.push_back(arr[i].ft.sd);
        y.push_back(arr[i].ft.ft);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    y.erase(unique(y.begin(), y.end()), y.end());
    for (int i = 0; i < n; i++) {
        arr[i].ft.sd = lower_bound(x.begin(), x.end(), arr[i].ft.sd) - x.begin();
        arr[i].ft.ft = lower_bound(y.begin(), y.end(), arr[i].ft.ft) - y.begin();
    }
    sort(arr.begin(), arr.end());

    ll ret = 0;
    for (int i = 0; i < n; i++) {
        if (i != 0 && arr[i - 1].ft.ft == arr[i].ft.ft) continue;
        seg.init();
        for (int j = i; j < n; j++) {
            seg.update(1, 0, n - 1, arr[j].ft.sd, arr[j].sd);
            if (j == n - 1 || arr[j].ft.ft != arr[j + 1].ft.ft) ret = max(ret, seg.query(1, 0, n - 1, 0, n - 1).mx);
        }
    }
    cout << ret;
}