# Week 7 Summary Notes: Graph Representations, Traversals & Applications

**Source PDF**: `Notes/Week 7 - Graphs.pdf`  
**Target Exam Focus**: Questions 1 (T/F Graph Definitions & Edge Bounds), 2 (BFS/DFS Tracing & Bipartiteness), 3 (Graph Algorithm Design, Cut-Edges/Vertices, & Cycle Detection)

---

## 1. Slide Structure & Content Overview

| Section | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Section 1** | **Graph Concepts & Representations** | Vertices $V$, Edges $E$, Handshaking Lemma, Adjacency Matrix vs Adjacency List |
| **Section 2** | **Graph Traversals** | Breadth-First Search (BFS), Layer Structures, Depth-First Search (DFS) |
| **Section 3** | **Edge Classification** | Tree edges, Back edges, Forward edges, Cross edges |
| **Section 4** | **Algorithmic Applications** | Shortest path (unweighted), Bipartite testing, Cycle detection, Cut-edges & Cut-vertices |

---

## 2. Core Definitions & Graph Metrics

### 2.1 Graph Terminology & Handshaking Lemma
- **Simple Graph**: Graph with no self-loops (edges from $v$ to $v$) and no parallel edges.
- **Degree $\deg(v)$**: Number of edges incident to vertex $v$.
- **Handshaking Lemma (Undirected Graph)**:
  $$\sum_{v \in V} \deg(v) = 2 |E| = 2m$$
  *(Consequence: The number of vertices with odd degree is always EVEN).*
- **Handshaking Lemma (Directed Graph)**:
  $$\sum_{v \in V} \text{indeg}(v) = \sum_{v \in V} \text{outdeg}(v) = |E| = m$$

---

### 2.2 Vertex & Edge Bounds
For a simple graph with $n = |V|$ vertices and $m = |E|$ edges:
- **Undirected Graph**: $0 \le m \le \frac{n(n-1)}{2}$
- **Directed Graph**: $0 \le m \le n(n-1)$
- **Sparse Graph**: $m = O(n)$
- **Dense Graph**: $m = \Theta(n^2)$

---

## 3. Graph Representation Summary Table

| Operations / Space | Adjacency Matrix | Adjacency List | Edge List |
| :--- | :---: | :---: | :---: |
| **Space Complexity** | $\Theta(n^2)$ | **$\Theta(n + m)$** | $\Theta(n + m)$ |
| **Check Edge $(u, v)$ Exists** | **$O(1)$** | $O(\deg(u))$ | $O(m)$ |
| **Find All Neighbors of $u$** | $\Theta(n)$ | **$O(\deg(u))$** | $O(m)$ |
| **Insert Vertex** | $O(n^2)$ (resize matrix) | $O(1)$ | $O(1)$ |
| **Insert Edge $(u, v)$** | $O(1)$ | $O(1)$ | $O(1)$ |
| **Delete Edge $(u, v)$** | $O(1)$ | $O(\deg(u))$ | $O(m)$ |
| **Best Used When** | Dense graphs ($m \approx n^2$) | **Sparse graphs** ($m \ll n^2$) | Edge-focused algorithms |

---

## 4. Graph Traversals: BFS vs DFS

### 4.1 Breadth-First Search (BFS)
- **Data Structure**: **Queue** (FIFO).
- **Behavior**: Visits graph level-by-level / layer-by-layer ($L_0, L_1, L_2, \dots$).
- **Key Property**: Finds the **shortest path** (minimum number of edges) from source $s$ to all reachable vertices in an unweighted graph.
- **Time Complexity**: $O(n + m)$ using Adjacency List, $O(n^2)$ using Adjacency Matrix.
- **Space Complexity**: $O(n)$ for queue and visited markers.

#### BFS Edge Classification (Undirected Graph)
- **Tree Edges**: Edges used to discover unvisited vertices. Form a BFS spanning tree/forest.
- **Cross Edges**: Edges connecting vertices already visited.
  - *Key Theorem*: In BFS, for any edge $(u, v)$ with $u \in L_i$ and $v \in L_j$, we have:
    $$|i - j| \le 1$$
    *(Edges can only exist within the same layer $L_i \to L_i$ or between adjacent layers $L_i \to L_{i+1}$ / $L_i \to L_{i-1}$. There are NO edges skipping layers!)*

---

### 4.2 Depth-First Search (DFS)
- **Data Structure**: **Call Stack** (Recursion) or explicit Stack.
- **Behavior**: Traverses as deep as possible along a branch before backtracking.
- **Time Complexity**: $O(n + m)$ using Adjacency List.
- **Space Complexity**: $O(n)$ for recursion stack.

#### DFS Edge Classification Summary Table

| Edge Type | Description | Indicates | Directed / Undirected |
| :--- | :--- | :--- | :---: |
| **Tree Edge** | Edge $(u, v)$ where $v$ was unvisited when explored from $u$ | Primary discovery path | Both |
| **Back Edge** | Edge $(u, v)$ connecting $u$ to an **ancestor** $v$ in DFS tree | **Presence of a CYCLE!** | Both |
| **Forward Edge** | Edge $(u, v)$ connecting $u$ to a non-child **descendant** $v$ | Shortcut in subtree | Directed Only |
| **Cross Edge** | Edge $(u, v)$ connecting $u$ to a vertex $v$ in a different branch | Cross-branch link | Directed Only |

---

## 5. Major Algorithmic Applications (Question 3 Preparation)

### 5.1 Bipartite Graph Testing ($O(n + m)$ Time)
- **Definition**: $G=(V, E)$ is bipartite iff $V$ can be partitioned into $A, B$ such that no edges connect vertices within the same set.
- **Theorem**: A graph is bipartite **if and only if it contains NO odd cycles**.
- **Algorithm**:
  1. Run BFS starting from an arbitrary vertex $s$. Assign $s$ to layer $L_0$.
  2. For every edge $(u, v)$:
     - If $u \in L_i$ and $v \in L_j$ where $i = j$ (**intra-layer edge**), the graph contains an odd cycle $\implies$ **NOT Bipartite**.
  3. If all edges connect adjacent layers ($i \neq j$), color even layers set $A$ and odd layers set $B$ $\implies$ **Bipartite!**

---

### 5.2 Cycle Detection ($O(n + m)$ Time)
- **Undirected Graph**: Run DFS. If an edge $(u, v)$ leads to an already visited vertex $v$ that is NOT the parent of $u$, then $(u, v)$ is a **Back Edge** $\implies$ **Cycle detected**.
- **Directed Graph**: Maintain state for each vertex (`UNVISITED`, `VISITING` [on stack], `VISITED`). If an edge points to a node in `VISITING` state $\implies$ **Directed Cycle detected**.

---

### 5.3 Cut Edges (Bridges) & Cut Vertices (Articulation Points)

#### Definitions
- **Cut Edge (Bridge)**: An edge whose removal increases the number of connected components.
- **Cut Vertex**: A vertex whose removal increases the number of connected components.

#### DFS Timestamps & Low Values (`down-and-up`)
- Assign each vertex $u$ a discovery timestamp `discovery_time[u]`.
- Define `low[u]` as the minimum discovery timestamp reachable from $u$ using at most one back-edge:
  $$\text{low}[u] = \min \begin{cases} \text{discovery\_time}[u] \\ \text{discovery\_time}[w] & \text{for back-edges } (u, w) \\ \text{low}[v] & \text{for tree-edges } (u, v) \end{cases}$$

#### Identification Criteria
1. **Cut Edge Criterion**: Edge $(u, v)$ (where $u = \text{parent}(v)$) is a Cut Edge **iff**:
   $$\text{low}[v] > \text{discovery\_time}[u]$$
   *(Meaning subtree at $v$ has NO back-edge reaching $u$ or any ancestor of $u$).*

2. **Cut Vertex Criterion**: Vertex $u$ is a Cut Vertex **iff**:
   - **Case 1 ($u$ is root of DFS tree)**: $u$ has **$\ge 2$ children** in the DFS tree.
   - **Case 2 ($u$ is non-root of DFS tree)**: $u$ has a child $v$ such that:
     $$\text{low}[v] \ge \text{discovery\_time}[u]$$

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"BFS on an unweighted graph finds the shortest path distance from source $s$ to all reachable vertices."** | **True** | Queue FIFO order explores vertices strictly by increasing edge distance. |
| **"In an undirected graph, an edge connecting two vertices in the same BFS layer proves the graph is NOT bipartite."** | **True** | An intra-layer edge forms an odd-length cycle, violating bipartiteness. |
| **"For sparse graphs where $m = O(n)$, an Adjacency Matrix representation uses less space than an Adjacency List."** | **False** | Adjacency Matrix uses $\Theta(n^2)$ space regardless of $m$, whereas Adjacency List uses $\Theta(n + m) = \Theta(n)$ space. |
| **"In a DFS of an undirected graph, every non-tree edge is a Back Edge."** | **True** | Undirected DFS trees cannot produce Forward or Cross edges. |
| **"The root of a DFS tree is always a cut vertex."** | **False** | The root is a cut vertex IF AND ONLY IF it has 2 or more children in the DFS tree. |
