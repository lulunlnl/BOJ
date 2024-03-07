#include "bits/stdc++.h"
using namespace std;
int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char dir[4] = {'R', 'L', 'U', 'D'};

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
    int N, M; cin >> N >> M;
    UF uf; uf.init(2000000);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char c; cin >> c;
            int x = i, y = j;
            if (c == 'D') x++;
            else if (c == 'U') x--;
            else if (c == 'L') y--;
            else y++;
            uf.merge(x*M+y, i*M+j);
        }
    }
    int ans = 0;
    vector<int> chk(2000000);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (chk[uf.find(i*M+j)]) continue;
            chk[uf.find(i*M+j)] = 1;
            ans++;
        }
    }
    cout << ans << "\n";
}