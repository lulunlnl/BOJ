#include "bits/stdc++.h"
using namespace std;

struct UF {
    vector<int> par;
    void init(int N) {
        par.resize(N);
        for (int i = 0; i < N; i++) {
            par[i] = i;
        }
    }
    int find(int u) {
        return (u == par[u]) ? u : par[u] = find(par[u]);
    }
    int merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        par[u] = v;
        return 1;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    UF uf; uf.init(N);
    for (int i = 1; i <= M; i++) {
        int a, b; cin >> a >> b;
        if (!uf.merge(a, b)) {
            cout << i;
            return 0;
        }
    }
    cout << "0\n";
}