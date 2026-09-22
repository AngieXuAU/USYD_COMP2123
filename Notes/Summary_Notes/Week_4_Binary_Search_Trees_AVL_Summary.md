# Week 4 Summary Notes: Binary Search Trees & AVL Trees

**Source PDF**: `Notes/Week 4 - w4_binary_search_tree.pdf`  
**Target Exam Focus**: Questions 1 (T/F Concepts & AVL Height Proofs), 2 (BST Deletion & AVL Rotation Tracing), 3 (BST/AVL Augmentation & Design)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–15** | **Binary Search Tree (BST) Concept** | BST Property, Map ADT, In-order key ordering |
| **Slides 16–30** | **BST Operations** | `search(k)`, `insert(k, v)`, `delete(k)` (3 deletion cases) |
| **Slides 31–43** | **Performance & Degeneracy** | Height-dependent running time $O(h)$, best case vs worst case |
| **Slides 44–47** | **AVL Tree Definition & Proof** | Height-Balance Property, Fibonacci minimum node proof $N(h)$ |
| **Slides 48–57** | **AVL Insertion & Restructuring** | Trinode restructuring, Single (LL/RR) and Double (LR/RL) rotations |
| **Slides 58–66** | **AVL Removal & Sorted Maps** | Deletion rebalancing ($O(\log n)$ cascades), Sorted Map operations |

---

## 2. Core Concepts & Definitions

### 2.1 The Binary Search Tree (BST) Property
For every node $x$ in a binary tree:
- All keys in the **left subtree** of $x$ are $\le \text{key}(x)$ (or strictly $<$ if duplicate keys are not allowed).
- All keys in the **right subtree** of $x$ are $\ge \text{key}(x)$ (or strictly $>$).

> [!NOTE]
> **In-Order Property**: An in-order traversal of a BST visits the keys in **sorted non-decreasing order**.

---

### 2.2 BST Operations & Deletion Mechanics

| Operation | Best Case Time | Worst Case Time | Description / Mechanics |
| :--- | :---: | :---: | :--- |
| **Search ($k$)** | $O(1)$ | $O(n)$ | Compare key $k$ with root: go left if $k < \text{key}$, right if $k > \text{key}$. |
| **Insert ($k, v$)** | $O(1)$ | $O(n)$ | Search for $k$. Insert new leaf node at the point where search terminates. |
| **Delete ($k$)** | $O(1)$ | $O(n)$ | Search for node $z$ containing $k$. Execute one of 3 deletion cases (below). |

#### The 3 Deletion Cases (Crucial for Tracing Questions)
1. **Case 0 (Leaf Node)**: Node $z$ has no children. Simply remove $z$ from its parent.
2. **Case 1 (Single Child)**: Node $z$ has exactly 1 child $c$. Connect $z$'s parent directly to $c$, bypassing $z$.
3. **Case 2 (Two Children)**: Node $z$ has 2 children.
   - Find $z$'s **in-order predecessor** $w$ (maximum key in $z$'s left subtree) OR **in-order successor** (minimum key in $z$'s right subtree).
   - Copy key/value of $w$ into $z$.
   - Delete node $w$ from its original location (which is guaranteed to fall into Case 0 or Case 1 because $w$ has at most 1 child!).

---

## 3. AVL Trees (Adel'son-Vel'skii & Landis)

### 3.1 Height-Balance Property
An AVL tree is a BST in which every internal node $v$ satisfies the **Height-Balance Property**:
$$|h_{\text{left}}(v) - h_{\text{right}}(v)| \le 1$$
where $h_{\text{left}}(v)$ and $h_{\text{right}}(v)$ are the heights of the left and right subtrees of $v$.

---

### 3.2 Proof of Height $h = O(\log n)$ (High Probability T/F)
Let $N(h)$ be the minimum number of internal nodes in an AVL tree of height $h$.
- Base Cases: $N(0) = 1$, $N(1) = 2$.
- Recurrence: $N(h) = 1 + N(h-1) + N(h-2)$ (1 root node + min nodes in taller subtree + min nodes in shorter subtree).
- Since $N(h-1) > N(h-2)$, we have $N(h) > 2 \cdot N(h-2)$.
- By induction: $N(h) > 2^{h/2 - 1}$.
- Taking logarithms:
  $$\log_2 n \ge \log_2 N(h) > \frac{h}{2} - 1 \implies h < 2 \log_2 n + 2 = O(\log n)$$
- Maximum height of an AVL tree with $n$ nodes is approximately $1.44 \log_2 n$.

---

## 4. Rebalancing: Trinode Restructuring & Rotations

When an insertion or deletion breaks the balance factor ($|h_L - h_R| > 1$) at an ancestor node $z$:
- $z$ is the first unbalanced node encountered traveling up from the modified node.
- $y$ is the child of $z$ with higher height.
- $x$ is the child of $y$ with higher height.

### 4.1 Single Rotations (LL and RR Configurations)
Occurs when $x$ is the left child of $y$ and $y$ is left child of $z$ (**LL**), OR $x$ is right child of $y$ and $y$ is right child of $z$ (**RR**).

```text
       z                      y
      / \                    / \
     y   T4    ===>        x     z
    / \                   / \   / \
   x   T3                T1 T2 T3 T4
  / \
 T1 T2
```
- **Single Rotation**: $y$ becomes the new root of the subtree, with $x$ as its left child and $z$ as its right child.

---

### 4.2 Double Rotations (LR and RL Configurations)
Occurs when $x$ is the right child of $y$ and $y$ is left child of $z$ (**LR**), OR $x$ is left child of $y$ and $y$ is right child of $z$ (**RL**).

```text
       z                         x
      / \                      /   \
     y   T4    ===>          y       z
    / \                     / \     / \
   T1  x                   T1 T2   T3 T4
      / \
     T2 T3
```
- **Double Rotation**: $x$ becomes the new root of the subtree, with $y$ as its left child and $z$ as its right child.

---

## 5. Summary Table: Insertion vs Deletion Rebalancing

| Feature | AVL Insertion | AVL Deletion |
| :--- | :--- | :--- |
| **Initial BST Operation** | Standard BST Insert ($O(\log n)$) | Standard BST Delete ($O(\log n)$) |
| **Height change of modified subtree** | Subtree height increases by 1 | Subtree height decreases by 1 |
| **Max Restructuring Operations Needed** | **At most 1** trinode restructuring (Single or Double rotation) | **Up to $O(\log n)$** trinode restructurings (may cascade to root) |
| **Worst-case Time Complexity** | $O(\log n)$ | $O(\log n)$ |

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"In a BST, search, insertion, and deletion always take $O(\log n)$ time."** | **False** | In an un-balanced BST, worst-case time is $O(h) = O(n)$ if keys are inserted in sorted order. |
| **"An AVL tree with $n$ nodes has height strictly bounded by $O(\log n)$."** | **True** | Guaranteed by the Height-Balance Property ($h < 1.44 \log_2 n$). |
| **"After inserting a new node into an AVL tree, at most one trinode restructuring operation is needed to rebalance the tree."** | **True** | A single restructuring restores the subtree to its pre-insertion height, fixing all ancestors. |
| **"After deleting a node from an AVL tree, at most one trinode restructuring operation is needed."** | **False** | Deletion restructuring can reduce subtree height, triggering further balance violations up to $O(\log n)$ times. |
| **"An in-order traversal of an AVL tree prints the keys in sorted order."** | **True** | An AVL tree is a valid BST, so in-order traversal always produces sorted keys. |
