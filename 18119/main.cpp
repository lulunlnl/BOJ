#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
#ifdef ONLINE_JUDGE
#define debug(x)
#else
#define debug(x) cout << "[Debug] " << #x << ": " << x << '\n'
#define debug2(x, y) cout << "[Debug] " << #x << ": " << x << ", " << #y << ": " << y << '\n';
#endif

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M; cin >> N >> M;
    vector<int> dic;
    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        int x = 0;
        for (int j = 0; j < S.size(); j++) {
            x |= (1 << (S[j] - 'a'));
        }
        dic.push_back(x);
    }
    int t = (1 << 26) - 1;
    while (M--) {
        int op; char c;
        cin >> op >> c;
        if (op == 1) t ^= (1 << (c - 'a'));
        else t |= (1 << (c - 'a'));
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if ((t & dic[i]) == dic[i]) ans++;
        }
        cout << ans << "\n";
    }
}