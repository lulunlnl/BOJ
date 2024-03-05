#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;

ll ccw(Point a, Point b, Point c) {
    return (b.x-a.x)*(c.y-a.y) - (c.x-a.x)*(b.y-a.y);
}

vector<Point> Hull() {
    int N; cin >> N;
    vector<Point> U, D, v;
    for (int i = 0; i < N; i++) {
        int a, b; cin >> a >> b;
        v.push_back({a, b});
    }
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<Point> ans = Hull();
    cout << ans.size() << "\n";
}