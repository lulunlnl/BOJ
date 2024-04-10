#include <bits/stdc++.h>
using namespace std;
constexpr int INF = 1e9;

struct node {
    int row, size;
    node* column;
    node* up;
    node* down;
    node* left;
    node* right;
};

void dlx_cover(node* c) {
    c->right->left = c->left;
    c->left->right = c->right;
    for (node* it = c->down; it != c; it = it->down) {
        for (node* jt = it->right; jt != it; jt = jt->right) {
            jt->down->up = jt->up;
            jt->up->down = jt->down;
            jt->column->size--;
        }
    }
}

void dlx_uncover(node* c) {
    for (node* it = c->up; it != c; it = it->up) {
        for (node* jt = it->left; jt != it; jt = jt->left) {
            jt->down->up = jt;
            jt->up->down = jt;
            jt->column->size++;
        }
    }
    c->right->left = c;
    c->left->right = c;
}

bool dlx_search(node* head, int k, vector<int>& sol) {
    if (head->right == head) return 1;
    node* ptr = nullptr;
    int low = INF;
    for (node* it = head->right; it != head; it = it->right) {
        if (it->size < low) {
            if (it->size == 0) return 0;
            low = it->size;
            ptr = it;
        }
    }
    dlx_cover(ptr);
    for (node* it = ptr->down; it != ptr; it = it->down) {
        sol.push_back(it->row);
        for (node* jt = it->right; jt != it; jt = jt->right) {
            dlx_cover(jt->column);
        }
        if (dlx_search(head, k + 1, sol)) return 1;
        else {
            sol.pop_back();
            for (node* jt = it->left; jt != it; jt = jt->left) {
                dlx_uncover(jt->column);
            }
        }
    }
    dlx_uncover(ptr);
    return 0;
}

vector<int> dlx_solve(vector<vector<int>> matrix) {
    int n = matrix[0].size();
    vector<node> column(n);
    node head;
    head.right = &column[0];
    head.left = &column[n - 1];
    for (int i = 0; i < n; i++) {
        column[i].size = 0;
        column[i].up = &column[i];
        column[i].down = &column[i];
        if (i == 0) column[i].left = &head;
        else column[i].left = &column[i - 1];
        if (i == n - 1) column[i].right = &head;
        else column[i].right = &column[i + 1];
    }

    vector<node*> nodes;
    for (int i = 0; i < matrix.size(); i++) {
        node* last = nullptr;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) {
                node* now = new node;
                now->row = i;
                now->column = &column[j];
                now->up = column[j].up;
                now->down = &column[j];
                if (last) {
                    now->left = last;
                    now->right = last->right;
                    last->right->left = now;
                    last->right = now;
                }
                else {
                    now->left = now;
                    now->right = now;
                }
                column[j].up->down = now;
                column[j].up = now;
                column[j].size++;
                last = now;
                nodes.push_back(now);
            }
        }
    }
    vector<int> solution;
    dlx_search(&head, 0, solution);
    for (node* ptr: nodes) delete ptr;

    return solution;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<vector<int>> matrix;
    int arr[9][9];
    vector<pair<int, pair<int, int>>> ret;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> arr[i][j];
            if (arr[i][j]) {
                int k = arr[i][j] - 1;
                vector<int> row(324, 0);
                row[i * 9 + j] = 1;
                row[81 + i * 9 + k] = 1;
                row[162 + j * 9 + k] = 1;
                row[243 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
                matrix.push_back(row);
                ret.push_back({i, {j, k}});
            }
            else {
                for (int k = 0; k < 9; k++) {
                    vector<int> row(324, 0);
                    row[i * 9 + j] = 1;
                    row[81 + i * 9 + k] = 1;
                    row[162 + j * 9 + k] = 1;
                    row[243 + (i / 3 * 3 + j / 3) * 9 + k] = 1;
                    matrix.push_back(row);
                    ret.push_back({i, {j, k}});
                }
            }
        }
    }
    auto ans = dlx_solve(matrix);
    for (auto e: ans) {
        arr[ret[e].first][ret[e].second.first] = ret[e].second.second;
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << arr[i][j] + 1 << " ";
        }
        cout << "\n";
    }
}