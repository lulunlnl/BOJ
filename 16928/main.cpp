#include "bits/stdc++.h"
using namespace std;
int mp[105], chk[105];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    for (int i = 0; i < N + M; i++) {
        int a, b; cin >> a >> b;
        mp[a] = b;
    }
    queue<int> Q;
    Q.push(1);
    while (!Q.empty()) {
        int x = Q.front(); Q.pop();
        if (x == 100) {
            cout << chk[100] << "\n";
            break;
        }
        for (int i = 1; i <= 6; i++) {
            if (x + i > 100) continue;
            if (mp[x + i]) {
                if (chk[mp[x + i]]) continue;
                Q.push(mp[x + i]);
                chk[mp[x + i]] = chk[x] + 1;
            }
            else {
                if (!chk[x+i]) {
                    Q.push(x+i);
                    chk[x+i] = chk[x] + 1;
                }
            }
        }
    }
}