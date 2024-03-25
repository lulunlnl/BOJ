#include "bits/stdc++.h"
using namespace std;

void BFS() {
    int n; cin >> n;
    if (n == 1) {
        cout << "1\n";
        return;
    }
    queue<int> Q;
    vector<int> chk(n);
    vector<pair<int, int>> arr(n);
    chk[1] = 1; arr[1] = {-1, 1};
    Q.push(1);
    while (!Q.empty()) {
        int now = Q.front(); Q.pop();
        int flag = 0;
        for (int i = 0; i < 2; i++) {
            int next = 10 * now + i;
            next %= n;
            if (chk[next]) continue;
            arr[next] = {now, i};
            chk[next] = 1;
            if (next == 0) flag = 1;
            Q.push(next);
        }
        if (flag) break;
    }
    vector<int> ans;
    for (int i = 0; i != -1; i = arr[i].first) {
        ans.push_back(arr[i].second);
    }
    reverse(ans.begin(), ans.end());
    for (auto& e: ans) cout << e;
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T--) {
        BFS();
    }
}