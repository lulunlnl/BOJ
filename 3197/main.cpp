#include "bits/stdc++.h"
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

struct UF {
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

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C; cin >> R >> C;
    vector<vector<char>> arr(R, vector<char>(C));
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> arr[i][j];
        }
    }

}