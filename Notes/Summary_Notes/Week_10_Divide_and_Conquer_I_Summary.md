# Week 10 Summary Notes: Divide and Conquer I (Recurrences, Sorting, & Lower Bounds)

**Source PDF**: `Notes/Week 10 - w10_divide_and_conquer_i.pdf`  
**Target Exam Focus**: Questions 1 (T/F Divide-and-Conquer Recurrences, Master Theorem cases, Sorting Lower Bounds), 2 (Unrolling Recurrences & Recursion Trees, Merge-Sort & Quick-Sort Tracing), 3 (Divide-and-Conquer Algorithm Design, Correctness via Strong Induction, Recurrence Setup & Solving)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–8** | **Divide and Conquer Paradigm** | The 3 steps (Divide, Recur/Delegate, Conquer), base cases, recursion fairy |
| **Slides 9–21** | **Binary Search Analysis & Correctness** | Array searching, middle element comparison, loop invariants, correctness proof |
| **Slides 22–28** | **Recurrence Formulation & Unrolling** | Setting up `T(n) = T(n/2) + O(1)` vs linked list `T(n) = T(n/2) + O(n)`, unrolling trees |
| **Slides 29–47** | **Merge-Sort** | Algorithm steps, `merge` routine implementation, correctness proof by induction, `T(n) = 2T(n/2) + O(n) = O(n log n)` |
| **Slides 48–52** | **Solving Recurrences by Unrolling & Summary Table** | Level patterns, geometric progressions, master list of standard recurrences |
| **Slides 53–54** | **Quick-Sort Introduction** | Pivot selection, 3-way partitioning (`<`, `=`, `>`), expected running time `O(n log n)` |
| **Slides 55–57** | **Comparison Sorting Lower Bound** | Decision tree model, height lower bound, proof that comparison sorting requires `Omega(n log n)` comparisons |
| **Slide 58** | **Common Conceptual Traps** | Using Merge-Sort does not automatically make an algorithm divide-and-conquer |

---

## 2. The Divide and Conquer Framework

A Divide and Conquer algorithm solves a problem through three recursive steps:
1. **Divide**: If the instance is small enough (constant size base case, usually `n <= 1`), solve it directly. Otherwise, break the input into one or more smaller subproblems.
2. **Recur (Delegate)**: Recursively solve each subproblem. The solutions are guaranteed correct by the inductive hypothesis ("Recursion Fairy").
3. **Conquer**: Combine / merge the subproblem solutions into the solution for the overall problem.

---

## 3. Case Studies & Recurrence Analysis

### 3.1 Binary Search: Array vs Linked List

| Feature | Binary Search on Array | Binary Search on Linked List |
| :--- | :--- | :--- |
| **Divide Step** | Find mid via indexing: `O(1)` | Traverse to middle node: `O(n)` |
| **Recur Step** | 1 subproblem of size `n/2`: `T(n/2)` | 1 subproblem of size `n/2`: `T(n/2)` |
| **Conquer Step** | Return result: `O(1)` | Return result: `O(1)` |
| **Recurrence** | `T(n) = T(n/2) + O(1)` | `T(n) = T(n/2) + O(n)` |
| **Total Running Time** | **`O(log n)`** | **`O(n)`** (`n + n/2 + n/4 + ... = 2n`) |

---

### 3.2 Merge-Sort: Design, Correctness & Analysis
- **Algorithm**:
  - Divide: Split array into two halves at `mid = floor(n / 2)` in `O(n)` (or `O(1)` with pointers).
  - Recur: `merge_sort(left)`, `merge_sort(right)` (`2 * T(n/2)`).
  - Conquer: Merge two sorted subarrays using two pointers into result array in `O(n)` comparisons.
- **Inductive Correctness**:
  - *Base Case*: Array of size `0` or `1` is trivially sorted.
  - *Inductive Step*: Subarrays of size `<= k` are correctly sorted by inductive hypothesis. The `merge` procedure preserves sorted order across both halves by repeatedly choosing the smallest remaining element.
- **Recurrence**:
  `T(n) = 2T(n/2) + O(n)`
  - Total levels in recursion tree: `log_2 n + 1`.
  - Work at level `i`: `2^i * c(n / 2^i) = c * n`.
  - Total work: `sum_{i=0}^{log_2 n} c * n = c * n * log_2 n = O(n log n)`.

---

### 3.3 Quick-Sort Overview
- **Divide**: Pick a pivot element `p` (randomly chosen). Partition array into three buckets:
  1. Elements `< p`
  2. Elements `== p`
  3. Elements `> p`
- **Recur**: Recursively sort `< p` and `> p` partitions.
- **Conquer**: Concatenate `< p`, `== p`, and `> p` arrays in `O(n)` time.
- **Complexity**:
  - Expected Running Time: **`O(n log n)`**.
  - Worst-Case Running Time (e.g. consistently bad pivot): `O(n^2)`.

---

## 4. Solving Recurrences by Unrolling

### 4.1 Unrolling Method (Step-by-Step)
1. Write out the tree representation level-by-level: Level 0 (root), Level 1, Level 2, ..., Level `k`.
2. Compute:
   - Number of subproblems at level `i`.
   - Size of each subproblem at level `i`.
   - Work done per subproblem at level `i`.
   - Total work done across all nodes at level `i`.
3. Identify tree depth `h` when subproblem reaches base case size 1.
4. Sum total work across all levels `sum_{i=0}^h [Work at level i]`.

---

### 4.2 Standard Recurrence Catalog (Exam Reference)

| Recurrence Relation | Solution | Example Algorithm |
| :--- | :---: | :--- |
| `T(n) = T(n/2) + O(1)` | **`O(log n)`** | Binary Search (Array) |
| `T(n) = T(n/2) + O(n)` | **`O(n)`** | Binary Search (Linked List) |
| `T(n) = 2T(n/2) + O(1)` | **`O(n)`** | Tree Traversal (Binary Tree) |
| `T(n) = 2T(n/2) + O(log n)` | **`O(n)`** | Divide and Conquer variants |
| `T(n) = 2T(n/2) + O(n)` | **`O(n log n)`** | Merge-Sort |
| `T(n) = T(n-1) + O(1)` | **`O(n)`** | Linear Scan / Factorial |
| `T(n) = T(n-1) + O(n)` | **`O(n^2)`** | Selection-Sort / Insertion-Sort |

---

## 5. Comparison-Based Sorting Lower Bound

### 5.1 Decision Tree Model
- Any comparison-based sorting algorithm can be modeled as a **binary decision tree**:
  - Each **internal node** represents a comparison between two elements `A[i] < A[j]`.
  - Each branch represents the binary outcome (True/Yes or False/No).
  - Each **leaf (external node)** represents a distinct permutation (sorted order) of the `n` elements.

### 5.2 The `Omega(n log n)` Proof
1. An array of `n` distinct elements has **`n!`** possible permutations.
2. The decision tree must contain at least `n!` leaves (external nodes `L >= n!`) to distinguish all possible outcomes.
3. A binary tree of height `h` has at most `2^h` leaves (`L <= 2^h`).
4. Therefore:
   `2^h >= L >= n!  ==>  h >= log_2(n!)`
5. Using Stirling's approximation or expansion:
   `log_2(n!) = sum_{i=1}^n log_2(i) >= sum_{i=n/2}^n log_2(n/2) = (n / 2) * log_2(n / 2) = Omega(n log n)`
6. **Conclusion**: Any comparison-based sorting algorithm requires at least `Omega(n log n)` comparisons in the worst case. Algorithms like Merge-Sort and Heap-Sort are asymptotically optimal.

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"Binary search on a singly linked list takes `O(log n)` time."** | **False** | Finding the midpoint in a linked list takes `O(n)` time, making the recurrence `T(n) = T(n/2) + O(n) = O(n)`. |
| **"Any sorting algorithm must make at least `Omega(n log n)` comparisons in the worst case."** | **True** | By the decision tree model, any comparison-based sort has height `h >= log(n!) = Omega(n log n)`. |
| **"If an algorithm sorts elements with Merge-Sort in step 1 and then runs a linear scan, the entire algorithm is classified as Divide and Conquer."** | **False** | Preprocessing with Merge-Sort does not make the underlying algorithmic strategy divide-and-conquer (e.g. greedy algorithms often sort first). |
| **"The recurrence `T(n) = 2T(n/2) + O(1)` solves to `O(log n)`."** | **False** | It solves to `O(n)` because base-case work dominates (`2^{log_2 n} = n` leaves). |
| **"Merge-Sort performs fewer comparisons in the worst case than any possible comparison sort."** | **False** | It achieves the asymptotic lower bound `O(n log n)`, but other comparison algorithms may use slightly fewer exact comparisons. |
| **"Quick-Sort always achieves `O(n log n)` time."** | **False** | Deterministic Quick-Sort with bad pivot choices (e.g. already sorted array with first element as pivot) degrades to `O(n^2)` worst-case time. |

