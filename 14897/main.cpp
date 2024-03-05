#pragma GCC optimize ("O3")
#include "bits/stdc++.h"
using namespace std;

int sqrtN;
int cnt[1000005];

struct Query {
    int idx, s, e;
    bool operator < (const Query &O) const {
        if (s/sqrtN != O.s/sqrtN) return s/sqrtN < O.s/sqrtN;
        return e < O.e;
    }
};

vector<Query> Q;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    sqrtN = (int)sqrt(N);
    vector<int> A(N+1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    vector<int> tmp = A;
    sort(tmp.begin()+1, tmp.end());
    tmp.erase(unique(tmp.begin()+1, tmp.end()), tmp.end());
    for (int i = 1; i <= N; i++) A[i] = lower_bound(tmp.begin(), tmp.end(), A[i]) - tmp.begin();
    cin >> M;
    for (int i = 0; i < M; i++) {
        int l, r; cin >> l >> r;
        Q.push_back({i, l, r});
    }
    sort(Q.begin(), Q.end());
    vector<int> ans(M);
    int ret = 0, s = Q[0].s, e = Q[0].e;
    for (int i = s; i <= e; i++) {
        if (cnt[A[i]]++ == 0) ret++;
    }
    ans[Q[0].idx] = ret;
    for (int i = 1; i < M; i++) {
        while (s > Q[i].s) if (cnt[A[--s]]++ == 0) ret++;
        while (s < Q[i].s) if (--cnt[A[s++]] == 0) ret--;
        while (e > Q[i].e) if (--cnt[A[e--]] == 0) ret--;
        while (e < Q[i].e) if (cnt[A[++e]]++ == 0) ret++;
        ans[Q[i].idx] = ret;
    }
    for (int i = 0; i < M; i++) cout << ans[i] << "\n";
}