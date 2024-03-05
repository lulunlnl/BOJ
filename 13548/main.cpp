#include "bits/stdc++.h"
using namespace std;

int sqrtN, ret;
int cnt[100005], num[100005];

struct Query {
    int idx, s, e;
    bool operator < (const Query &O) const {
        if (s/sqrtN != O.s/sqrtN) return s/sqrtN < O.s/sqrtN;
        return e < O.e;
    }
};
vector<Query> Q;

void Plus(int x) {
    if (cnt[x] != 0) num[cnt[x]]--;
    num[++cnt[x]]++;
    if (cnt[x] > ret) ret = cnt[x];
}

void Minus(int x) {
    if (--num[cnt[x]] == 0 && ret == cnt[x]) ret--;
    num[--cnt[x]]++;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N;
    sqrtN = (int)sqrt(N);
    vector<int> A(N+1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    cin >> M;
    for (int i = 0; i < M; i++) {
        int l, r; cin >> l >> r;
        Q.push_back({i, l, r});
    }
    sort(Q.begin(), Q.end());
    vector<int> ans(M);
    int s = 0, e = 0;
    for (int i = 0; i < M; i++) {
        while (Q[i].s < s) Plus(A[--s]);
        while (s < Q[i].s) Minus(A[s++]);
        while (Q[i].e < e) Minus(A[e--]);
        while (e < Q[i].e) Plus(A[++e]);
        ans[Q[i].idx] = ret;
    }
    for (int i = 0; i < M; i++) cout << ans[i] << "\n";
}