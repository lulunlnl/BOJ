#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

ll dist(Point a, Point b) {
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}

void ROT() {
    int N; cin >> N;
    vector<Point> v(N, {0, 0});
    for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;
    vector<Point> U, D;
    sort(v.begin(), v.end());
    for (auto i: v) {
        while (U.size() >= 2 && ccw(U[U.size()-2], U.back(), i) >= 0) U.pop_back();
        while (D.size() >= 2 && ccw(D[D.size()-2], D.back(), i) <= 0) D.pop_back();
        U.push_back(i); D.push_back(i);
    }
    ll ret = 0;
    for (int i = 0, j = D.size()-1; i + 1 < U.size() || j > 0;) {
        ret = max(ret, dist(U[i], D[j]));
        if ((i+1 != U.size()) &&
            (j == 0 || (U[i+1].y - U[i].y) * (D[j].x - D[j-1].x) > (D[j].y - D[j-1].y) * (U[i+1].x - U[i].x))) i++;
        else j--;
    }
    cout << ret << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ROT();
}