#include "bits/stdc++.h"
using namespace std;

struct SCC {
    vector<int> num, low, SN;
    vector<bool> chk;
    int cnt, sz;
    vector<vector<int>> g, ans;
    stack<int> s;

    void init(int V) {
        num.clear(); num.resize(V+1, 0);
        low.clear(); low.resize(V+1, 0);
        chk.clear(); chk.resize(V+1, 0);
        SN.clear(); SN.resize(V+1, 0);
        cnt = 0, sz = 0;
        g.clear(); g.resize(V+1, vector<int>());
        ans.clear();
        while (!s.empty()) s.pop();
    }

    void dfs(int now) {
        s.push(now);
        num[now] = ++cnt; low[now] = cnt;
        for (auto next: g[now]) {
            if (!num[next]) {
                dfs(next);
                low[now] = min(low[now], low[next]);
            }
            else if (!chk[next]) low[now] = min(low[now], num[next]);
        }
        if (low[now] == num[now]) {
            vector<int> scc;
            while (!s.empty()) {
                int t = s.top(); s.pop();
                scc.push_back(t);
                chk[t] = 1; SN[t] = sz;
                if (t == now) break;
            }
            sz++;
            sort(scc.begin(), scc.end());
            ans.push_back(scc);
        }
    }

    void GetSCC(int V) {
        for (int i = 1; i <= V; i++) {
            if (!num[i]) dfs(i);
        }
        sort(ans.begin(), ans.end());
    }
} scc;

void solve() {
    int N, M; cin >> N >> M;
    scc.init(N);
    for (int i = 0; i < M; i++) {
        int x, y; cin >> x >> y;
        scc.g[x].push_back(y);
    }
    scc.GetSCC(N);
    vector<int> in(scc.sz, 0);
    for (int i = 1; i <= N; i++) {
        for (int j: scc.g[i]) {
            if (scc.SN[i] != scc.SN[j]) in[scc.SN[j]]++;
        }
    }
    int ret = 0;
    for (int i = 0; i < scc.sz; i++) {
        if (in[i] == 0) ret++;
    }
    cout << ret << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) solve();
}