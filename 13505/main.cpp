#include "bits/stdc++.h"
using namespace std;

struct TrieNode {
    int child[2] = {}, cnt = 0;
};

struct Trie {
    vector<TrieNode> trie;
    int newNode() {
        TrieNode tmp;
        trie.push_back(tmp);
        return trie.size() - 1;
    }
    void add(int x) {
        int now = 0;
        for (int i = 31; i >= 0; i--) {
            bool flag = x & (1 << i);
            if (!trie[now].child[flag]) {
                int next = newNode();
                trie[now].child[flag] = next;
            }
            now = trie[now].child[flag];
            trie[now].cnt++;
        }
    }
    int query(int x) {
        int now = 0, ret = 0;
        for (int i = 31; i >= 0; i--) {
            bool flag = x & (1 << i);
            if (trie[trie[now].child[!flag]].cnt) {
                ret = 2*ret + 1;
                now = trie[now].child[!flag];
            }
            else {
                ret *= 2;
                now = trie[now].child[flag];
            }
        }
        return ret;
    }
    Trie() {
        newNode();
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Trie trie;
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    int ans = 0;
    for (int i = 0; i < N; i++) {
        if (i) ans = max(ans, trie.query(A[i]));
        trie.add(A[i]);
    }
    cout << ans << "\n";
}