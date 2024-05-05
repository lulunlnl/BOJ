#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<pair<int, int>> adj[n + 1], rev[n + 1];
    vector<int> indegree(n + 1), dist(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b, c});
        rev[b].push_back({a, c});
        indegree[b]++;
    }
    int s, e; cin >> s >> e;
    queue<int> Q;
    Q.push(s);
    while (!Q.empty()) {
        int now = Q.front(); Q.pop();
        for (auto [next, cost]: adj[now]) {
            dist[next] = max(dist[next], dist[now] + cost);
            if (--indegree[next] == 0) Q.push(next);
        }
    }
    int cnt = 0;
    vector<int> chk(n + 1);
    Q.push(e); chk[e] = 1;
    while (!Q.empty()) {
        int now = Q.front(); Q.pop();
        for (auto [next, cost]: rev[now]) {
            if (dist[next] == dist[now] - cost) {
                cnt++;
                if (!chk[next]) {
                    chk[next] = 1;
                    Q.push(next);
                }
            }
        }
    }
    cout << dist[e] << "\n" << cnt;
}