#include "bits/stdc++.h"
using namespace std;

struct UnionFind {
    vector<int> par, sz;

    void init(int N) {
        par.resize(N+1);
        sz.resize(N+1);
        for (int i = 0; i <= N; i++) par[i] = i, sz[i] = 1;
    }

    int find(int v) {
        return (v == par[v]) ? v : (par[v] = find(par[v]));
    }

    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        par[u] = v;
        sz[v] += sz[u]; sz[u] = sz[v];
        return true;
    }
};

struct Edge {
    int u, v, w;
    Edge(): Edge(-1, -1, 0) {}
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    bool operator < (const Edge &O) {
        return w < O.w;
    }
};

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int arr[105][105], chk[105][105];
int N, M;
vector<pair<int, int>> v[11];
vector<Edge> E;

void dfs(int x, int y, int t) {
    chk[x][y] = t;
    v[t].push_back({x, y});
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M || !arr[nx][ny] || chk[nx][ny]) continue;
        dfs(nx, ny, t);
    }
}

void f(int x, int y, int dir) {
    int cnt = 0, k = chk[x][y];
    while (1) {
        x += dx[dir]; y += dy[dir];
        cnt++;
        if (x < 0 || x >= N || y < 0 || y >= M || chk[x][y] == k) break;
        if (!chk[x][y]) continue;
        if (cnt-1 != 1) E.push_back({k, chk[x][y], cnt-1});
        break;
    }
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> arr[i][j];
    }
    int t = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (arr[i][j] && !chk[i][j]) dfs(i, j, ++t);
        }
    }
    for (int i = 0; i < t; i++) {
        for (auto e: v[i]) {
            for (int d = 0; d < 4; d++) f(e.first, e.second, d);
        }
    }
    UnionFind UF; UF.init(11);
    sort(E.begin(), E.end());
    int ret = 0, cnt = 0;
    for (int i = 0; i < E.size(); i++) {
        if (UF.merge(E[i].u, E[i].v)) {
            ret += E[i].w;
            cnt++;
        }
    }
    if (cnt != t-1) cout << -1;
    else cout << ret;
}