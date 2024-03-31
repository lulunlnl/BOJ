#include "bits/stdc++.h"
using namespace std;
typedef vector<vector<char>> vvc;
int flag, n, m;

void rotate(vvc& arr) {
    vvc tmp = arr;
    for (int i = 0; i < ; i++)
}

void solve(vvc& arr) {

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    vvc arr(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    solve(arr);
    if (!flag) cout << -1;
}