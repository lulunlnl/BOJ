#include <bits/stdc++.h>
using namespace std;

int p(int e) {
    for (int c, s = 0, v; c = getchar(), ~c;)
        if (c == '(' || c == '[') {
            v = p(-~c | 1);
            // -~x = -(-x-1) = x+1
            if (!v) return 0;
            s += v * ((c >> 5) + 1);
        } else return c % 2 ? c - e ? 0 : s ? s : 1 : e ? 0 : s;
}

int main() {
    cout << (-~40 | 1) << " " << -~91;
//    cout << p(0);
}