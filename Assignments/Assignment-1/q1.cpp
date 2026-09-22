
#include <iostream>
#include <stack>

using namespace std;

int main() {
    cout << "number of inputs: ";
    int n;
    cin >> n;

    stack<int> io;

    string action;
    int x, current_depth = 0, max_depth = 0;
    for (int i = 0; i < n; i++) {
        cin >> action >> x;
        if (action == "open") {
            io.push(x);
            current_depth++;
            max_depth = current_depth > max_depth ? current_depth : max_depth;
        } else {              // action == "close"
            if (io.empty()) { // trying to close on an empty set
                cout << "invalid: " << i << "\n";
                return -1;
            }

            if (io.top() == x) { // matches most recently opened
                io.pop();
                current_depth--;
                continue;
            } else { // closing something not at the top
                cout << "invalid: " << i << "\n";
                return -1;
            }
        }
    }

    // the set should be empty now
    if (!io.empty()) {
        cout << "incomplete" << "\n";
        return -2;
    }

    cout << "valid: " << max_depth;

    return 0;
}