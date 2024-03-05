#include "bits/stdc++.h"
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<string> arr;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        arr.push_back(S);
    }
    int K; cin >> K;
    int mx = 0;
    vector<int> chk(N, 0);
    for (int i = 0; i < N; i++) {
        if (chk[i]) continue;
        int zero = 0;
        for (int j = 0; j < M; j++) {
            zero += (arr[i][j] == '0');
        }
        if (zero > K) continue;
        if ((K - zero) % 2 == 1) continue;
        int cnt = 1;
        for (int j = i + 1; j < N; j++) {
            if (arr[i] == arr[j]) {
                cnt++;
                chk[j] = 1;
            }
        }
        mx = max(mx, cnt);
    }
    cout << mx << "\n";
}