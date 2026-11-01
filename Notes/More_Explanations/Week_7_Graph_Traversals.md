# Detailed Explanations: Week 7 Graph Traversals

This document summarizes all key concept clarifications, intuitive breakdowns, and mathematical nuances discussed during the Week 7 study session.

---

## 1. Asymptotic Notation: Understanding Big-Theta `Theta(n)`

- **Big-O `O(n)`**: Upper bound ("runs in at most `n` steps").
- **Big-Omega `Omega(n)`**: Lower bound ("runs in at least `n` steps").
- **Big-Theta `Theta(n)`**: Tightly bounded both from above and below (`O(n)` AND `Omega(n)`).

### Practical Meaning
When an algorithm operation is `Theta(n)`, its execution time grows linearly **regardless of the input data structure contents**. A "more suitable" or sparse input will **not** make the algorithm faster because it is forced to execute all `n` loop iterations (e.g. scanning all `n` cells in an Adjacency Matrix row).

---

## 2. Graph Representation Operations & Complexities

### 2.1 Adjacency Matrix (`n x n` grid)
- **Finding Outgoing Neighbors of `u`**: `Theta(n)` time.
  - *Reason*: Must iterate through every column `0` to `n-1` in row `u`.
- **Finding Incoming Neighbors of `u` (Directed)**: `Theta(n)` time.
  - *Reason*: Must scan column `u` from row `0` to `n-1`.
- **Checking Edge `(u, v)` Existence**: `O(1)` time.
  - *Reason*: Direct array lookup `Matrix[u][v]`.

### 2.2 Adjacency List (Array of linked lists/vectors)
- **Inserting Edge `(u, v)`**: `O(1)` time.
  - *Reason*: Prepending node `v` to the head of `u`'s list takes a constant number of pointer assignments regardless of graph size.
- **Deleting Edge `(u, v)`**: `O(deg(u))` time.
  - *Reason*: Must iterate sequentially through `u`'s list to locate node `v` before unlinking it.
- **Checking Edge `(u, v)` Existence**: `O(deg(u))` time.

### 2.3 Edge List (Array of edge pairs)
- **Checking Edge `(u, v)` Existence**: `O(m)` time.
  - *Reason*: Must perform a linear scan across all `m` edge pairs in the array.

---

## 3. Bipartite Graphs & Cycle Parity

### 3.1 What is an Odd Cycle vs. Even Cycle?
- **Cycle Length**: The total number of edges (or jumps) required to start at a vertex and travel back to itself.
- **Odd Cycle**: A cycle with an odd number of edges (e.g., length 3 triangle `A -> B -> C -> A`).
- **Even Cycle**: A cycle with an even number of edges (e.g., length 4 square `A -> B -> C -> D -> A`).

### 3.2 Why Bipartite Graphs Allow Even Cycles but Forbid Odd Cycles
A graph is bipartite if vertices can be colored using **2 colors** (Red and Blue) such that adjacent vertices have different colors.

Tracing a cycle starting from a **Red** node:
- Jump 1: Blue
- Jump 2: Red
- Jump 3: Blue
- Jump 4: Red (Back to start!)

- **Even number of jumps**: Returns to the starting color (**Red**), which maintains 2-coloring. Thus, **even cycles are allowed**.
- **Odd number of jumps**: Lands on the opposite color (**Blue**). An odd cycle ending back at the start node forces that node to be both Red and Blue simultaneously, which is impossible. Thus, **odd cycles are strictly forbidden**.

---

## 4. BFS Cross Edges & Bipartite Testing

### 4.1 What makes an edge a Cross Edge in BFS?
Any edge `(u, v)` that was **not used to discover an unvisited vertex** (because `v` was already visited via a different parent) is classified as a **Cross Edge**.

### 4.2 Types of Cross Edges in BFS
In an undirected graph BFS, cross edges can be:
1. **Intra-layer Cross Edges**: Connecting two vertices in the **same layer** (`L_i` to `L_i`).
2. **Inter-layer Cross Edges**: Connecting two vertices in **adjacent layers** (`L_i` to `L_(i+1)`).

### 4.3 Practical Application: Bipartite Testing
Standard BFS ignores cross edges when finding shortest paths. However, in **Bipartite Testing**, BFS actively checks every edge `(u, v)`:
- If `layer[u] == layer[v]` (an **intra-layer cross edge**), it proves an **odd cycle** exists.
- The algorithm immediately terminates and returns `False` (Not Bipartite).

---

## 5. DFS Edge Classification: Undirected vs. Directed Graphs

### 5.1 Why Forward and Cross Edges Cannot Exist in Undirected DFS
In an undirected graph, edge `(u, v)` works in both directions (`u -> v` and `v -> u`).

When DFS is at node `u`:
- If `v` is unvisited, DFS immediately explores `v` as a **Tree Edge**.
- If `v` was already visited, `v` must be an ancestor of `u` higher up on the active path, making `(u, v)` a **Back Edge**.

Because DFS explores as deep as possible before backtracking, it will never leave `(u, v)` unvisited to be discovered later in a separate branch. Thus:
> In an undirected DFS tree, **every non-tree edge is a Back Edge**.

### 5.2 Directed DFS Edge Classification via Timestamps & States
Using Discovery Time `d[x]` and Finish Time `f[x]` when inspecting edge `(u, v)`:

- **Tree Edge**: Target `v` is `UNVISITED`.
- **Back Edge**: Target `v` is `VISITING` (active on stack, `d[v] < d[u]`). **Indicates a Cycle!**
- **Forward Edge**: Target `v` is `VISITED` and `d[u] < d[v]` (`u` discovered before `v`; `v` is a descendant).
- **Cross Edge**: Target `v` is `VISITED` and `d[u] > d[v]` (`u` discovered after `v`; `v` is in an already-completed branch).

---

## 6. Cut-Edges (Bridges) & Cut-Vertices (Articulation Points)

### 6.1 Cut-Edge (Bridge) Condition: `low[v] > discovery_time[u]`
- `discovery_time[u]`: Timestamp when node `u` was first visited.
- `low[v]`: Smallest discovery timestamp reachable from `v`'s subtree using tree-edges and at most one back-edge.

- **If `low[v] <= discovery_time[u]`**: `v`'s subtree has a back-edge (backdoor path) connecting back to `u` or an ancestor of `u`. Cutting edge `(u, v)` will **not** disconnect `v`'s subtree. `(u, v)` is **NOT a Bridge**.
- **If `low[v] > discovery_time[u]`**: `v`'s subtree has **no back-edges** reaching `u` or higher. Edge `(u, v)` is the **only** link connecting `v`'s subtree to the rest of the graph. Cutting `(u, v)` disconnects the graph. `(u, v)` **IS a Bridge**.

### 6.2 Root Cut-Vertex Rule
The root of a DFS tree is a Cut-Vertex **if and only if it has 2 or more children in the DFS tree**.
- If the root has only 1 child in the DFS tree, all other nodes are descendants of that single child and remain connected if the root is removed.
