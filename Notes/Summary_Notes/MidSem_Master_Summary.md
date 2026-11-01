# COMP2123 Exam Revision Master Summary & Study Guide (Weeks 1–7)

**Reference Exam Structure**: `Revision/instruction.txt`  
**Coverage**: Weeks 1 to 7 (Analysis, Stacks/Queues/Lists, Trees, BST/AVL, Priority Queues/Heaps, Hashing, Graphs)

---

## Executive Summary & Navigation Index

This master document synthesizes the core data structures, algorithm analysis techniques, and theoretical concepts covered in **COMP2123 Weeks 1 to 7**, specifically structured according to the three exam question formats specified in [`instruction.txt`](file:///c:/Users/angel/Repositories/USYD_COMP2123/Revision/instruction.txt).

### Detailed Weekly Summary Notes
- 📘 [**Week 1: Algorithm Analysis & Asymptotic Notation**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_1_Analysis_Summary.md)
- 📘 [**Week 2: Stacks, Queues, Lists & Amortized Analysis**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_2_Lists_Stacks_Queues_Summary.md)
- 📘 [**Week 3: Trees & Tree Traversals**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_3_Trees_Summary.md)
- 📘 [**Week 4: Binary Search Trees & AVL Trees**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_4_Binary_Search_Trees_AVL_Summary.md)
- 📘 [**Week 5: Priority Queues, Heaps & Heap-Sort**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_5_Priority_Queues_Heaps_Summary.md)
- 📘 [**Week 6: Hash Tables, Maps & Sets**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_6_Hashing_Maps_Sets_Summary.md)
- 📘 [**Week 7: Graph Representations, Traversals & Applications**](file:///c:/Users/angel/Repositories/USYD_COMP2123/Notes/Summary_Notes/Week_7_Graphs_Traversals_Summary.md)

---

## 1. Master Time & Space Complexity Cheat Sheet

Below is the definitive reference table comparing all major data structures across Weeks 1 to 7:

| Data Structure / Concept | Search / Access (Avg / Worst) | Insert (Avg / Worst) | Delete (Avg / Worst) | Auxiliary Space | Key Properties / Constraints |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Array Stack / Queue** | $O(1)$ | $O(1)^*$ | $O(1)$ | $O(N)$ | $O(1)$ amortized insert with doubling strategy |
| **Singly Linked List** | $O(n)$ | $O(1)$ front / $O(1)^**$ back | $O(1)$ front / $O(n)$ back | $O(n)$ | Deleting tail takes $O(n)$ even with tail pointer |
| **Doubly Linked List** | $O(n)$ | $O(1)$ | $O(1)$ | $O(n)$ | Sentinels (header/trailer) eliminate boundary checks |
| **General / Binary Tree** | $O(n)$ | $O(1)$ at position | $O(1)$ at position | $O(n)$ | $m = n - 1$ edges; Depth vs Height definitions |
| **Unbalanced BST** | $O(h) \to O(n)$ | $O(h) \to O(n)$ | $O(h) \to O(n)$ | $O(n)$ | Degenerates to $O(n)$ if keys inserted in order |
| **AVL Tree** | **$O(\log n)$** | **$O(\log n)$** | **$O(\log n)$** | $O(n)$ | Height-balance property $|h_L - h_R| \le 1$; $h < 1.44 \log_2 n$ |
| **Binary Min/Max Heap** | $O(1)$ min | **$O(\log n)$** | **$O(\log n)$** min | $O(n)$ | Array indexing ($2i, 2i+1, \lfloor i/2 \rfloor$); Bottom-up build $O(n)$ |
| **Hash Table (Chaining)** | $O(1+\alpha) / O(n)$ | $O(1) / O(n)$ | $O(1+\alpha) / O(n)$ | $O(n + N)$ | Load factor $\alpha = n/N$; allows $\alpha > 1$ |
| **Hash Table (Probing)** | $O(1) / O(n)$ | $O(1) / O(n)$ | $O(1) / O(n)$ | $O(N)$ | Requires $\alpha < 0.5$; `AVAILABLE` tombstones on delete |
| **Cuckoo Hashing** | **$O(1)$ Worst** | $O(1)$ Expected / $O(n)$ | **$O(1)$ Worst** | $O(N)$ | Checks max 2 slots; Evictions can trigger rehash |
| **Adjacency Matrix (Graph)** | $O(1)$ edge check | $O(1)$ edge insert | $O(1)$ edge delete | **$\Theta(n^2)$** | Best for dense graphs ($m \approx n^2$) |
| **Adjacency List (Graph)** | $O(\deg(u))$ edge check | $O(1)$ edge insert | $O(\deg(u))$ edge delete | **$\Theta(n + m)$** | Best for sparse graphs ($m \ll n^2$) |

*\* Amortized $O(1)$ time assuming array doubling capacity strategy.*  
*\*\* Requires maintaining an explicit tail reference pointer.*

---

## 2. Question 1 Strategy: True / False Conceptual Guide (10 Marks)

Question 1 consists of **10 True/False statements** testing high-level concepts, edge cases, and bounds across Weeks 1–7.

### Top 15 Must-Know T/F Exam Rules & Traps

1. **Asymptotic Upper Bounds vs Worst-Case**:
   - *Trap*: "Big-O means worst-case running time."
   - *Fact*: **False**. Big-O is a mathematical upper bound on a function. An algorithm can have an $O(n^2)$ upper bound on its best-case running time if defined loosely, though tight bounds $\Theta$ describe exact behavior.
2. **Polynomial vs Exponential Growth**:
   - *Fact*: Any positive exponential $c^n$ ($c > 1$) eventually grows faster than any polynomial $n^k$ ($k > 0$). Thus $n^{100} \in O(1.01^n)$.
3. **Singly Linked List Tail Deletion**:
   - *Fact*: In a Singly Linked List with `head` and `tail` pointers, deleting the tail takes **$O(n)$ time** because you must traverse from `head` to update `tail` to the predecessor.
4. **Dynamic Array Expansion**:
   - *Fact*: Array doubling yields **$O(1)$ amortized time** per push, but a single push triggering a resize takes **$O(n)$ worst-case time**.
5. **Proper Binary Tree Node Formulas**:
   - *Fact*: In any Proper (Full) Binary Tree, external nodes $e$ and internal nodes $i$ satisfy **$e = i + 1$** and total nodes **$n = 2e - 1 = 2i + 1$**.
6. **In-Order Traversal Sorting**:
   - *Fact*: An in-order traversal visits nodes in non-decreasing sorted order **IF AND ONLY IF** the tree is a Binary Search Tree (BST).
7. **AVL Tree Height Guarantee**:
   - *Fact*: An AVL tree with $n$ nodes has height strictly bounded by **$h < 1.44 \log_2 n = O(\log n)$**.
8. **AVL Insertion vs Deletion Restructuring**:
   - *Fact*: Insertion in an AVL tree requires **at most 1** trinode restructuring operation. Deletion may require **up to $O(\log n)$** restructurings cascading to the root.
9. **Heap Min/Max Element Locations**:
   - *Fact*: In a Min-Heap, the minimum element is always at the root ($O(1)$ access). The **maximum element** can be at any of the $\lceil n/2 \rceil$ leaf nodes ($O(n)$ search).
10. **Bottom-Up Heap Construction**:
    - *Fact*: Building a binary heap from an unsorted array of $n$ elements using bottom-up heapify takes **$O(n)$ time** (NOT $O(n \log n)$).
11. **Linear Probing Tombstones**:
    - *Fact*: When deleting from a linear probing hash table, setting a cell to empty/null breaks search chains. Cells must be marked with **`AVAILABLE` / Tombstones**.
12. **Cuckoo Hashing Lookup**:
    - *Fact*: Cuckoo hashing guarantees **$O(1)$ worst-case lookup time** because a key can only reside in $T_1[h_1(k)]$ or $T_2[h_2(k)]$.
13. **Handshaking Lemma**:
    - *Fact*: In any undirected graph, $\sum \deg(v) = 2m$. The number of odd-degree vertices is always **EVEN**.
14. **BFS Edge Layer Property**:
    - *Fact*: In BFS on an undirected graph, an edge can only connect vertices in the same layer ($L_i \to L_i$) or adjacent layers ($L_i \to L_{i \pm 1}$). **No cross-edges skip layers.**
15. **Bipartite Graphs & Odd Cycles**:
    - *Fact*: A graph is bipartite **if and only if it contains NO odd-length cycles**. Intra-layer edges in BFS prove a graph is not bipartite.

---

## 3. Question 2 Strategy: Short Answer Tracing Guide (8 Marks)

Question 2 requires working through small concrete examples. Below are the execution rules for tracing each data structure:

### 3.1 Tracing AVL Tree Restructuring (LL, RR, LR, RL)
When inserting or deleting breaks balance ($|h_L - h_R| > 1$):
1. Identify first unbalanced node $z$ going upwards.
2. Identify child $y$ of $z$ with higher height, and child $x$ of $y$ with higher height.
3. Rename $x, y, z$ in in-order order as $a, b, c$.
4. Re-hang the subtree with **$b$ as the new root**, $a$ as left child, $c$ as right child, and attach subtrees $T_1, T_2, T_3, T_4$ in in-order order.

### 3.2 Tracing Heap Operations (Up-Heap & Down-Heap)
- **Insert $k$**: Put $k$ at index $n+1$. Compare with parent $\lfloor i/2 \rfloor$. Swap if $k < \text{parent}$. Repeat upwards.
- **Remove Min**: Swap root $A[1]$ with last element $A[n]$. Remove $A[n]$. Compare root $A[1]$ with its children at $2i$ and $2i+1$. Swap with the **SMALLER child**. Repeat downwards.

### 3.3 Tracing Hash Table Collisions
- **Linear Probing**: $(h(k) + i) \bmod N$ for $i = 0, 1, 2, \dots$
- **Double Hashing**: $(h_1(k) + i \cdot h_2(k)) \bmod N$ for $i = 0, 1, 2, \dots$
- **Cuckoo Hashing**: Insert into $T_1[h_1(k)]$. If occupied by $x$, evict $x$ and insert $x$ into $T_2[h_2(x)]$. Repeat until no eviction or cycle detected.

---

## 4. Question 3 Strategy: Algorithm Design & Analysis (12 Marks)

Question 3 is the main problem-solving question. To get full marks, your answer **MUST** follow this 4-part structure:

### The Required 4-Part Exam Solution Template

```markdown
### Part 1: Main Idea & Algorithm Description
- High-level overview of the proposed data structure/algorithm.
- Step-by-step description of how the algorithm processes the input.

### Part 2: Additional Data Structures / Information Maintained
- Explicitly state any additional arrays, pointers, fields (e.g. subtree sizes, node heights, low-values, visited arrays) maintained.
- Explain how this extra information is initialized and kept updated during modifications.

### Part 3: Running Time & Space Analysis
- Time Complexity: State worst-case time using Big-O notation with respect to input size n (or vertices V and edges E). Break down costs step-by-step.
- Space Complexity: State auxiliary space used (excluding input).

### Part 4: Correctness Argument
- Provide a clear, logical explanation or inductive argument showing why the algorithm always produces the correct result for all input instances.
```

### Key Algorithm Design Patterns to Master
1. **Tree Augmentation (Weeks 3–4)**:
   - Augment tree nodes with `subtree_size` or `sum` to answer order-statistic or range-sum queries in $O(\log n)$ time.
2. **Two-Heap Pattern (Week 5)**:
   - Use a Max-Heap for lower half and Min-Heap for upper half to maintain the **running median** in $O(\log n)$ time per insertion and $O(1)$ query.
3. **Hash Map + Doubly Linked List (Week 6)**:
   - Combine Hash Table (fast $O(1)$ lookup) with Doubly Linked List (fast $O(1)$ deletion/re-ordering) for LRU Cache or fast element movement.
4. **Graph Traversal & Layering (Week 7)**:
   - Adapt BFS for shortest path or bipartite testing. Adapt DFS timestamps and `low[u]` values for cut-edge or cycle detection in $O(V + E)$ time.
