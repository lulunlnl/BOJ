#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dist[100005];
int par[100005];

int find(int x) {
    if (x == par[x]) return x;
    int p = find(par[x]);
    dist[x] += dist[par[x]];
    return par[x] = p;
}

bool merge(int a, int b, ll w) {
    int ra = find(a), rb = find(b);
    if (ra == rb) return 0;
    dist[rb] = dist[a] + w - dist[b];
    par[rb] = par[ra];
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        int n, m; cin >> n >> m;
        if (!n && !m) break;
        fill(dist, dist + 100005, 0);
        iota(par, par + 100005, 0);
        for (int i = 0; i < m; i++) {
            char op; int a, b;
            cin >> op >> a >> b;
            if (op == '?') {
                if (find(a) != find(b)) {
                    cout << "UNKNOWN\n";
                }
                else {
                    cout << dist[b] - dist[a] << "\n";
                }
            }
            else {
                ll w; cin >> w;
                merge(a, b, w);
            }
        }
    }
}