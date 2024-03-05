#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

int N, T;
vector<Point> arr;
vector<Point> dxy;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

ll dist(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

ll ROT(int t) {
    vector<Point> v;
    for (int i = 0; i < N; i++) {
        v.push_back({arr[i].x + dxy[i].x * t, arr[i].y + dxy[i].y * t});
    }
    sort(v.begin(), v.end());
    vector<Point> U, D;
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    ll ret = 0;
    for (int i = 0, j = D.size()-1; i + 1 < U.size() || j > 0;) {
        ret = max(ret, dist(U[i], D[j]));
        if (j == 0 || (U[i+1].y-U[i].y)*(D[j].x-D[j-1].x) > (D[j].y-D[j-1].y)*(U[i+1].x-U[i].x)) i++;
        else j--;
    }
    return ret;
}

int main() {
    cin >> N >> T;
    for (int i = 0; i < N; i++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        arr.push_back({a, b});
        dxy.push_back({c, d});
    }
    int lo = 0, hi = T;
    while (hi-lo > 2) {
        int p = (lo*2+hi)/3, q = (lo+hi*2)/3;
        if (ROT(p) <= ROT(q)) hi = q;
        else lo = p;
    }
    ll ans = 2e18;
    int idx = 0;
    for (int i = lo; i <= hi; i++) {
        if (ans > ROT(i)) {
            idx = i, ans = ROT(i);
        }
    }
    cout << idx << "\n" << ans << "\n";
}