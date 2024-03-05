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
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    vector<Point> ans;
    for (int i = 0; i + 1 < D.size(); i++) ans.push_back(D[i]);
    for (int i = U.size()-1; i >= 1; i--) ans.push_back(U[i]);
    return ans;
}

int in_hull(vector<Point>& hull, Point p) {
    int n = hull.size();
    if (n < 3) return 0;
    for (int i = 0; i < n; i++) {
        if (ccw(hull[i], p, hull[(i+1)%n]) > 0) return 0;
        if (ccw(hull[i], p, hull[(i+1)%n]) == 0) return -1;
    }
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; Point P;
    cin >> N >> P.x >> P.y;
    vector<Point> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;
    int ans = 0;
    vector<bool> chk(N, 0);
    while (1) {
        vector<Point> tmp;
        for (int i = 0; i < N; i++) {
            if (!chk[i]) tmp.push_back(v[i]);
        }
        vector<Point> hull = Hull(tmp);
        if (!in_hull(hull, P)) break;
        ans++;
        for (int i = 0; i < N; i++) {
            if (in_hull(hull, v[i]) == -1) chk[i] = 1;
        }
    }
    cout << ans << "\n";
}