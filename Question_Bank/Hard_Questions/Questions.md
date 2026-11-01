# Hard Questions Bank

---

## Question 1: Get-Stuck Vertex Detection in O(n) Time (Universal Sink)

**Tags**: `#Graphs` `#Adjacency-Matrix` `#Universal-Sink` `#Linear-Time-Elimination` `#Algorithm-Design`

### Problem Statement
In a directed graph G = (V, E) with n vertices labeled 1, ..., n, a **get-stuck vertex** (also known as a **universal sink**) is defined as a vertex with:
1. **In-degree = n - 1**: Every other vertex in the graph has a directed edge pointing into it.
2. **Out-degree = 0**: It has no outgoing edges to any vertex (including itself).

Assume the graph is represented as an n x n **Adjacency Matrix** A, where:
- `A[i][j] = 1` if there is a directed edge from vertex i to vertex j
- `A[i][j] = 0` otherwise

Design an O(n) time algorithm to determine whether graph G contains a get-stuck vertex.

> **Constraint Note**: An adjacency matrix has n^2 total entries. A naive search checking every entry takes O(n^2) time. This problem must be solved in O(n) time without examining the entire input matrix.

---
* **Solution File**: [Solutions.md#solution-1-get-stuck-vertex-detection-universal-sink](file:///c:/Users/angel/Repositories/USYD_COMP2123/Question_Bank/Hard_Questions/Solutions.md#solution-1-get-stuck-vertex-detection-universal-sink)

---

## Question 2: Minimum Reachable Vertex (small(i)) in O(n + m) Time

**Tags**: `#Graphs` `#DFS` `#Connected-Components` `#Reachability` `#Linear-Time`

### Problem Statement
Let G = (V, E) be an undirected graph with vertices numbered 1, ..., n.
For a vertex i, define `small(i) = min{j : j is reachable from i}`, that is, the smallest vertex label reachable from vertex i.

Design an O(n + m) time algorithm that computes `small(i)` for every vertex in the graph.

---
* **Solution File**: [Solutions.md#solution-2-minimum-reachable-vertex-smalli](file:///c:/Users/angel/Repositories/USYD_COMP2123/Question_Bank/Hard_Questions/Solutions.md#solution-2-minimum-reachable-vertex-smalli)
