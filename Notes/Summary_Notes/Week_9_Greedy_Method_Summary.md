# Week 9 Summary Notes: The Greedy Method & Applications

**Source PDF**: `Notes/Week 9 - w9_greedy.pdf`  
**Target Exam Focus**: Questions 1 (T/F Greedy Choice Property, Exchange Arguments & Counterexamples), 2 (Tracing Fractional Knapsack, Interval Partitioning, & Huffman Coding Trees), 3 (Greedy Algorithm Design, Proofs of Optimality via Exchange / Stays Ahead)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–5** | **Greedy Algorithm Paradigm** | Definition, locally optimal choices, generic framework, pros/cons |
| **Slides 6–14** | **The Fractional Knapsack Problem** | Problem formulation, benefit/weight ratio, exchange argument proof, `O(n log n)` complexity |
| **Slides 15–20** | **Task Scheduling & Interval Partitioning** | Interval depth lower bound, greedy assignment, "stays ahead" optimality proof, `O(n log n)` with Min-Heap |
| **Slides 21–24** | **Text Compression & Prefix Codes** | Run-length encoding, prefix codes, binary encoding trees, frequency/depth relationship |
| **Slides 25–35** | **Huffman's Algorithm** | Bottom-up tree construction, Min-Heap PQ implementation, full tracing example, induction proof, `O(n + d log d)` running time |
| **Slide 36** | **Greedy Heuristics & Pitfalls** | 0-1 Knapsack failure, task constraints, non-binary encoding limitations |

---

## 2. The Greedy Paradigm

### 2.1 Core Philosophy
- A **greedy algorithm** builds a solution incrementally, step by step, making the **locally optimal choice** at each stage without backtracking, hoping to find a global optimum.
- **Advantages**: Typically very fast, simple to implement, and mathematically elegant.
- **Challenges**: Hardest to design and prove correct. Small changes to problem constraints often cause greedy approaches to produce suboptimal or invalid results.

### 2.2 Standard Proof Techniques for Greedy Algorithms
1. **Exchange Argument**:
   - Assume an arbitrary optimal solution `OPT` differs from the greedy solution `G`.
   - Identify the first difference where `OPT` chose differently from `G`.
   - "Exchange" the element in `OPT` for the greedy element, showing that the objective value cannot worsen (cost decreases or remains equal, value increases or remains equal).
   - Inductively transform `OPT` into `G` without losing optimality, proving `G` is optimal.
2. **"Greedy Stays Ahead"**:
   - Define a progress measure at each step `k`.
   - Prove by induction that after `k` choices, the greedy solution is at least as far ahead as any other valid solution.

---

## 3. Classic Problem 1: Fractional Knapsack

### 3.1 Problem Definition
- **Input**: Set `S` of `n` items, each with benefit `b_i > 0` and weight `w_i > 0`; knapsack capacity `W`.
- **Constraint**: Can take a fraction `x_i` of item `i` where `0 <= x_i <= w_i` and `sum_{i in S} x_i <= W`.
- **Objective**: Maximize total benefit `sum_{i in S} b_i * (x_i / w_i)`.

### 3.2 Evaluation of Greedy Strategies

| Strategy | Rule | Optimal? | Counterexample / Reason |
| :--- | :--- | :---: | :--- |
| **Highest Benefit** | Pick highest `b_i` | **No** | Heavy item with large benefit might block many light items with higher total value per unit. |
| **Smallest Weight** | Pick smallest `w_i` | **No** | Light items might have negligible value. |
| **Benefit-to-Weight Ratio** | Pick highest `v_i = b_i / w_i` | **YES** | Every unit of capacity used gives maximum immediate value return. |

### 3.3 Algorithm & Complexity
```text
def fractional_knapsack(b, w, W):
    sort items in descending order of value ratio b[i] / w[i]
    curr = 0
    x = [0] * n
    for i in sorted order:
        if curr == W:
            break
        take = min(w[i], W - curr)
        x[i] = take
        curr += take
    return x
```
- **Time Complexity**: **`O(n log n)`** to sort items; **`O(n)`** for the greedy loop. Overall: **`O(n log n)`**.
- **Important Contrast**: The **0-1 Knapsack Problem** (where items cannot be split) CANNOT be solved with a greedy strategy; it is NP-hard and requires Dynamic Programming.

---

## 4. Classic Problem 2: Interval Partitioning (Task Scheduling)

### 4.1 Problem Definition & Lower Bound
- **Input**: Set of `n` lectures/tasks, each with start time `s_i` and finish time `f_i` (open intervals `(s_i, f_i)`).
- **Goal**: Find the minimum number of classrooms needed so that no two overlapping lectures share a classroom.
- **Interval Depth**: The maximum number of intervals that overlap at any single point in time.
  - **Fundamental Lower Bound**: `Number of classrooms needed >= depth`.

### 4.2 Greedy Algorithm (Earliest Start Time)
1. Sort all lectures in increasing order of start time `s_i`.
2. For each lecture `i`:
   - If lecture `i` is compatible with some already opened classroom `k` (i.e. `finish_time[k] <= s_i`), schedule lecture `i` in classroom `k`.
   - Else, open a new classroom `d + 1` and schedule lecture `i` in it.
3. Return total classrooms `d`.

### 4.3 Optimality & Implementation
- **Optimality ("Greedy Stays Ahead")**: Suppose the algorithm opens classroom `d`. This only occurs because some lecture `i` was incompatible with all existing `d - 1` classrooms. Since intervals are sorted by start time, all `d - 1` other lectures started at or before `s_i` and finish strictly after `s_i`. Thus, exactly `d` intervals overlap at time `s_i + epsilon`. Hence, `depth >= d`, proving the schedule uses exactly `depth` classrooms and is strictly optimal.
- **Data Structure Implementation**:
  - Maintain a **Min-Heap** of existing classrooms keyed by their current finish time.
  - Query `min()` to check if earliest finishing classroom is free (`min() <= s_i`).
  - If free: `remove_min()`, update finish time to `f_i`, and `insert()`.
  - If not free: create new classroom with finish time `f_i` and `insert()`.
- **Time Complexity**: **`O(n log n)`** (sorting takes `O(n log n)`, each task does `O(log n)` heap operations).

---

## 5. Classic Problem 3: Huffman Coding (Optimal Prefix Codes)

### 5.1 Prefix Codes & Binary Encoding Trees
- **Prefix Code**: A variable-length code where no codeword is a prefix of any other codeword. Allows unambiguous instantaneous decoding without delimiters.
- **Encoding Tree Representation**:
  - Binary tree where each **leaf** represents a character `c in C`.
  - Left edge = `0`, Right edge = `1`.
  - Path from root to leaf `c` defines character `c`'s codeword.
  - Length of codeword = `depth_T(c)`.
  - Total bits needed to encode text:
    `Cost(T) = sum_{c in C} f(c) * depth_T(c)`
  - **Optimality Rule**: Frequent characters must have shallow depths (short codes); rare characters have larger depths (longer codes).

---

### 5.2 Huffman's Algorithm Mechanics
Bottom-up greedy tree merger using a Min-Heap priority queue:
```text
def huffman(C, f):
    Q = new Min-Heap Priority Queue
    for c in C:
        T = single-node tree storing (c, f[c])
        Q.insert(f[c], T)
    
    while Q.size() > 1:
        f1, T1 = Q.remove_min()
        f2, T2 = Q.remove_min()
        T = new binary tree with children T1, T2
        f = f1 + f2
        Q.insert(f, T)
        
    return Q.remove_min()
```

### 5.3 Complexity & Correctness
- **Time Complexity**:
  - Counting character frequencies in text of length `n`: `O(n)`.
  - Let `d = |C|` be the number of distinct alphabet characters.
  - Heap initialization: `O(d)` or `O(d log d)`.
  - Loop runs `d - 1` iterations; each iteration performs 2 `remove_min` and 1 `insert` (`O(log d)` each).
  - Total time: **`O(n + d log d)`**.
- **Correctness (Exchange & Induction)**:
  - *Lemma*: There exists an optimal tree where the two lowest-frequency characters are siblings at maximum depth.
  - *Induction*: Replacing the two lowest frequency characters `(i, k)` with a composite character `ik` having frequency `f(i) + f(k)` reduces problem size from `d` to `d - 1`. By induction, the contracted tree is optimal, which implies optimality of the reconstructed tree.

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"The greedy choice of choosing the item with highest benefit solves the 0-1 Knapsack problem optimally."** | **False** | Neither highest benefit nor highest ratio guarantees optimality for 0-1 Knapsack due to indivisibility of items. |
| **"The greedy benefit-to-weight ratio strategy computes the optimal solution for Fractional Knapsack."** | **True** | Proven optimal via exchange argument. |
| **"In interval partitioning, sorting intervals by finish time always yields an optimal classroom allocation."** | **False** | Interval partitioning requires sorting by **start time** (sorting by finish time is used for Interval Scheduling / Max Non-overlapping Intervals). |
| **"The number of classrooms needed to schedule tasks is always strictly greater than the depth of intervals."** | **False** | Greedy interval partitioning achieves exactly `depth` classrooms, proving minimum classrooms equals depth. |
| **"In a Huffman tree, a character with higher frequency can have a greater depth than a character with lower frequency."** | **False** | If `depth(a) > depth(b)` while `f(a) > f(b)`, swapping their positions would strictly decrease total code length. |
| **"Huffman coding produces unique optimal prefix codes."** | **False** | Ties in frequency and arbitrary left/right child assignments yield different trees with identical total length. |
| **"Every internal node in a Huffman tree has exactly two children (full binary tree)."** | **True** | An internal node with only one child could be eliminated to shorten all downstream codes, contradicting optimality. |

