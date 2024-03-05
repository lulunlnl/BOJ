#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

double dist(Point a, Point b, Point p) {
    if (a.x == b.x) {
        return abs(p.x-a.x);
    }
    double A = (b.y-a.y)/(double)(b.x-a.x), B = -1, C = a.y - a.x*A;
    return abs(A*p.x+B*p.y+C)/sqrt(A*A+B*B);
}

void ROT() {
    int N; ll R; cin >> N >> R;
    vector<Point> v(N, {0, 0});
    for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;
    vector<Point> U, D;
    sort(v.begin(), v.end());
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    double ret = 2e18;
    for (int i = 0, j = D.size()-1; i + 1 < U.size() || j > 0;) {
        if ((i + 1 != U.size()) &&
        (j == 0 || (U[i+1].y - U[i].y) * (D[j].x - D[j-1].x) > (D[j].y - D[j-1].y) * (U[i+1].x - U[i].x))) {
            ret = min(ret, dist(U[i], U[i+1], D[j])); i++;
        }
        else {
            ret = min(ret, dist(D[j-1], D[j], U[i])); j--;
        }
    }
    cout << fixed << setprecision(10) << ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ROT();
}