#include <bits/stdc++.h>
using namespace std;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
char dir[4] = {'R', 'L', 'D', 'U'};
char arr[15][15];
bool chk[15][15][15][15];

struct ball {
    int rx, ry, bx, by, cnt;
};

void move(int& x, int& y, int d) {
    while (1) {
        x += dx[d], y += dy[d];
        if (arr[x][y] == '#') {
            x -= dx[d], y -= dy[d];
            break;
        }
        else if (arr[x][y] == 'O') break;
    }
}

int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int n, m; cin >> n >> m;
    int a, b, c, d;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'R') a = i, b = j;
            else if (arr[i][j] == 'B') c = i, d = j;
        }
    }
    int ans = -1;
    string way;
    queue<pair<ball, string>> Q;
    Q.push({{a, b, c, d, 0}, ""});
    chk[a][b][c][d] = 1;
    while (!Q.empty()) {
        ball now = Q.front().first;
        string S = Q.front().second;
        Q.pop();
        if (now.cnt > 10) break;
        if (arr[now.rx][now.ry] == 'O') {
            ans = now.cnt;
            way = S;
            break;
        }
        for (int i = 0; i < 4; i++) {
            int rx = now.rx, ry = now.ry, bx = now.bx, by = now.by;
            move(rx, ry, i);
            move(bx, by, i);
            if (arr[bx][by] == 'O') continue;
            if (rx == bx && ry == by) {
                if (i == 0) now.ry < now.by ? ry-- : by--;
                else if (i == 1) now.ry < now.by ? by++ : ry++;
                else if (i == 2) now.rx < now.bx ? rx-- : bx--;
                else now.rx < now.bx ? bx++ : rx++;
            }
            if (!chk[rx][ry][bx][by]) {
                Q.push({{rx, ry, bx, by, now.cnt + 1}, S + dir[i]});
                chk[rx][ry][bx][by] = 1;
            }
        }
    }
    cout << ans << "\n";
    if (ans != -1) {
        cout << way;
    }
}