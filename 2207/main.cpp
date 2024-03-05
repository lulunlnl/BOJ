#include "bits/stdc++.h"
using namespace std;
const int MAX = 20005;
int num[MAX], low[MAX], SN[MAX];
bool chk[MAX];
int pv, sz;
vector<int> g[MAX];
stack<int> s;
vector<vector<int>> SCC;

void GetSCC(int now) {
    s.push(now);
    num[now] = ++pv;
    low[now] = pv;
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
            chk[t] = 1; SN[t] = sz;
            if (t == now) break;
        }
        sz++;
        sort(scc.begin(), scc.end());
        SCC.push_back(scc);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> M >> N;
    for (int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        if (a > 0) a *= 2;
        else a = a*(-2) + 1;
        if (b > 0) b *= 2;
        else b = b*(-2) + 1;

        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
    }
    for (int i = 2; i <= 2*N+1; i++) {
        if (!num[i]) GetSCC(i);
    }
    for (int i = 1; i <= N; i++) {
        if (SN[i*2] == SN[i*2+1]) {
            cout << "OTL"; return 0;
        }
    }
    cout << "^_^";
}