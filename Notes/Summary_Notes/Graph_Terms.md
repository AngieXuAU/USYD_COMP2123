### 📖 Essential Graph & Tree Terminology Cheat Sheet

Here is a clear reference guide comparing graph types and tree definitions so you never confuse them again:

#### Graph Terms
- **Simple Graph**: A graph with **no self-loops** (an edge from vertex `v` to `v`) and **no parallel/multiple edges** (multiple edges between the same two vertices `u` and `v`).
- **Connected Graph**: An undirected graph where there is at least one path between *every* pair of vertices.
- **Disconnected Graph**: A graph broken into separate pieces, called **Connected Components**.
- **Complete Graph (`K_n`)**: A simple graph where *every* pair of distinct vertices is connected by an edge. Has `n * (n - 1) / 2` edges.
- **Spanning Tree**: A subgraph that includes **all `n` vertices** of the original connected graph, connected together with exactly `n - 1` edges without any cycles.
- **Bipartite Graph**: A graph whose vertices can be split into two sets `A` and `B` such that every edge connects a vertex in `A` to a vertex in `B` (no edges within `A` or within `B`). Equivalently: a graph with **no odd cycles**.

#### Tree Terms
- **Depth of a node `v`**: The number of edges on the path from the **root down to node `v`**. (Root has `depth = 0`).
- **Height of a node `v`**: The number of edges on the longest path from node `v` **down to a leaf**. (Leaf has `height = 0`).
- **Height of a tree**: The height of its root node (length of longest path from root to leaf).
- **Full Binary Tree**: Every node has **either 0 or 2 children** (never just 1 child).
- **Complete Binary Tree**: All levels are completely filled except possibly the last level, which is filled from **left to right**. (Used in Binary Heaps).
- **Perfect Binary Tree**: All internal nodes have 2 children AND all leaves are at the exact same level/depth. Total nodes = `2^(h+1) - 1`.
- **Balanced / AVL Tree**: A Binary Search Tree where for *every* node, the height difference between its left and right subtrees (the **Balance Factor**) is at most **1** (`|height(left) - height(right)| <= 1`). Ensures `O(log n)` height.