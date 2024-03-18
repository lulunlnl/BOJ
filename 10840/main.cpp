#include "bits/stdc++.h"
using namespace std;
constexpr int MOD = 524287;
vector<pair<int, int>> Hash[MOD];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b; cin >> a >> b;
    vector<int> p(10005, 1);
    p[1] = 0;
    for (int i = 2; i <= 100; i++) {
        if (p[i]) {
            for (int j = i*i; j <= 10000; j += i) p[j] = 0;
        }
    }
    vector<int> prime;
    for (int i = 2; i <= 10000; i++) if (p[i]) prime.push_back(i);

    int x, y;
    for (int i = 0; i < a.size(); i++) {
        x = y = 1;
        for (int j = i; j < a.size(); j++) {
            int now = a[j] - 'a';
            int l = j - i + 1;
            x = x * prime[now] % MOD;
            y = y * prime[now+26] % MOD;
            Hash[x].push_back({y, l});
        }
    }
    int ans = 0;
    for (int i = 0; i < b.size(); i++) {
        x = y = 1;
        for (int j = i; j < b.size(); j++) {
            int now = b[j] - 'a';
            int l = j - i + 1;
            x = x * prime[now] % MOD;
            y = y * prime[now+26] % MOD;
            for (auto& e: Hash[x]) {
                if (e == make_pair(y, l)) {
                    ans = max(ans, l);
                    break;
                }
            }
        }
    }
    cout << ans << "\n";
}