#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

vector<int> y;
pll tree[1600005];

void update(int node, int s, int e, int l, int r, int val) {
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        tree[node].second += val;
    }
    else {
        int m = s + e >> 1;
        update(node << 1, s, m, l, r, val);
        update(node << 1 | 1, m + 1, e, l, r, val);
    }
    if (tree[node].second) {
        tree[node].first = y[e] - y[s - 1];
    }
    else {
        if (s == e) tree[node].first = 0;
        else tree[node].first = tree[node << 1].first + tree[node << 1 | 1].first;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<array<int, 4>> Points, arr;
    vector<int> ycor;
    ycor.push_back(-2e9);
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        arr.push_back({x1, x2, y1, y2});
        ycor.push_back(y1); ycor.push_back(y2);
    }
    sort(ycor.begin(), ycor.end());
    ycor.erase(unique(ycor.begin(), ycor.end()), ycor.end());
    y = ycor;

    for (int i = 0; i < n; i++) {
        int y1 = lower_bound(ycor.begin(), ycor.end(), arr[i][2]) - ycor.begin();
        int y2 = lower_bound(ycor.begin(), ycor.end(), arr[i][3]) - ycor.begin();
        Points.push_back({arr[i][0], y1, y2, 1});
        Points.push_back({arr[i][1], y1, y2, -1});
    }
    sort(Points.begin(), Points.end());

    ll ret = 0, last = 0;
    for (int i = 0; i < 2 * n; i++) {
        auto [x, l, r, val] = Points[i];
        ll dx = x - last;
        ret += dx * tree[1].first;
        update(1, 1, 400001, l + 1, r, val);
        last = x;
    }
    cout << ret;
}