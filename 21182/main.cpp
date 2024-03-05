#include "bits/stdc++.h"
using namespace std;
constexpr double eps = 1e-9, INF = 1e9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    friend Point operator + (const Point& p, const Point &q) {
        return Point(p.x + q.x, p.y + q.y);
    }
    friend Point operator - (const Point& p, const Point& q) {
        return Point(p.x - q.x, p.y - q.y);
    }
    friend Point operator * (const Point& p, const double& k) {
        return Point(p.x * k, p.y * k);
    }
    Point& operator = (const Point& p) {
        x = p.x; y = p.y;
        return *this;
    }
    friend double dot(const Point& p, const Point& q) {
        return p.x * q.x + p.y * q.y;
    }
    friend double cross(const Point& p, const Point& q) {
        return p.x * q.y - p.y * q.x;
    }
    friend double dist(const Point& p, const Point& q) {
        double ret = (p-q).x*(p-q).x + (p-q).y*(p-q).y;
        ret = sqrt(ret);
        return ret;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<double> x(N), y(N), z(N);
    for (int i = 0; i < N; i++) {
        cin >> x[i] >> y[i] >> z[i];
    }
    double ret = INF;
    for (int j = 0; j < 3; j++) {
        vector<Point> P(N);
        double X = 0, Y = 0, R, k = 0.1;
        if (j == 0) {
            for (int i = 0; i < N; i++) {
                P[i] = {x[i], y[i]};
                X += P[i].x;
                Y += P[i].y;
            }
        }
        else if (j == 1) {
            for (int i = 0; i < N; i++) {
                P[i] = {y[i], z[i]};
                X += P[i].x;
                Y += P[i].y;
            }
        }
        else {
            for (int i = 0; i < N; i++) {
                P[i] = {z[i], x[i]};
                X += P[i].x;
                Y += P[i].y;
            }
        }
        X /= N;
        Y /= N;
        for (int t = 0; t < 20000; t++) {
            int idx = 0;
            R = 0;
            for (int i = 0; i < N; i++) {
                double now = dist(P[i], {X, Y});
                if (now > R) {
                    R = now;
                    idx = i;
                }
            }
            X += (P[idx].x - X) * k;
            Y += (P[idx].y - Y) * k;
            k *= 0.999;
        }
        ret = min(ret, 2*R);
    }
    cout << fixed << setprecision(5) << ret;
}