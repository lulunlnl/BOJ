#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> Point;
int N, M;
ll res_x = 1e9, res_y = 1e9;
vector<pair<int, int>> MST;

struct Edge {
    int u, v, x, y;
};
Edge E[10005];

ll CCW(const Point& A, const Point& B, const Point& C) {
    return (B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x);
}

int par[205], sz[205];

void init(int n) {
    for (int i = 0; i <= n; i++) par[i] = i, sz[i] = 1;
}
int find(int v) {
    if (v == par[v]) return v;
    return par[v] = find(par[v]);
}

bool merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return false;
    par[u] = v;
    sz[v] += sz[u]; sz[u] = sz[v];
    return true;
}

// dy/dx = slope
Point Optimize(ll dy, ll dx) {
    init(204);
    ll X = 0, Y = 0;
    // ax + by 기준 정렬
    sort(E+1, E+M+1, [&](const Edge &a, const Edge &b) {
        return dy*a.x + dx*a.y < dy*b.x + dx*b.y;
    });
    vector<pair<int, int>> ret;
    for (int i = 1; i <= M; i++) {
        if (merge(E[i].u, E[i].v)) {
            X += E[i].x; Y += E[i].y;
            ret.push_back({E[i].u, E[i].v});
        }
    }
    if (res_x * res_y > X * Y) {
        res_x = X; res_y = Y;
        MST = ret;
    }
    return {X, Y};
}

void solve(Point left, Point bottom) {
    Point pt = Optimize(left.y - bottom.y, bottom.x - left.x);
    if (CCW(left, pt, bottom) > 0) {
        solve(left, pt); solve(pt, bottom);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 1; i <= M; i++) cin >> E[i].u >> E[i].v >> E[i].x >> E[i].y;
    Point left = Optimize(1, 0), bottom = Optimize(0, 1);
    solve(left, bottom);
    cout << res_x << " " << res_y << "\n\n";
    for (int i = 0; i < MST.size(); i++) {
        cout << MST[i].x << " " << MST[i].y << "\n";
    }
}