#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

/**
 * Min-Heap Priority Queue Scaffold (0-indexed)
 *
 * Invariant (Min-Heap Property):
 *   For every node i (except root 0): heap[parent(i)] <= heap[i]
 *
 * 0-based Index formulas:
 *   - parent(i)      = (i - 1) / 2
 *   - left_child(i)  = 2 * i + 1
 *   - right_child(i) = 2 * i + 2
 */

class MinHeap {
  private:
    vector<int> heap;

    // --- Index Helper Methods ---
    int parent(int i) const { return (i - 1) / 2; }

    int left_child(int i) const { return i * 2 + 1; }

    int right_child(int i) const { return i * 2 + 2; }

    // --- Core Heap Restructuring Operations ---

    /**
     * sift_up (up-heap / bubble-up):
     * Used after inserting an element at the back.
     * Continuously swap element with its parent while heap property is
     * violated. Time Complexity: O(log n)
     */
    void sift_up(int i) {
        // i: index of newly added element
        // invariant: parent <= child
        int self = heap.at(i);
        int p_index = parent(i);
        while (self < heap[p_index]) {
            swap(heap[i], heap[p_index]);
            i = p_index;
            if (i <= 0) {
                break;
            }
            p_index = parent(i);
            self = heap.at(i);
        }
    }

    /**
     * sift_down (down-heap / bubble-down):
     * Used after replacing the root with the last element during pop().
     * Compare element with its children, swap with the smaller child, repeat.
     * Time Complexity: O(log n)
     */
    void sift_down(int i) {
        // invariant: parent <= child
        // int self = heap.at(i);
        // int lc_ind = left_child(i);
        // int rc_ind = right_child(i);

        // while (self > heap.at(lc_ind) || self > heap.at(rc_ind)) {
        //     int swap_ind;
        //     if (self > heap.at(lc_ind) && self > heap.at(rc_ind)) {
        //         swap_ind =
        //             (heap.at(lc_ind) < heap.at(rc_ind) ? lc_ind : rc_ind);
        //     } else if (self > heap.at(lc_ind)) { // only larger than left
        //     child
        //         swap_ind = lc_ind;
        //     } else { // only larger than right child
        //         swap_ind = rc_ind;
        //     }
        //     swap(heap[i], heap[swap_ind]);

        //     i = swap_ind;
        //     self = heap.at(i);

        //     lc_ind = left_child(i);
        //     rc_ind = right_child(i);

        //     if (lc_ind >= heap.size() || rc_ind >= heap.size()) {
        //         break;
        //     }
        // }

        int n = heap.size();
        while (left_child(i) < n) { // As long as at least a left child exists
            int lc_ind = left_child(i);
            int rc_ind = right_child(i);
            // Assume current node is smallest to start
            int smallest = i;
            // Compare with left child (we already know it exists)
            if (heap[lc_ind] < heap[smallest]) {
                smallest = lc_ind;
            }
            // Compare with right child ONLY IF it exists
            if (rc_ind < n && heap[rc_ind] < heap[smallest]) {
                smallest = rc_ind;
            }
            // If current node is smaller than both children, we're done!
            if (smallest == i) {
                break;
            }
            // Otherwise swap and continue down
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

    /**
     * heapify (Bottom-up heap construction):
     * Builds a heap in-place from an arbitrary array.
     * Calls sift_down starting from the last internal node up to root.
     * Time Complexity: O(n)
     */
    void heapify() {
        for (int i = (heap.size() / 2) - 1; i >= 0; --i) {
            sift_down(i);
        }
    }

  public:
    // Default constructor: creates an empty priority queue
    MinHeap() = default;

    // Range constructor: builds heap using bottom-up heapify in O(n)
    MinHeap(const vector<int> &elements) : heap(elements) { heapify(); }

    // Returns whether the priority queue is empty
    bool empty() const { return heap.empty(); }

    // Returns the number of elements in the priority queue
    size_t size() const { return heap.size(); }

    // Returns the minimum element (root) without removing it
    // Throws runtime_error if empty
    int top() const {
        if (empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap.at(0);
    }

    // Inserts a new value into the priority queue
    // Time Complexity: O(log n)
    void push(int val) {
        int i = heap.size();
        heap.push_back(val);
        sift_up(i);
    }

    // Removes the minimum element (root)
    // Throws runtime_error if empty
    // Time Complexity: O(log n)
    void pop() {
        if (empty()) {
            throw runtime_error("Heap is empty");
        }

        // swap first and last in vector, then delete the last
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();

        // restore heap property
        if (!heap.empty()) {
            sift_down(0);
        }
    }
};

// --- Test Driver ---
int main() {
    cout << "Running MinHeap tests..." << endl;

    // Test 1: Push and Pop order
    MinHeap pq;
    vector<int> inputs = {10, 4, 15, 20, 0, 8, -2, 5};
    for (int x : inputs) {
        pq.push(x);
    }

    assert(pq.size() == 8);
    assert(!pq.empty());

    vector<int> extracted;
    while (!pq.empty()) {
        extracted.push_back(pq.top());
        pq.pop();
    }

    // Expected sorted order: -2, 0, 4, 5, 8, 10, 15, 20
    vector<int> expected = {-2, 0, 4, 5, 8, 10, 15, 20};
    assert(extracted == expected);
    cout << "Test 1 Passed: Basic push/pop produces min order." << endl;

    // Test 2: Bottom-up Heapify constructor O(n)
    vector<int> unsorted = {9, 3, 7, 1, 6, 2, 8, 4, 5};
    MinHeap pq2(unsorted);
    assert(pq2.size() == 9);

    vector<int> extracted2;
    while (!pq2.empty()) {
        extracted2.push_back(pq2.top());
        pq2.pop();
    }

    vector<int> expected2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(extracted2 == expected2);
    cout << "Test 2 Passed: Bottom-up heapify constructor works correctly."
         << endl;

    // Test 3: Duplicates
    MinHeap pq3;
    pq3.push(5);
    pq3.push(2);
    pq3.push(5);
    pq3.push(2);
    assert(pq3.top() == 2);
    pq3.pop();
    assert(pq3.top() == 2);
    pq3.pop();
    assert(pq3.top() == 5);
    pq3.pop();
    assert(pq3.top() == 5);
    pq3.pop();
    assert(pq3.empty());
    cout << "Test 3 Passed: Duplicates handled properly." << endl;

    cout << "\nAll tests passed successfully!" << endl;
    return 0;
}