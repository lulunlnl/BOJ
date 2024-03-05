#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int sqrtN, N, K;
int cnt[100005];
ll ret;

struct Query {
    int idx, s, e;
    bool operator < (const Query &O) const {
        if (s/sqrtN != O.s/sqrtN) return s/sqrtN < O.s/sqrtN;
        return e < O.e;
    }
};

struct Fenwick {
    vector<ll> tree;
    int sz;
    void init(int N) {
        tree.resize(N+1);
        sz = N;
    }
    void update(int i, ll v) {
        while (i <= sz) {
            tree[i] += v;
            i += i & -i;
        }
    }
    ll sum(int i) {
        ll ans = 0;
        while (i > 0) {
            ans += tree[i];
            i -= i & -i;
        }
        return ans;
    }
} fen;

void Plus(int x) {
    ret += fen.sum(min(100000, x+K)) - fen.sum(max(0, x-K-1));
    fen.update(x, 1);
}

void Minus(int x) {
    fen.update(x, -1);
    ret -= fen.sum(min(100000, x+K)) - fen.sum(max(0, x-K-1));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> K;
    vector<int> A(N+1);
    fen.init(1e5);
    sqrtN = (int)sqrt(N);
    for (int i = 1; i <= N; i++) cin >> A[i];
    int M; cin >> M;
    vector<Query> Q;
    for (int i = 0; i < M; i++) {
        int l, r; cin >> l >> r;
        Q.push_back({i, l, r});
    }
    sort(Q.begin(), Q.end());
    vector<ll> ans(M);
    int s = Q[0].s, e = s-1;
    for (int i = 0; i < M; i++) {
        while (s < Q[i].s) Minus(A[s++]);
        while (s > Q[i].s) Plus(A[--s]);
        while (e < Q[i].e) Plus(A[++e]);
        while (e > Q[i].e) Minus(A[e--]);
        ans[Q[i].idx] = ret;
    }
    for (int i = 0; i < M; i++) cout << ans[i] << "\n";
}