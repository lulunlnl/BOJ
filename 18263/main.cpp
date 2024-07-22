#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int sn;

struct Query {
    int idx, s, e, c;
    bool operator < (const Query &O) {
        if (s / sn != O.s / sn) return s / sn < O.s / sn;
        return e < O.e;
    }
};

vector<int> adj[100005], g[100005];
int dep[100005], sz[100005], in[100005], par[100005], top[100005];
int color[100005], cnt[100005], res[100005], v[100005];

void dfs(int now = 1, int prev = 0) {
    for (auto next: adj[now]) {
        if (next == prev) continue;
        g[now].push_back(next);
        dfs(next, now);
    }
}

void dfs1(int now = 1) {
    sz[now] = 1;
    for (auto &next: g[now]) {
        dep[next] = dep[now] + 1; par[next] = now;
        dfs1(next);
        sz[now] += sz[next];
        if (sz[next] > sz[g[now][0]]) swap(next, g[now][0]);
    }
}

int pv;
void dfs2(int now = 1) {
    in[now] = ++pv;
    for (auto next: g[now]) {
        top[next] = (next == g[now][0] ? top[now] : next);
        dfs2(next);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    sn = (int)sqrt(n);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    top[1] = 1;
    dfs(); dfs1(); dfs2();
    for (int i = 1; i <= n; i++) color[in[i]] = v[i];
    vector<Query> Q;
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) swap(a, b);
            int st = top[a];
            Q.push_back({i, in[st], in[a], c});
            a = par[st];
        }
        if (in[a] > in[b]) swap(a, b);
        Q.push_back({i, in[a], in[b], c});
    }
    sort(Q.begin(), Q.end());
    int l = 0, r = 0;
    for (auto [idx, s, e, c]: Q) {
        while (l > s) cnt[color[--l]]++;
        while (l < s) cnt[color[l++]]--;
        while (r < e) cnt[color[++r]]++;
        while (r > e) cnt[color[r--]]--;
        if (cnt[c]) res[idx] = 1;
    }
    for (int i = 0; i < m; i++) cout << res[i];
}