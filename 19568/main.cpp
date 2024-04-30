#include <bits/stdc++.h>
using namespace std;

int main() {
    auto solve = [&](int x, int y) {
        if (x < 15) return y == 15 ? 1 : 0;
        else if (x == 15) {
            if (y == 15) return 0;
            return y < 15 ? 225 : 3375;
        }
        return y == 15 ? 15 : 0;
    };
    for (int i = 0; i < 30; i++) for (int j = 0; j < 30; j++) cout << solve(i, j) << " \n"[j == 29];
}