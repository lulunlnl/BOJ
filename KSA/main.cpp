#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string S; cin >> S;
    string a = "KSA";
    int N = S.size();
    if (N == 1) {
        if (S[0] == 'K') cout << 0;
        else cout << 2;
        return 0;
    }
    if (N == 2) {
        if (S == "KS") cout << 0;
        else if (S == "AA") cout << 4;
        else cout << 2;
        return 0;
    }
    int ret = 2*N, cur = 0;
    int tmp = 0, cnt = 0;
    for (int i = 0; i < N; i++) {
        if (a[cur] == S[i]) {
            cur = (cur+1)%3;
        }
        else {
            cnt++;
        }
    }
    ret = min(ret, 2*cnt);

    tmp = 0, cnt = 0, cur = 1;
    for (int i = 0; i < N; i++) {
        if (a[cur] == S[i]) {
            cur = (cur+1)%3;
        }
        else {
            cnt++;
        }
    }
    if (!cnt) cnt = 1;
    ret = min(ret, 2*cnt);

    tmp = 0, cnt = 0, cur = 2;
    for (int i = 0; i < N; i++) {
        if (a[cur] == S[i]) {
            cur = (cur+1)%3;
        }
        else {
            cnt++;
        }
    }
    if (cnt <= 1) cnt++;
    ret = min(ret, cnt*2);
    cout << ret << "\n";
}