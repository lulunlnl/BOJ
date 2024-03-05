#include "bits/stdc++.h"
using namespace std;
int pos[500005], sa[500005], lcp[500005];

void GetSA(string& S) {
    int N = S.size();
    for (int i = 0; i < N; i++) {
        sa[i] = i;
        pos[i] = S[i];
    }
    for (int d = 1; ; d <<= 1) {
        auto cmp = [&](int i, int j) {
            if (pos[i] != pos[j]) return pos[i] < pos[j];
            i += d; j += d;
            if (i >= N || j >= N) return i > j;
            return pos[i] < pos[j];
        };
        sort(sa, sa + N, cmp);
        vector<int> tmp(N, 0);
        for (int i = 0; i < N - 1; i++) {
            tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i+1]);
        }
        for (int i = 0; i < N; i++) pos[sa[i]] = tmp[i];
        if (tmp[N-1] == N-1) break;
    }
}

void GetLCP(string& S) {
    int N = S.size();
    for (int i = 0, k = 0; i < N; i++, k = max(0, k-1)) {
        if (pos[i] == N-1) continue;
        for (int j = sa[pos[i]+1]; S[i+k] == S[j+k]; k++);
        lcp[pos[i]] = k;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    GetSA(S); GetLCP(S);
    for (int i = 0; i < S.size(); i++) cout << sa[i] + 1 << " ";
    cout << "\nx ";
    for (int i = 0; i < S.size() - 1; i++) cout << lcp[i] << " ";
}