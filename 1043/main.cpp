#include "bits/stdc++.h"
using namespace std;

struct UF {
    vector<int> par;
    void init(int N) {
        par.resize(N+1);
        for (int i = 0; i <= N; i++) par[i] = i;
    }
    int find(int u) {
        return (u == par[u]) ? u : par[u] = find(par[u]);
    }
    int merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        par[v] = u;
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    UF uf; uf.init(N);
    int t; cin >> t;
    vector<int> chk(N);
    for (int i = 0; i < t; i++) {
        int x; cin >> x; x--;
        chk[x] = 1;
    }
    vector<vector<int>> party(M);
    for (int i = 0; i < M; i++) {
        cin >> t;
        for (int j = 0; j < t; j++) {
            int x; cin >> x; x--;
            party[i].push_back(x);
        }
        for (int j = 1; j < t; j++) {
            uf.merge(party[i][0], party[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        if (chk[i]) chk[uf.find(i)] = 1;
    }
    int ans = 0;
    for (int i = 0; i < M; i++) {
        int flag = 1;
        for (int j = 0; j < party[i].size(); j++) if (chk[uf.find(party[i][j])]) flag = 0;
        if (flag) ans++;
    }
    cout << ans << "\n";
}