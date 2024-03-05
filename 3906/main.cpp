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
};

struct HalfPlane {
    // p: 지나는 점, d: 방향 벡터
    Point p, d;
    double angle;

    HalfPlane() {}
    HalfPlane(const Point& a, const Point& b) : p(a), d(b - a) {
        angle = atan2(d.y, d.x);
    }
    // 점 r이 반평면 밖인지 판별, 반평면: 선분의 왼쪽
    bool out(const Point& r) {
        return cross(d, r - p) < -eps;
    }
    bool operator < (const HalfPlane& e) {
        return angle < e.angle;
    }
    friend Point inter(const HalfPlane& s, const HalfPlane& t) {
        double alpha = cross((t.p - s.p), t.d) / cross(s.d, t.d);
        return s.p + (s.d * alpha);
    }
};

vector<Point> HP_inter(vector<HalfPlane> &H) {
    Point box[4] = {
            Point(INF, INF),
            Point(-INF, INF),
            Point(-INF, -INF),
            Point(INF, -INF)
    };
    for (int i = 0; i < 4; i++) {
        HalfPlane tmp(box[i], box[(i+1)%4]);
        H.push_back(tmp);
    }
    sort(H.begin(), H.end());

    deque<HalfPlane> dq;
    int sz = 0;
    for (int i = 0; i < H.size(); i++) {
        while (sz >= 2 && H[i].out(inter(dq[sz-1], dq[sz-2]))) {
            dq.pop_back(); sz--;
        }
        while (sz >= 2 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front(); sz--;
        }
        // 예외 처리: 평행한 경우
        if (sz > 0 && fabs(cross(H[i].d, dq[sz-1].d)) < eps) {
            if (dot(H[i].d, dq[sz-1].d) < 0) return vector<Point> ();
            if (H[i].out(dq[sz-1].p)) {
                dq.pop_back(); sz--;
            }
            else continue;
        }
        dq.push_back(H[i]); sz++;
    }

    while (sz >= 2 && dq[0].out(inter(dq[sz-1], dq[sz-2]))) {
        dq.pop_back(); sz--;
    }
    while (sz >= 2 && dq[sz-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front(); sz--;
    }
    if (sz < 3) return vector<Point> ();
    vector<Point> ret(sz);
    for (int i = 0; i < sz-1; i++) {
        ret[i] = inter(dq[i], dq[i+1]);
    }
    ret[sz-1] = inter(dq[sz-1], dq[0]);
    return ret;
}

void solve(int N) {
    vector<Point> P(N);
    for (int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;
    vector<HalfPlane> Edge;
    for (int i = 0; i < N; i++) Edge.push_back(HalfPlane(P[i], P[(i+1)%N]));
    vector<Point> ret = HP_inter(Edge);
    if (ret.empty()) cout << "0\n";
    else cout << "1\n";
}

int main() {
    int N;
    while (1) {
        cin >> N; if (!N) break;
        solve(N);
    }
}