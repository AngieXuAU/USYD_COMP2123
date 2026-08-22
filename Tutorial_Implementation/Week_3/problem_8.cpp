#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;

    explicit Node(int val, Node *left = nullptr, Node *right = nullptr)
        : val{val}, left{left}, right{right} {}
};

unordered_map<int, int> map = {};
int height(Node *node) {
    if (node == nullptr) {
        return -1;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);

    map[node->val] = abs(left_height - right_height);

    return (left_height > right_height ? left_height : right_height) + 1;
}

int main() {
    Node *n12 = new Node(12);
    Node *n11 = new Node(11, n12);
    Node *n7 = new Node(7, n11);
    Node *n10 = new Node(10);
    Node *n6 = new Node(6, n10);
    Node *n3 = new Node(3, n6, n7);

    Node *n8 = new Node(8);
    Node *n9 = new Node(9);
    Node *n5 = new Node(5, n8, n9);
    Node *n4 = new Node(4);
    Node *n2 = new Node(2, n4, n5);

    Node *n1 = new Node(1, n2, n3);

    height(n1);

    auto print_key_value = [](const auto &key, const auto &value) {
        cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };

    for (auto node : map) {
        print_key_value(node.first, node.second);
    }

    return 0;
}