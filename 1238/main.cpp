#include "bits/stdc++.h"
#define ft first
#define sd second
using namespace std;
typedef pair<int, int> pii;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M, X; cin >> N >> M >> X;
    X--;
    vector<vector<pii>> g1(N), g2(N);
    for (int i = 0; i < M; i++) {
        int a, b, T; cin >> a >> b >> T;
        a--; b--;
        g1[a].push_back({b, T});
        g2[b].push_back({a, T});
    }
    priority_queue<pii> PQ;
    vector<int> D1(N, 1e9), D2(N, 1e9);
    D1[X] = 0; D2[X] = 0;
    PQ.push({0, X});
    while (!PQ.empty()) {
        auto [cost, now] = PQ.top();
        cost = -cost; PQ.pop();
        if (cost > D1[now]) continue;
        for (auto next: g1[now]) {
            if (next.sd + cost < D1[next.ft]) {
                D1[next.ft] = next.sd + cost;
                PQ.push({-(next.sd + cost), next.ft});
            }
        }
    }
    PQ.push({0, X});
    while (!PQ.empty()) {
        auto [cost, now] = PQ.top();
        cost = -cost; PQ.pop();
        if (cost > D2[now]) continue;
        for (auto next: g2[now]) {
            if (next.sd + cost < D2[next.ft]) {
                D2[next.ft] = next.sd + cost;
                PQ.push({-(next.sd + cost), next.ft});
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans = max(ans, D1[i] + D2[i]);
    }
    cout << ans << "\n";
}