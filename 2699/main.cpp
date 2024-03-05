#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

void solve() {
    int N; cin >> N;
    vector<Point> v(N), U, D;
    for (int i = 0; i < N; i++) {
        cin >> v[i].x >> v[i].y;
    }
    sort(v.begin(), v.end());
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    int sz = U.size() + D.size() - 2;
    cout << sz << "\n";
    int idx = 0, M = 0;
    for (int i = 0; i < U.size(); i++) {
        if (U[i].y > M) M = U[i].y, idx = i;
    }
    for (int i = idx; i < U.size(); i++) cout << U[i].x << " " << U[i].y << "\n";
    for (int i = D.size()-2; i > 0; i--) cout << D[i].x << " " << D[i].y << "\n";
    for (int i = 0; i < idx; i++) cout << U[i].x << " " << U[i].y << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}