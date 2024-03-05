#include "bits/stdc++.h"
using namespace std;
int num[10005], low[10005];
bool chk[10005];
int cnt = 0;
vector<int> g[10005];
stack<int> s;
vector<vector<int>> SCC;

void GetSCC(int now) {
    s.push(now);
    num[now] = ++cnt;
    low[now] = cnt;
    for (auto next: g[now]) {
        if (!num[next]) {
            GetSCC(next);
            low[now] = min(low[now], low[next]);
        }
        else if (!chk[next]) low[now] = min(low[now], num[next]);
    }
    if (low[now] == num[now]) {
        vector<int> scc;
        while (!s.empty()) {
            int t = s.top(); s.pop();
            scc.push_back(t);
            chk[t] = 1;
            if (t == now) break;
        }
        sort(scc.begin(), scc.end());
        SCC.push_back(scc);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int V, E; cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= V; i++) {
        if (!num[i]) GetSCC(i);
    }
    cout << SCC.size() << "\n";
    sort(SCC.begin(), SCC.end());
    for (auto v: SCC) {
        for (auto e: v) cout << e << " ";
        cout << "-1\n";
    }
}