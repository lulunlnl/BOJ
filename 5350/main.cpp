#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    string S; cin >> S;
    vector<int> is;
    for (int i = 0; i < n; i++) {
        if (S[i] == 'I') is.push_back(i);
    }
    auto chk = [&](int x) {
        int idx = is[is.size() - x];
        int cnt = 0, a = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (S[i] == 'J') a++;
            else if (S[i] == 'O' && a) b++, a--;
            else if (S[i] == 'I' && b && i >= idx) cnt++, b--;
            else if (S[i] == 'I' && i < idx) a++;
        }
        return x <= cnt;
    };

    int l = 1, r = is.size(), ans = 0;
    while (l <= r) {
        int m = l + r >> 1;
        if (chk(m)) {
            ans = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    cout << ans;
}