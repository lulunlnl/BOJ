#include <bits/stdc++.h>
using namespace std;
int par[300005], chk[300005];

int find(int x) {
    return (x == par[x]) ? x : par[x] = find(par[x]);
}

bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return 0;
    par[v] = u;
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, l; cin >> n >> l;
    iota(par + 1, par + l + 1, 1);
    for (int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        if (!chk[a]) {
            cout << "LADICA\n";
            chk[a] = 1;
            merge(b, a);
            continue;
        }
        if (!chk[b]) {
            cout << "LADICA\n";
            chk[b] = 1;
            merge(a, b);
            continue;
        }
        if (!chk[find(a)]) {
            cout << "LADICA\n";
            chk[find(a)] = 1;
            merge(b, a);
            continue;
        }
        if (!chk[find(b)]) {
            cout << "LADICA\n";
            chk[find(b)] = 1;
            merge(b, a);
            continue;
        }
        cout << "SMECE\n";
    }
}