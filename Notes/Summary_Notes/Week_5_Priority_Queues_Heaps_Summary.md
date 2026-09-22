# Week 5 Summary Notes: Priority Queues, Heaps & Heap-Sort

**Source PDF**: `Notes/Week 5 - w5_priority_queue.pdf`  
**Target Exam Focus**: Questions 1 (T/F Heap Properties & Complexities), 2 (Up-heap, Down-heap, & Array-Heap Tracing), 3 (Heap-based Algorithm Design & Build-Heap Proofs)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–8** | **Priority Queue ADT** | Key-Value entries, total ordering, stock engine applications |
| **Slides 9–14** | **Sequence-based PQs & Sorting** | Unsorted List vs Sorted List implementations, Selection Sort, Insertion Sort |
| **Slides 15–18** | **Heap Data Structure** | Heap-Order Property, Complete Binary Tree Property, Height $h = \lfloor \log n \rfloor$ |
| **Slides 19–27** | **Heap Operations** | `insert` (Up-heap), `removeMin` (Down-heap), Last-node tracking |
| **Slides 28–33** | **Array Heap & Heap-Sort** | Array index navigation ($2i, 2i+1, \lfloor i/2 \rfloor$), In-place Heap-Sort, Bottom-up $O(n)$ Heap Construction |

---

## 2. Priority Queue Implementations & Complexities

### 2.1 Comparison Table of Priority Queue Representations

| Implementation | `insert(k, v)` | `min()` | `removeMin()` | Space Complexity |
| :--- | :---: | :---: | :---: | :---: |
| **Unsorted List / Array** | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Sorted List / Array** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ |
| **Binary Heap (Min-Heap)** | **$O(\log n)$** (Amortized) | **$O(1)$** | **$O(\log n)$** | **$O(n)$** |

---

### 2.2 Sequence-Based PQ Sorting Algorithms

1. **Selection-Sort**:
   - Uses an **Unsorted List** Priority Queue.
   - Phase 1: Insert $n$ elements into unsorted list ($n \times O(1) = O(n)$ time).
   - Phase 2: Call `removeMin()` $n$ times ($\sum_{i=1}^n i = O(n^2)$ time).
   - Total Time: **$O(n^2)$** in best, average, and worst cases.

2. **Insertion-Sort**:
   - Uses a **Sorted List** Priority Queue.
   - Phase 1: Insert $n$ elements into sorted list ($\sum_{i=1}^n i = O(n^2)$ worst case).
   - Phase 2: Call `removeMin()` $n$ times ($n \times O(1) = O(n)$ time).
   - Total Time: **$O(n^2)$** worst case, **$O(n)$** best case (if input array is already sorted).

---

## 3. Heap Data Structure & Array Implementation

### 3.1 Properties of a Min-Heap
A binary heap is a binary tree storing key-value pairs at its nodes satisfying two structural and ordering properties:
1. **Heap-Order Property**: For every node $v$ other than the root:
   $$\text{key}(v) \ge \text{key}(\text{parent}(v))$$
   *(The root always contains the minimum key).*
2. **Complete Binary Tree Property**: Every level $d$ is completely full, except possibly the bottom level, which is filled strictly from left to right.

- **Height Property**: A heap storing $n$ keys has height:
  $$h = \lfloor \log_2 n \rfloor$$

---

### 3.2 Array-Based Heap Navigation (1-Indexed Array)
For a node stored at array index $i$ ($1 \le i \le n$):
- **Left Child**: `2 * i`
- **Right Child**: `2 * i + 1`
- **Parent**: `floor(i / 2)`
- **Last Node**: Located at index $n$. Next insertion position is at index $n + 1$.

*(Note: For 0-indexed arrays: Left = $2i+1$, Right = $2i+2$, Parent = $\lfloor (i-1)/2 \rfloor$).*

---

## 4. Tracing Heap Operations (Question 2 Preparation)

### 4.1 Insertion (`insert(k, v)`)
1. Store key $k$ at index $n + 1$ (the next available leaf slot).
2. Execute **Up-Heap (Bubble-Up)**:
   - Compare key at $i$ with key at parent $\lfloor i/2 \rfloor$.
   - If $\text{key}(i) < \text{key}(\text{parent})$, swap elements and update $i \leftarrow \lfloor i/2 \rfloor$.
   - Stop when $\text{key}(i) \ge \text{key}(\text{parent})$ or $i = 1$ (root reached).
- **Time Complexity**: $O(\log n)$ worst-case.

---

### 4.2 Removal of Minimum (`removeMin()`)
1. Save key at root index 1 (the minimum element).
2. Replace root element at index 1 with the element at last index $n$.
3. Decrement heap size $n \leftarrow n - 1$.
4. Execute **Down-Heap (Bubble-Down)**:
   - Compare key at $i$ with its children at $2i$ and $2i+1$.
   - Find the child with the **smaller key**.
   - If $\text{key}(i) > \text{key}(\text{smaller\_child})$, swap elements and set $i \leftarrow \text{smaller\_child\_index}$.
   - Stop when $\text{key}(i) \le \text{key}(\text{both\_children})$ or $i$ becomes a leaf ($2i > n$).
- **Time Complexity**: $O(\log n)$ worst-case.

---

## 5. Bottom-Up Heap Construction ($O(n)$ Heapify)

Building a heap by performing $n$ sequential `insert` operations takes $O(n \log n)$ time.  
**Bottom-Up Heap Construction** builds a heap in **$O(n)$ time**:

### Algorithm
1. Store all $n$ arbitrary elements into the array $A[1 \dots n]$.
2. Starting from index $i = \lfloor n/2 \rfloor$ down to $1$, call `down_heap(i)` on node $i$.

### Proof of $O(n)$ Complexity
- Nodes at height $h'$ perform at most $h'$ swaps during `down_heap`.
- The number of nodes at height $h'$ is at most $\lceil n / 2^{h'+1} \rceil$.
- Total swaps:
  $$S = \sum_{h'=0}^{\lfloor \log_2 n \rfloor} \frac{n}{2^{h'+1}} \cdot h' = \frac{n}{2} \sum_{h'=0}^{\infty} \frac{h'}{2^{h'}} = \frac{n}{2} \cdot 2 = O(n)$$

---

## 6. Heap-Sort Algorithm

1. **Phase 1 (Heapify)**: Convert input array of size $n$ into a Max-Heap in $O(n)$ time using Bottom-Up construction.
2. **Phase 2 (Extraction)**: For $i = n$ down to 2:
   - Swap $A[1]$ (current max) with $A[i]$.
   - Reduce active heap size to $i - 1$.
   - Call `down_heap(1)` on active heap of size $i - 1$.

| Metric | Complexity | Notes |
| :--- | :---: | :--- |
| **Worst-Case Time** | $O(n \log n)$ | Performs $n-1$ extractions of $O(\log n)$ cost |
| **Best-Case Time** | $O(n \log n)$ | Even if array is sorted |
| **Average-Case Time** | $O(n \log n)$ | Consistently optimal bound |
| **Auxiliary Space** | **$O(1)$** | **In-place algorithm** (operates directly on input array) |

---

## 7. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"In a min-heap with $n$ nodes, finding the MAXIMUM key takes $O(1)$ time."** | **False** | The maximum key can reside at any of the leaf nodes (which make up $\lceil n/2 \rceil$ nodes), requiring an $O(n)$ search. |
| **"Bottom-up heap construction transforms an unsorted array of $n$ elements into a heap in $O(n)$ time."** | **True** | Proven mathematically via sum of series bounded by $O(n)$. |
| **"Heap-Sort has a worst-case time complexity of $O(n \log n)$ and auxiliary space complexity of $O(1)$."** | **True** | Heap-sort is an in-place $O(n \log n)$ sorting algorithm. |
| **"In a 1-indexed array representation of a binary heap, the parent of node at index $i$ is at $\lfloor i/2 \rfloor$."** | **True** | Standard complete binary tree indexing property. |
| **"Selection Sort using an unsorted list priority queue runs in $O(n \log n)$ time."** | **False** | Finding the minimum in an unsorted list takes $O(n)$ time per removal, yielding $O(n^2)$ total time. |
