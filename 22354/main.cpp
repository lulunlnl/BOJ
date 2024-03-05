#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; string S; cin >> N >> S;
    vector<int> a(N), b;
    int M = 0, chk = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        if (i == 0) continue;
        if (S[i-1] != S[i]) {
            if (!chk) chk = 1;
            else b.push_back(M);
            M = a[i];
        }
        else {
            M = max(M, a[i]);
        }
    }
    sort(b.rbegin(), b.rend());
    ll ret = 0;
    for (int i = 0; i < (b.size()+1)/2; i++) {
        ret += b[i];
    }
    cout << ret << "\n";
}