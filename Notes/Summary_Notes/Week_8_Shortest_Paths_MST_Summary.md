# Week 8 Summary Notes: Shortest Paths (Dijkstra) & Minimum Spanning Trees (Prim, Kruskal)

**Source PDF**: `Notes/Week 8 - w8_shortest_path_MST.pdf`  
**Target Exam Focus**: Questions 1 (T/F Dijkstra, Prim, Kruskal Properties & Bounds), 2 (Tracing Dijkstra & Prim/Kruskal MST executions), 3 (Algorithm Design for Weighted Graphs, Path & Tree Optimization)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–6** | **Weighted Graphs & Shortest Paths** | Edge weights, path cost, subpath optimality property, shortest path trees |
| **Slides 7–9** | **Dijkstra's Algorithm Design** | Greedy strategy, distance estimates `D[v]`, edge relaxation, priority queue |
| **Slides 10–28** | **Dijkstra Tracing Walk-Through** | Step-by-step vertex extraction, key updates, shortest path tree growth |
| **Slides 29–34** | **Dijkstra Analysis & Correctness** | `O(m log n)` complexity, Fibonacci heap `O(m + n log n)`, induction proof, negative weight limitation, directed graphs |
| **Slides 35–40** | **Minimum Spanning Trees (MST)** | Definition, network design applications, Cut Property, Cycle Property, cycle-cut intersection lemma |
| **Slides 41–61** | **Prim's Algorithm** | Greedy cut expansion, priority queue implementation, step-by-step tracing, `O(m log n)` analysis |
| **Slides 62–74** | **Kruskal's Algorithm & Union-Find** | Greedy edge selection, cycle check, Union-Find ADT (`make_sets`, `find`, `union`), list-based implementation |
| **Slide 75** | **Tiebreaking & Perturbation** | Distinct edge weights assumption, lexicographic tiebreaking |

---

## 2. Shortest Paths: Dijkstra's Algorithm

### 2.1 Problem Formulation & Fundamental Properties
- **Problem**: Given a connected, edge-weighted graph `G = (V, E)` with weights `w(e) >= 0` and a source vertex `s`, find shortest paths (minimum total weight) from `s` to all `v in V`.
- **Subpath Optimality Property**: Any subpath of a shortest path is itself a shortest path.
- **Shortest Path Tree (SPT)**: The union of shortest paths from source `s` to all reachable vertices forms a directed/undirected tree rooted at `s`.

---

### 2.2 Algorithm Mechanics & Edge Relaxation
- Maintain:
  - `S`: Set of vertices whose shortest distance from `s` is finalized.
  - `D[v]`: Current upper bound on distance from `s` to `v` (`D[s] = 0`, `D[v] = infinity` for `v != s`).
  - Priority Queue `Q`: Stores unvisited vertices `v in V \ S` keyed by `D[v]`.
- **Edge Relaxation**: When extracting vertex `u` with minimum `D[u]`:
  For each neighbor `z` of `u`:
  ```text
  if D[u] + w(u, z) < D[z]:
      D[z] = D[u] + w(u, z)
      parent[z] = u
      Q.update_priority(z, D[z])
  ```

---

### 2.3 Complexity Analysis

Assuming connected graph (`m >= n - 1`):
- `insert`: `n` operations
- `remove_min`: `n` operations
- `decrease_key` (via relaxation): At most `m` operations

| Priority Queue Implementation | `remove_min` | `decrease_key` | Total Running Time |
| :--- | :---: | :---: | :---: |
| **Unsorted Array / List** | `O(n)` | `O(1)` | `O(n^2 + m) = O(n^2)` (Optimal for dense graphs `m = Theta(n^2)`) |
| **Standard Binary Heap** | `O(log n)` | `O(log n)` | **`O(m log n)`** (Standard exam complexity) |
| **Fibonacci Heap** | `O(log n)` amortized | `O(1)` amortized | **`O(m + n log n)`** |

---

### 2.4 Critical Dijkstra Constraints & Properties
1. **Non-negative Edge Weights**: Dijkstra **fails** on graphs with negative edge weights.
   - *Why?* Dijkstra assumes once a vertex `u` is added to `S`, `D[u]` is permanently optimal. A negative weight edge encountered later could provide a cheaper alternative path to `u`, violating the greedy choice.
2. **Directed vs Undirected**: Dijkstra works equally well on directed graphs (assuming no negative weights), provided directed paths are followed.
3. **Unweighted Graphs**: On unweighted graphs, standard **BFS** finds shortest paths faster in `O(n + m)` time.

---

## 3. Minimum Spanning Trees (MST)

### 3.1 Definition & Foundational Theorems
- **MST**: Given a connected, undirected graph `G = (V, E)` with edge weights `c(e)`, an MST is a spanning subgraph `T` that is a tree (contains `n - 1` edges, connects all `n` vertices, contains no cycles) with minimum total edge weight `sum_{e in T} c(e)`.

#### Cycle-Cut Intersection Lemma
- A cycle `C` and a cutset `D` (the set of edges crossing cut `(S, V \ S)`) intersect in an **even number of edges**.

#### The Cut Property (Min-Edge Crossing a Cut)
- Let `S` be any subset of nodes (`S != empty`, `S != V`), and let `e` be the minimum cost edge crossing the cut `(S, V \ S)`. Then **`e` belongs to every MST** (assuming distinct edge weights).
- *Proof (Exchange Argument)*: If `e not in T*`, adding `e` creates a cycle `C`. By cycle-cut intersection, there exists another edge `f in C` crossing `(S, V \ S)`. Since `c(e) < c(f)`, the tree `T' = T* U {e} \ {f}` is spanning and has strictly smaller cost, contradicting minimality of `T*`.

#### The Cycle Property (Max-Edge in a Cycle)
- Let `C` be any cycle in `G`, and let `f` be the maximum cost edge in `C`. Then **`f` cannot belong to any MST** (assuming distinct edge weights).

#### Handling Non-Distinct Edge Weights
- If edge weights are not distinct, MST is not necessarily unique. Ties can be broken deterministically using **lexicographic tiebreaking** (e.g. comparing unique edge ID/indices).

---

## 4. MST Algorithms: Prim vs Kruskal

### 4.1 Prim's Algorithm (Cut-Growing Strategy)
- **High-Level Concept**: Starts at an arbitrary root vertex `s`. Maintains tree `S` and repeatedly selects the cheapest edge `(u, v)` crossing cut `(S, V \ S)`.
- **Implementation**:
  - Maintain `d[v]` for all `v in V \ S`: minimum weight of an edge connecting `v` to any node in `S`.
  - Use Min-Heap `Q` of vertices keyed by `d[v]`.
  - At each step, extract `u = Q.remove_min()`, add `u` to `S`, and for each incident edge `(u, v)` with `v not in S`, if `c(u, v) < d[v]`, decrease `d[v] = c(u, v)`.
- **Time Complexity**: **`O(m log n)`** with binary heap; **`O(m + n log n)`** with Fibonacci heap.

---

### 4.2 Kruskal's Algorithm (Cycle-Avoiding Strategy)
- **High-Level Concept**: Sorts all `m` edges globally by increasing weight. Iterates through sorted edges: if adding edge `e = (u, v)` does not create a cycle, add `e` to `T`; otherwise discard `e`.
- **Implementation via Union-Find ADT**:
  - `make_sets(V)`: Initializes `n` disjoint sets (1 call).
  - `find(u)`: Returns component ID containing `u` (`2m` calls, testing endpoints).
  - `union(u, v)`: Merges components of `u` and `v` (`n - 1` calls when edge accepted).
- **Time Complexity**:
  - Edge sorting: `O(m log m) = O(m log n)`.
  - Simple list-based Union-Find: `O(n^2)` total time for unions.
  - Disjoint Set Forest (with union-by-rank & path compression): `O(m alpha(n))` for UF ops, giving overall time **`O(m log n)`** (dominated by sorting).

---

## 5. Comparison: Dijkstra vs Prim vs Kruskal

| Feature | Dijkstra's Algorithm | Prim's Algorithm | Kruskal's Algorithm |
| :--- | :--- | :--- | :--- |
| **Problem Solved** | Single-Source Shortest Paths (SSSP) | Minimum Spanning Tree (MST) | Minimum Spanning Tree (MST) |
| **Graph Type** | Directed or Undirected, non-negative weights | Undirected, weighted (negative weights allowed!) | Undirected, weighted (negative weights allowed!) |
| **Greedy Choice** | Smallest `D[u] = dist(s, u)` from source | Smallest edge connecting tree `S` to `V \ S` | Smallest global edge that doesn't create a cycle |
| **Negative Weights?** | **NO** (Fails) | **YES** (Works correctly) | **YES** (Works correctly) |
| **Primary Data Structure** | Min-Heap Priority Queue | Min-Heap Priority Queue | Union-Find (Disjoint Sets) + Sorted List |
| **Time Complexity** | `O(m log n)` | `O(m log n)` | `O(m log n)` |

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"Dijkstra's algorithm always finds the shortest path even if some edge weights are negative, provided there are no negative cycles."** | **False** | Dijkstra can fail even with a single negative edge because finalized nodes in `S` are never re-evaluated. |
| **"Prim's algorithm and Kruskal's algorithm work correctly even if edge weights are negative."** | **True** | MST definitions and Cut/Cycle properties hold for all real numbers (positive, zero, negative). |
| **"If all edge weights in a connected undirected graph are distinct, the MST is unique."** | **True** | At every cut, the minimum crossing edge is strictly defined, yielding a unique MST. |
| **"The shortest path tree from source `s` computed by Dijkstra is always a Minimum Spanning Tree."** | **False** | An SPT minimizes path distance from `s`, not total sum of edge weights (e.g. star graph vs line graph). |
| **"Adding a positive constant `c` to every edge weight leaves the MST unchanged."** | **True** | Every spanning tree has exactly `n - 1` edges, so every spanning tree's total weight increases by exactly `(n - 1) * c`, preserving ordering. |
| **"Adding a positive constant `c` to every edge weight leaves the shortest paths between all pairs unchanged."** | **False** | Paths with more edges are penalized more than paths with fewer edges; shortest path structure can change completely. |
| **"If an edge `e` has the strictly minimum weight in the whole graph, `e` must belong to every MST."** | **True** | Take cut separating one endpoint of `e` from the rest of the graph; `e` is the min-cost crossing edge. |
| **"If an edge `e` has the strictly maximum weight in the whole graph, `e` cannot belong to any MST."** | **False** | If `e` is a bridge (cut-edge) whose removal disconnects the graph, it MUST belong to every spanning tree. |

