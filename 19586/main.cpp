#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

Point operator + (Point a, Point b) {
    return {a.x+b.x, a.y+b.y};
}

Point operator - (Point a, Point b) {
    return {a.x-b.x, a.y-b.y};
}

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

ll ccw(Point a, Point b) {
    return a.x*b.y - b.x*a.y;
}

ll dot(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}

double dist(Point a, Point b) {
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

double line_dist(Point a, Point b, Point d) {
    double ret = abs(ccw(b-a, d)) / dist(a, a+d);
    return ret;
}

void solve() {
    int N; cin >> N;
    vector<Point> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;
    vector<Point> U, D;
    sort(v.begin(), v.end());
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    vector<Point> hull;
    for (int i = 0; i + 1 < D.size(); i++) hull.push_back(D[i]);
    for (int i = U.size()-1; i > 0; i--) hull.push_back(U[i]);
    N = hull.size();
    if (N == 2) {
        cout << 2*dist(hull[0], hull[1]) << "\n"; return;
    }
    double ret = 2e18;
    int r1 = 1, r2 = 1, r3 = 1;
    for (int i = 0; i < N; i++) {
        if (r1 % N == i) r1++;
        if (r2 % N == i) r2++;
        if (r3 % N == i) r3++;

        while (ccw(hull[(i+1)%N]-hull[i], hull[(r1+1)%N]-hull[r1%N]) > 0 &&
               dot(hull[(i+1)%N]-hull[i], hull[(r1+1)%N]-hull[r1%N]) > 0) r1++;
        while (ccw(hull[(i+1)%N]-hull[i], hull[(r2+1)%N]-hull[r2%N]) > 0) r2++;
        while (ccw(hull[(i+1)%N]-hull[i], hull[(r3+1)%N]-hull[r3%N]) > 0 ||
               dot(hull[(i+1)%N]-hull[i], hull[(r3+1)%N]-hull[r3%N]) < 0) r3++;
        Point d = hull[(i+1)%N] - hull[i];
        ret = min(ret, line_dist(hull[i], hull[r2%N], d) + line_dist(hull[r1%N], hull[r3%N], {d.y, -d.x}));
    }
    ret *= 2;
    cout << ret << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);
    solve();
}