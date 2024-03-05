#include "bits/stdc++.h"
using namespace std;

struct Point {
    double x, y, z;
};

double dist(Point &a, Point &b) {
    double ret = (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z);
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<Point> P(N);
    double X = 0, Y = 0, Z = 0;
    double R, k = 0.1;
    for (int i = 0; i < N; i++) {
        cin >> P[i].x >> P[i].y >> P[i].z;
        X += P[i].x; Y += P[i].y; Z += P[i].z;
    }
    X /= N; Y /= N; Z /= N;
    for (int t = 0; t < 20000; t++) {
        int idx = 0; R = 0;
        for (int i = 0; i < N; i++) {
            Point O = {X, Y, Z};
            double now = dist(P[i], O);
            if (now > R) {
                R = now; idx = i;
            }
        }
        X += (P[idx].x-X)*k;
        Y += (P[idx].y-Y)*k;
        Z += (P[idx].z-Z)*k;
        k *= 0.999;
    }
    R = sqrt(R);
    cout << fixed << setprecision(2) << R << "\n";
}