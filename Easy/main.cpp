#include <bits/stdc++.h>
using namespace std;
int a[15][15], b[15][15];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> a[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            cin >> b[i][j];
            ans += a[i][j] ^ b[i][j];
        }
    }
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            tmp += a[i][j] ^ b[n - 1 - j + i][i - j];
        }
    }
    ans = min(ans, tmp);
    tmp = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            tmp += a[i][j] ^ b[n - j - 1][i];
        }
    }
    ans = min(ans, tmp);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            a[i][j] = a[i][i - j];
        }
    }
    tmp = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            tmp += a[i][j] ^ b[n - 1 - j + i][i - j];
        }
    }
    ans = min(ans, tmp);
    tmp = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            tmp += a[i][j] ^ b[n - j - 1][i];
        }
    }
    ans = min(ans, tmp);
    cout << ans;
}