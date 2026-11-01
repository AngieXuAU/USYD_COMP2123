# Hard Questions Solutions

---

## Solution 1: Get-Stuck Vertex Detection (Universal Sink)

**Tags**: `#Graphs` `#Adjacency-Matrix` `#Universal-Sink` `#Linear-Time-Elimination` `#Algorithm-Design`  
**Question Link**: [Questions.md#question-1-get-stuck-vertex-detection-in-on-time-universal-sink](file:///c:/Users/angel/Repositories/USYD_COMP2123/Question_Bank/Hard_Questions/Questions.md#question-1-get-stuck-vertex-detection-in-on-time-universal-sink)

---

### Core Intuition: Candidate Elimination Rule
Why can we avoid checking all n^2 entries?

Consider querying any single matrix cell `A[i][j]` where i is not equal to j:

- **Case 1: A[i][j] == 1**
  - There is a directed edge i -> j.
  - Therefore, vertex i has an out-degree of at least 1 (which is not 0).
  - **Conclusion**: Vertex i **cannot** be a get-stuck vertex. We safely **eliminate row i** from candidacy.

- **Case 2: A[i][j] == 0**
  - There is **no** directed edge i -> j.
  - Therefore, vertex j is missing an incoming edge from i, so its in-degree can be at most n - 2 (which is not n - 1).
  - **Conclusion**: Vertex j **cannot** be a get-stuck vertex. We safely **eliminate column j** from candidacy.

> **Key Insight**: A single O(1) matrix lookup `A[i][j]` **guarantees the elimination of at least one vertex** (either i or j) as a potential get-stuck vertex!

---

### Algorithm Walkthrough

#### Step 1: Matrix Walk (Candidate Elimination)
We maintain two pointers: row index `i = 1` and column index `j = 1`.

1. Start at top-left cell `(1, 1)`.
2. Loop while `i <= n` and `j <= n`:
   - If `i == j`: Increment `j = j + 1` (skip diagonal).
   - Else if `A[i][j] == 1`: Vertex i is disqualified -> move down (`i = i + 1`).
   - Else if `A[i][j] == 0`: Vertex j is disqualified -> move right (`j = j + 1`).
3. When the loop terminates (either `i > n` or `j > n`), the remaining row index `i` (if `i <= n`) is the **only possible candidate**. If `i > n`, no get-stuck vertex exists.

#### Step 2: Candidate Verification
Because elimination only compares pairs, we must confirm whether candidate `i` satisfies both get-stuck conditions:
1. **Out-degree check**: Verify row `i` contains all 0s: `A[i][k] == 0` for all `k` from 1 to n.
2. **In-degree check**: Verify column `i` contains all 1s (except diagonal `A[i][i]`): `A[k][i] == 1` for all `k != i`.

If candidate `i` passes both checks, output **Vertex i is a get-stuck vertex**. Otherwise, output **No get-stuck vertex exists**.

---

### Complexity Analysis

- **Elimination Walk**: At each step, we either increment `i` or `j`. Since `1 <= i, j <= n`, the loop executes at most `2n` times. Each step performs an O(1) lookup.
  - Walk Time = O(n)

- **Verification Step**: Inspecting row `i` (n entries) and column `i` (n - 1 entries) takes `2n - 1` lookups.
  - Verification Time = O(n)

- **Total Time Complexity**: O(n) + O(n) = O(n)
- **Space Complexity**: O(1) auxiliary space (only pointer variables `i` and `j`).

---
---

## Solution 2: Minimum Reachable Vertex (small(i))

**Tags**: `#Graphs` `#DFS` `#Connected-Components` `#Reachability` `#Linear-Time`  
**Question Link**: [Questions.md#question-2-minimum-reachable-vertex-smalli-in-on--m-time](file:///c:/Users/angel/Repositories/USYD_COMP2123/Question_Bank/Hard_Questions/Questions.md#question-2-minimum-reachable-vertex-smalli-in-on--m-time)

---

### Core Intuition: Component Equivalence of Reachability
In an **undirected graph**, reachability is an equivalence relation (symmetric and transitive):
- If vertex `x` can reach vertex `y`, then vertex `y` can also reach vertex `x`.
- Therefore, for any connected component `C`, **every vertex in `C` can reach every other vertex in `C`**.

Thus, for any vertex `b` in component `C`:
- The set of reachable vertices from `b` is the entire component `C`.
- Therefore, `small(b) = min{ j : j in C }` for all vertices `b` in `C`.

> **Key Insight**: Every vertex in the same connected component shares the exact same `small(i)` value, which is simply the minimum vertex ID present in that component!

---

### Algorithm Walkthrough

1. **Find Connected Components via DFS**:
   - Run Depth-First Search (DFS) on graph G to group vertices into connected components `C1, C2, ..., Ck`.
2. **Process Each Component**:
   - For each connected component `C`:
     - Scan the vertex IDs in `C` to find `min_val = min(C)`.
     - For every vertex `b` in `C`, set `small[b] = min_val`.

---

### Complexity Analysis

- **DFS Graph Traversal**: Running DFS visits all `n` vertices and `m` edges once.
  - DFS Time = O(n + m)

- **Component Scanning & Min Finding**: Across all components `C1, ..., Ck`, the sum of sizes is `sum(size(Ci)) = n`. Finding the minimum label in each component takes `O(n)` total time.
  - Min Finding Time = O(n)

- **Assigning Result Array**: Updating `small[b] = min_val` for every vertex takes `sum(size(Ci)) = n` total direct array writes.
  - Assignment Time = O(n)

- **Total Time Complexity**: `O(n + m) + O(n) + O(n) = O(n + m)`
- **Space Complexity**: `O(n)` auxiliary space for visited array, component vertex lists, and result array `small`.
