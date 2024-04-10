#include <bits/stdc++.h>
using namespace std;

int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int a, b; cin >> a >> b;
    set<int> s;
    for (int i = 0; i < a; i++) {
        int x; cin >> x;
        s.insert(x);
    }
    for (int i = 0; i < b; i++) {
        int x; cin >> x;
        s.erase(x);
    }
    cout << s.size() << "\n";
    for (auto it = s.begin(); it != s.end(); it++) cout << *it << " ";
}