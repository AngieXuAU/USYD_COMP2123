# Week 2 Summary Notes: Stacks, Queues, Lists & Amortized Analysis

**Source PDF**: `Notes/Week 2 - w2_lists.pdf`  
**Target Exam Focus**: Questions 1 (T/F Concepts), 2 (Tracing Stack/Queue/List operations), 3 (Data Structure selection & Amortized proofs)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–8** | **ADT vs Data Structure** | Abstract Base Classes, encapsulation, interface vs implementation |
| **Slides 9–25** | **Stack ADT** | LIFO order, array-based & linked-list implementations, dynamic array resizing |
| **Slides 26–42** | **Queue ADT** | FIFO order, circular array implementation, linked-list implementation |
| **Slides 43–60** | **List & Positional List ADT** | Index-based lists, Position abstraction, Singly vs Doubly Linked Lists |
| **Slides 61–75** | **Amortized Analysis** | Aggregate method, Accounting method, Doubling vs Incremental expansion |

---

## 2. Key Data Structures & Complexity Summary Table

| Data Structure / Operation | `Stack` (Array) | `Stack` (Linked List) | `Queue` (Circular Array) | `Queue` (Linked List) | `List` (Array) | `List` (Singly Linked) | `List` (Doubly Linked) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **Access Front / Top / Index 0** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| **Access Back / Rear / Index $n-1$** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)^*$ | $O(1)$ |
| **Access Arbitrary Index $i$** | $O(1)$ | N/A | $O(1)$ | N/A | $O(1)$ | $O(i)$ | $O(\min(i, n-i))$ |
| **Insert Front / Push / Enqueue** | $O(1)^**$ | $O(1)$ | $O(1)^**$ | $O(1)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Insert Back** | $O(1)^**$ | $O(1)$ | $O(1)^**$ | $O(1)$ | $O(1)^**$ | $O(1)^*$ | $O(1)$ |
| **Delete Front / Pop / Dequeue** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Delete Back** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ | $O(n)$ | $O(1)$ |
| **Insert / Delete at Given Position $p$** | N/A | N/A | N/A | N/A | $O(n)$ | $O(1)^*{*\text{given node reference}}$ | $O(1)$ |
| **Space Complexity** | $O(N)$ | $O(n)$ | $O(N)$ | $O(n)$ | $O(N)$ | $O(n)$ | $O(n)$ |

*\* Assumes tail pointer is maintained in Singly Linked List.*  
*\*\* Amortized $O(1)$ time if dynamic array doubling is used.*

---

## 3. Core Abstract Data Types & Implementations

### 3.1 Stack ADT
- **Principle**: Last-In, First-Out (LIFO).
- **Core Operations**:
  - `push(e)`: Add element $e$ to the top of the stack.
  - `pop()`: Remove and return the top element. Throws exception if empty.
  - `top()` / `peek()`: Return top element without removing.
  - `size()`, `isEmpty()`: Utility query methods.
- **Implementations**:
  1. **Array-based Stack**: Fixed capacity $N$. Top tracked by index $t$ (initially $-1$). Overflow occurs if $t = N-1$.
  2. **Linked-List Stack**: Nodes connected via `next` pointers. Head of list serves as the top of stack. Never overflows unless system runs out of memory.

### 3.2 Queue ADT
- **Principle**: First-In, First-Out (FIFO).
- **Core Operations**:
  - `enqueue(e)`: Add element $e$ to the back of the queue.
  - `dequeue()`: Remove and return the front element.
  - `first()` / `front()`: Return front element without removing.
  - `size()`, `isEmpty()`: Utility query methods.
- **Implementations**:
  1. **Circular Array Queue**: Maintains `front` index $f$ and size $sz$. Next insertion slot is at `(f + sz) % N`. Avoids array shifting upon `dequeue()`.
  2. **Linked-List Queue**: Maintains `head` (front) and `tail` (rear) pointers. Enqueue at `tail`, dequeue at `head`.

### 3.3 Positional List ADT & Sentinels
- **Position Abstraction**: Wraps a node, providing access to `element()`.
- **Doubly Linked List with Sentinels**:
  - Uses dummy `header` and `trailer` nodes to avoid boundary check edge-cases.
  - Eliminates special checks for empty lists during insertion/deletion.

---

## 4. Amortized Analysis (Dynamic Array Expansion)

Amortized analysis computes the average time per operation over a worst-case sequence of operations.

### 4.1 Comparison of Resizing Strategies

#### Strategy 1: Incremental Expansion (Add fixed size $c$)
- Array expands by adding constant size $c$ when full.
- Cost of $i$-th resize operation: $O(i \cdot c)$.
- Total cost for $n$ `push` operations requiring $k = n/c$ resizes:
  $$\text{Total Cost} = n + \sum_{j=1}^{k} j \cdot c = n + c \frac{k(k+1)}{2} = O(n + c k^2) = O(n^2)$$
- **Amortized time per operation**: $\frac{O(n^2)}{n} = O(n)$.

#### Strategy 2: Doubling Strategy (Multiply capacity by 2)
- Capacity doubles ($N \to 2N$) when full.
- Resizes occur at insertions $1, 2, 4, 8, \dots, 2^k$.
- Total cost for $n$ `push` operations:
  $$\text{Total Cost} = n + \sum_{j=0}^{\lfloor \log_2 n \rfloor} 2^j = n + (2^{\lfloor \log_2 n \rfloor + 1} - 1) < n + 2n = 3n = O(n)$$
- **Amortized time per operation**: $\frac{O(n)}{n} = O(1)$.

---

## 5. Short Answer Tracing & Operations (Question 2 Preparation)

### Tracing Circular Array Queue
- Given array capacity $N = 5$, initial `front = 2`, `size = 3` (elements stored at indices $2, 3, 4$):
  - `enqueue(A)`: Index = $(2 + 3) \pmod 5 = 0$. `size` becomes 4.
  - `enqueue(B)`: Index = $(2 + 4) \pmod 5 = 1$. `size` becomes 5 (Full).
  - `dequeue()`: Returns element at index 2. `front` becomes $(2 + 1) \pmod 5 = 3$. `size` becomes 4.

### Tracing Doubly Linked List Deletion
- To remove node $p$:
  ```text
  p.prev.next = p.next
  p.next.prev = p.prev
  ```
  - Takes $O(1)$ time given pointer to node $p$.

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"In a singly linked list with head and tail pointers, deleting the last element takes $O(1)$ time."** | **False** | Deleting the last element requires updating `tail` to the second-to-last node, which requires traversing the list from `head` in $O(n)$ time. |
| **"Using a circular array for a Queue allows both `enqueue` and `dequeue` in $O(1)$ worst-case time."** | **True** | Modulo arithmetic updates `front` and `rear` pointers directly in $O(1)$ time without shifting elements. |
| **"Dynamic array doubling guarantees that EVERY individual `push` operation completes in $O(1)$ worst-case time."** | **False** | The worst-case time of a SINGLE `push` that triggers a resize is $O(n)$. It is $O(1)$ **amortized** time. |
| **"A Stack can be used to reverse an array or string in $O(n)$ time."** | **True** | Pushing $n$ elements and then popping them processes each item in LIFO order in $O(n)$ total time. |
| **"Dummy header and trailer sentinels in a Doubly Linked List increase asymptotic space complexity."** | **False** | Sentinels only add 2 constant dummy nodes, so space remains $\Theta(n)$. |
