#include <bits/stdc++.h>
using namespace std;
int h, w, dp[25][25][25][25];
char a[25][25];

int Grundy(int l1, int r1, int l2, int r2) {
    if (l1 < 0 || r1 < 0 || l2 >= h || r2 >= w || l1 > l2 || r1 > r2) return 0;
    int &ret = dp[l1][r1][l2][r2];
    if (ret != -1) return ret;
    set<int> s;
    for (int i = l1; i <= l2; i++) {
        for (int j = r1; j <= r2; j++) {
            if (a[i][j] == 'X') continue;
            int t = Grundy(l1, r1, i - 1, j - 1) ^ Grundy(l1, j + 1, i - 1, r2) ^ Grundy(i + 1, r1, l2, j - 1) ^ Grundy(i + 1, j + 1, l2, r2);
            s.insert(t);
        }
    }
    for (int i = 0; ; i ++) if (s.find(i) == s.end()) return ret = i;
}

int main() {
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    if (Grundy(0, 0, h - 1,  w - 1)) cout << "First";
    else cout << "Second";
}