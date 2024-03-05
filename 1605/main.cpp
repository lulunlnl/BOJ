#include "bits/stdc++.h"
using namespace std;
int L; string S;
int pos[200005], sa[200005], lcp[200005];

void GetSA() {
    for (int i = 0; i < L; i++) {
        pos[i] = S[i];
        sa[i] = i;
    }
    for (int d = 1; ; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (pos[i] != pos[j]) return pos[i] < pos[j];
            i += d; j += d;
            if (i >= L || j >= L) return i > j;
            return pos[i] < pos[j];
        };
        sort(sa, sa + L, cmp);
        vector<int> tmp(L, 0);
        for (int i = 0; i < L - 1; i++) {
            tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i + 1]);
        }
        for (int i = 0; i < L; i++) pos[sa[i]] = tmp[i];
        if (tmp[L-1] == L-1) break;
    }
}

void GetLCP() {
    for (int i = 0, k = 0; i < L; i++, k = max(0, k-1)) {
        if (pos[i] == L-1) continue;
        for (int j = sa[pos[i] + 1]; S[i+k] == S[j+k]; k++) ;
        lcp[pos[i]] = k;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> L >> S;
    GetSA();
    GetLCP();
    int ans = 0;
    for (int i = 0; i < L - 1; i++) ans = max(ans, lcp[i]);
    cout << ans << "\n";
}