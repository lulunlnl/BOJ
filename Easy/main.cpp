#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, c; cin >> a >> b >> c;
    if (!c) cout << (int)sqrt(a + b);
    else cout << c * c - a - b;
}