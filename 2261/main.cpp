#include "bits/stdc++.h"
#define x first
#define y second
using namespace std;
typedef pair<int, int> Point;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    vector<Point> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].x >> v[i].y;
    sort(v.begin(), v.end());
    set<Point> sweep = {{v[0].y, v[0].x}, {v[1].y, v[1].x}};
    auto D = [&](Point a, Point b) {
        return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
    };
    int ans = D(v[0], v[1]);
    int start = 0;
    for (int i = 2; i < N; i++) {
        Point now = v[i];
        while (start < i) {
            Point tmp = v[start];
            if ((tmp.x-now.x) * (tmp.x-now.x) > ans) {
                sweep.erase({tmp.y, tmp.x});
                start++;
            }
            else break;
        }
        int d = (int)sqrt((double)ans) + 1;
        auto lower = sweep.lower_bound({now.y - d, -10000});
        auto upper = sweep.upper_bound({now.y + d, 10000});
        for (auto it = lower; it != upper; it++) {
            Point t = *it;
            ans = min(ans, D(now, {t.y, t.x}));
        }
        if (ans == 0) break;
        sweep.insert({now.y, now.x});
    }
    cout << ans << "\n";
}