# Week 3 Summary Notes: Trees & Tree Traversals

**Source PDF**: `Notes/Week 3 - w3_trees.pdf`  
**Target Exam Focus**: Questions 1 (T/F Concepts & Height Properties), 2 (Traversal Tracing & Tree Calculations), 3 (Recursive Tree Algorithm Design)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–5** | **Tree Concepts & Definitions** | Root, parent, child, ancestors, descendants, internal/external nodes |
| **Slides 6–10** | **Tree Metrics & Properties** | Depth of a node, Height of a node, Height of a tree, Node/Edge counting |
| **Slides 11–16** | **Tree ADT Interface** | `root()`, `parent(p)`, `children(p)`, `isInternal(p)`, `isExternal(p)` |
| **Slides 17–20** | **Tree Traversals** | Pre-order, Post-order, In-order, Euler Tour traversals |
| **Slides 21–26** | **Binary Trees** | Proper/Full binary trees, Height bounds, Array vs Linked representation |

---

## 2. Core Definitions & Mathematical Properties

### 2.1 Terminology & Classification
- **Root**: The unique node without a parent (depth 0).
- **Internal Node**: A node with at least one child.
- **External Node (Leaf)**: A node with no children.
- **Ancestors of $v$**: Parent of $v$, parent's parent, ..., up to the root (includes $v$ if specified, or strict ancestors excluding $v$).
- **Descendants of $v$**: Children of $v$, children's children, ..., down to leaves.
- **Subtree $T_v$**: Tree rooted at node $v$, consisting of $v$ and all its descendants.

---

### 2.2 Mathematical Metrics

#### Depth vs Height Formulas
- **Depth of node $v$**: Number of ancestors of $v$ (excluding $v$).
  $$depth(root) = 0, \quad depth(v) = 1 + depth(parent(v))$$
  - Maximum depth in a tree equals the height of the tree.
- **Height of node $v$**: Length of the longest path from $v$ down to an external node (leaf).
  $$height(leaf) = 0, \quad height(v) = 1 + \max_{c \in children(v)} height(c)$$
- **Height of a tree $T$**: $height(root)$.

#### Fundamental Tree Properties
For any tree $T$ with $n$ nodes and $m$ edges:
$$m = n - 1$$

---

### 2.3 Binary Tree Special Types & Bounds

#### Binary Tree Definitions
- **Binary Tree**: A tree where every internal node has **at most 2 children** (labeled left child and right child).
- **Proper / Full Binary Tree**: Every internal node has **exactly 2 children** (no node has only 1 child).
- **Perfect Binary Tree**: A proper binary tree in which all leaves have the exact same depth.
- **Complete Binary Tree**: Every level is completely filled, except possibly the last level, which is filled strictly from left to right.

#### Proper Binary Tree Summary Table of Relations

| Property | Symbol / Formula | Notes |
| :--- | :--- | :--- |
| **External Nodes ($e$) vs Internal Nodes ($i$)** | $e = i + 1$ | Holds for all Proper Binary Trees |
| **Total Nodes ($n$) vs Internal Nodes ($i$)** | $n = 2i + 1$ | $n$ is always odd in a proper binary tree |
| **Total Nodes ($n$) vs External Nodes ($e$)** | $n = 2e - 1$ | $e = \frac{n+1}{2}$ |
| **Minimum Height for $n$ nodes** | $h \ge \lceil \log_2(n+1) \rceil - 1$ | Achieved by Perfect / Complete binary tree |
| **Maximum Height for $n$ nodes** | $h \le \frac{n-1}{2}$ | Achieved by degenerate proper tree (chain) |
| **Minimum Nodes for height $h$** | $n \ge 2h + 1$ | Degenerate proper tree |
| **Maximum Nodes for height $h$** | $n \le 2^{h+1} - 1$ | Perfect binary tree |

---

## 3. Tree Traversals (Question 2 Tracing & Code Patterns)

```text
       ( A )
      /     \
    ( B )   ( C )
   /     \
 ( D )   ( E )
```

### 3.1 Pre-Order Traversal
- **Order**: Visit current node $v$, then recursively traverse left subtree, then right subtree.
- **Algorithm**:
  ```python
  def preorder(v):
      visit(v)
      for c in children(v):
          preorder(c)
  ```
- **Trace for Example**: `A -> B -> D -> E -> C`
- **Application**: Printing structured documents, directory structure listing.

### 3.2 Post-Order Traversal
- **Order**: Recursively traverse left subtree, then right subtree, then visit current node $v$.
- **Algorithm**:
  ```python
  def postorder(v):
      for c in children(v):
          postorder(c)
      visit(v)
  ```
- **Trace for Example**: `D -> E -> B -> C -> A`
- **Application**: Disk space calculation, expression tree evaluation, bottom-up tree DP.

### 3.3 In-Order Traversal (Binary Trees Only)
- **Order**: Recursively traverse left subtree, visit current node $v$, recursively traverse right subtree.
- **Algorithm**:
  ```python
  def inorder(v):
      if v has left child:
          inorder(v.left)
      visit(v)
      if v has right child:
          inorder(v.right)
  ```
- **Trace for Example**: `D -> B -> E -> A -> C`
- **Application**: In-order traversal of a Binary Search Tree (BST) visits keys in **sorted non-decreasing order**.

---

## 4. Tree Implementations

### 4.1 Linked Structure Representation
- Node stores: `element`, pointer to `parent`, pointers to `left` and `right` (or list of `children`).
- Space Complexity: $\Theta(n)$.
- Operations (`parent`, `left`, `right`, `children`): $O(1)$ time.

### 4.2 Array Representation (Complete / Binary Trees)
- Elements stored in array $A$ where root is at index 1:
  - Left child of node at index $i$: $2i$
  - Right child of node at index $i$: $2i + 1$
  - Parent of node at index $i$: $\lfloor i / 2 \rfloor$
- **Pros**: $O(1)$ navigation without explicit pointers; space efficient for complete binary trees.
- **Cons**: Space inefficient for sparse or degenerate trees (requires $O(2^h)$ size in worst case).

---

## 5. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"In any tree with $n$ nodes, the number of edges is always $n-1$."** | **True** | Proven by induction; every node except the root has exactly one incoming edge from its parent. |
| **"In a proper binary tree, the number of external nodes is always equal to the number of internal nodes plus 1 ($e = i + 1$)."** | **True** | Standard property of proper binary trees. |
| **"In-order traversal can be performed on general trees with arbitrary number of children."** | **False** | In-order traversal is strictly defined for binary trees (or ordered trees with a distinguished partition of children). |
| **"The depth of a node is equal to the height of its subtree."** | **False** | Depth is distance from root down to node. Height is distance from node down to lowest leaf. They are generally not equal. |
| **"Array representation of a binary tree of height $h$ requires an array of size at least $2^{h+1}$."** | **True** | If the tree is a right-skewed chain of height $h$, the rightmost node will reside at index $2^{h+1}-1$. |
