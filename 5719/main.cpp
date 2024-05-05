#include <bits/stdc++.h>
using namespace std;
constexpr int inf = 2e9;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (1) {
        int n, m; cin >> n >> m;
        if (!n && !m) break;
        int s, d; cin >> s >> d;
        vector<pair<int, int>> adj[n], rev[n];
        for (int i = 0; i < m; i++) {
            int u, v, p; cin >> u >> v >> p;
            adj[u].push_back({v, p});
            rev[v].push_back({u, p});
        }
        vector<int> d1(n, inf), d2(n, inf), d3(n, inf);

        d1[s] = 0, d2[d] = 0;
        priority_queue<pair<int, int>> PQ;
        PQ.push({0, s});
        while (!PQ.empty()) {
            auto [cost, now] = PQ.top(); PQ.pop();
            cost = -cost;
            for (auto [next, next_cost]: adj[now]) {
                next_cost += cost;
                if (next_cost < d1[next]) {
                    d1[next] = next_cost;
                    PQ.push({-next_cost, next});
                }
            }
        }
        PQ.push({0, d});
        while (!PQ.empty()) {
            auto [cost, now] = PQ.top(); PQ.pop();
            cost = -cost;
            for (auto [next, next_cost]: rev[now]) {
                next_cost += cost;
                if (next_cost < d2[next]) {
                    d2[next] = next_cost;
                    PQ.push({-next_cost, next});
                }
            }
        }

        d3[s] = 0;
        PQ.push({0, s});
        while (!PQ.empty()) {
            auto [cost, now] = PQ.top(); PQ.pop();
            cost = -cost;
            for (auto [next, next_cost]: adj[now]) {
                if (d1[now] + next_cost + d2[next] == d1[d]) continue;
                next_cost += cost;
                if (next_cost < d3[next]) {
                    d3[next] = next_cost;
                    PQ.push({-next_cost, next});
                }
            }
        }
        cout << (d3[d] == inf ? -1 : d3[d]) << "\n";
    }
}