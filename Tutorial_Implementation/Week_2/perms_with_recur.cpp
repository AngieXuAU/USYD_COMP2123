
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<vector<int>> all_perms(vector<int> n) {
    if (n.size() == 1) {
        return {{}, n};
    } else {
        int choice = n[n.size() - 1];
        n.pop_back();
        vector<vector<int>> remaining = all_perms(n);
        return {{choice}, n};
    }
}

void pprint(stack<int> res) {
    int top;
    while (!res.empty()) {
        top = res.top();
        cout << top << "\t";
        res.pop();
    }
    cout << "\n";
}

int main() { return 0; }