#include "bits/stdc++.h"
using namespace std;
vector<int> g[32005];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<int> indegree(N+1);
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        indegree[b]++;
    }
    priority_queue<int> PQ;
    for (int i = 1; i <= N; i++) {
        if (!indegree[i]) PQ.push(-i);
    }
    while (!PQ.empty()) {
        int t = -PQ.top(); PQ.pop();
        cout << t << " ";
        for (auto next: g[t]) {
            indegree[next]--;
            if (!indegree[next]) PQ.push(-next);
        }
    }
}