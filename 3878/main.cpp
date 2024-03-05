#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

vector<Point> Hull(vector<Point>& v) {
    int n = v.size();
    vector<Point> U, D;
    sort(v.begin(), v.end());
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) > 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) < 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    vector<Point> ans;
    if (D.size() == 1) {
        ans.push_back(D[0]);
        return ans;
    }
    for (int i = 0; i + 1 < D.size(); i++) ans.push_back(D[i]);
    for (int i = U.size()-1; i >= 1; i--) ans.push_back(U[i]);
    return ans;
}

bool in_hull(vector<Point>& hull, Point p) {
    int n = hull.size();
    if (n < 3) return 0;
    for (int i = 0; i < n; i++) {
        if (ccw(hull[i], p, hull[(i+1)%n]) > 0) return 0;
    }
    return 1;
}

bool is_cross(Point a, Point b, Point c, Point d) {
    ll ans1 = ccw(a, b, c) * ccw(a, b, d);
    ll ans2 = ccw(c, d, a) * ccw(c, d, b);
    if (ans1 == 0 && ans2 == 0) {
        if (a > b) swap(a, b);
        if (c > d) swap(c, d);
        if (a <= d && b >= c) return 1;
        return 0;
    }
    if (ans1 <= 0 && ans2 <= 0) return 1;
    return 0;
}

bool is_on_line(Point a, Point b, Point p) {
    if (ccw(a, b, p)) return 0;
    if (a > b) swap(a, b);
    if (a <= p && p <= b) return 1;
    return 0;
}

void solve() {
    int N, M; cin >> N >> M;
    vector<Point> black(N), white(M);
    for (int i = 0; i < N; i++) cin >> black[i].x >> black[i].y;
    for (int i = 0; i < M; i++) cin >> white[i].x >> white[i].y;
    vector<Point> a, b;
    a = Hull(black), b = Hull(white);
    N = a.size(), M = b.size();
    if (N > M) swap(N, M), swap(a, b);
    if (M <= 2) {
        if (M == 1) cout << "YES\n";
        else if (N == 1) {
            if (is_on_line(b[0], b[1], a[0])) cout << "NO\n";
            else cout << "YES\n";
        }
        else {
            if (is_cross(a[0], a[1], b[0], b[1])) cout << "NO\n";
            else cout << "YES\n";
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            if (in_hull(b, a[i])) {
                cout << "NO\n";
                return;
            }
        }
        for (int i = 0; i < M; i++) {
            if (in_hull(a, b[i])) {
                cout << "NO\n";
                return;
            }
        }
        cout << "YES\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}