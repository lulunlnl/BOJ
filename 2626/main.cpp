#include "bits/stdc++.h"
using namespace std;
constexpr long double eps = 1e-9, INF = 1e9;

struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {}

    friend Point operator + (const Point& p, const Point &q) {
        return Point(p.x + q.x, p.y + q.y);
    }
    friend Point operator - (const Point& p, const Point& q) {
        return Point(p.x - q.x, p.y - q.y);
    }
    friend Point operator * (const Point& p, const long double& k) {
        return Point(p.x * k, p.y * k);
    }
    Point& operator = (const Point& p) {
        x = p.x; y = p.y;
        return *this;
    }
    friend long double dot(const Point& p, const Point& q) {
        return p.x * q.x + p.y * q.y;
    }
    friend long double cross(const Point& p, const Point& q) {
        return p.x * q.y - p.y * q.x;
    }
    friend long double dist(const Point& p, const Point& q) {
        long double ret = (p-q).x*(p-q).x + (p-q).y*(p-q).y;
        ret = sqrt(ret);
        return ret;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<Point> P(N);
    long double X = 0, Y = 0, R, k = 0.1;
    for (int i = 0; i < N; i++) {
        cin >> P[i].x >> P[i].y;
        X += P[i].x; Y += P[i].y;
    }
    X /= N; Y /= N;
    for (int t = 0; t < 100000; t++) {
        int idx = 0; R = 0;
        for (int i = 0; i < N; i++) {
            long double now = dist(P[i], {X, Y});
            if (now > R) {
                R = now; idx = i;
            }
        }
        X += (P[idx].x-X)*k;
        Y += (P[idx].y-Y)*k;
        k *= 0.999;
    }
    cout << fixed << setprecision(2) << 2*R << "\n";
}