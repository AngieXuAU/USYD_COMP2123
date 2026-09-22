# Week 6 Summary Notes: Hash Tables, Maps & Sets

**Source PDF**: `Notes/Week 6 - w6_hashing.pdf`  
**Target Exam Focus**: Questions 1 (T/F Collision Strategies & Complexity), 2 (Collision Tracing & Double Hashing/Cuckoo calculations), 3 (Hash Table Design & Load Factor Analysis)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–13** | **Map ADT & List Maps** | `put`, `get`, `remove`, List-based map performance ($O(n)$) |
| **Slides 14–25** | **Hash Functions** | Hash Code Maps (Polynomial, Cyclic shift) & Compression Maps (Division, MAD) |
| **Slides 26–34** | **Collision Handling** | Separate Chaining vs Open Addressing (Linear Probing, Deletion with Tombstones) |
| **Slides 35–46** | **Cuckoo Hashing** | Dual tables/functions, $O(1)$ worst-case lookup, eviction chains, rehash cycles |
| **Slides 47–53** | **Sets, Multisets & Theory** | Set ADT via Maps, Load factor $\alpha$, Universal Hashing, Cryptographic hashes |

---

## 2. Core Concepts & Hash Function Components

A **Hash Table** consists of a Bucket Array $A[0 \dots N-1]$ of size $N$ and a **Hash Function** $h(k)$ mapping keys to indices in $[0, N-1]$.

### 2.1 The Two Stages of a Hash Function
$$h(k) = \text{CompressionMap}(\text{HashCodeMap}(k))$$

1. **Hash Code Map**: Maps a key $k$ of arbitrary type to an integer $y \in \mathbb{Z}$.
   - **Polynomial Hash Code**: $y = a_0 + a_1 x + a_2 x^2 + \dots + a_{k-1} x^{k-1} \pmod P$. Excellent for strings and sequences (typically $x = 31, 33, 37$).
   - **Cyclic Shift Code**: Combines bit representations using bitwise rotations/shifts.

2. **Compression Map**: Maps integer $y \in \mathbb{Z}$ to bucket index $i \in [0, N-1]$.
   - **Division Method**: $h(y) = |y| \bmod N$. *(Best when $N$ is chosen as a PRIME number to reduce periodic collisions)*.
   - **Multiply-Add-and-Divide (MAD) Method**:
     $$h(y) = ((a \cdot y + b) \bmod p) \bmod N$$
     where $p$ is a prime $> N$, and $a, b$ are integers randomly chosen from $[0, p-1]$ with $a > 0$. Eliminates pattern bias in key sets.

---

## 3. Collision Resolution Strategies Summary Table

| Collision Strategy | Lookup (Avg / Worst) | Insert (Avg / Worst) | Delete (Avg / Worst) | Primary / Secondary Clustering? | Key Trade-offs / Notes |
| :--- | :---: | :---: | :---: | :---: | :--- |
| **Separate Chaining** | $O(1 + \alpha) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | $O(1 + \alpha) \;\big/\; O(n)$ | None | Requires extra pointer memory for linked lists. Handles $\alpha > 1$. |
| **Linear Probing** | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | **Primary Clustering** | High cache locality; requires `AVAILABLE` tombstones on delete. Needs $\alpha < 0.5$. |
| **Quadratic Probing** | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | **Secondary Clustering** | Probe sequence: $(h(k) + c_1 i + c_2 i^2) \bmod N$. May fail to find free slot if $\alpha \ge 0.5$. |
| **Double Hashing** | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | $O(1) \;\big/\; O(n)$ | None | Probe sequence: $(h_1(k) + i \cdot h_2(k)) \bmod N$. $h_2(k)$ must be coprime to $N$. |
| **Cuckoo Hashing** | **$O(1)$ Worst** | $O(1)$ Expected $/ O(n)$ | **$O(1)$ Worst** | None | Checks exactly 2 locations! Insert can trigger eviction chain or full table rehash. |

*Load Factor $\alpha = \frac{n}{N}$ (where $n = \text{number of keys}$, $N = \text{capacity of table}$).*

---

## 4. Operational Mechanics & Tracing (Question 2 Preparation)

### 4.1 Linear Probing Probe Sequence
- Formula for $i$-th attempt ($i = 0, 1, 2, \dots$):
  $$A[(h(k) + i) \bmod N]$$
- **Deletion Problem**: If key $X$ at $h(k)$ is deleted by setting cell to `None`, a subsequent search for key $Y$ (hashed to $h(k)$ but probed to $h(k)+1$) will hit `None` and incorrectly report "Not Found".
- **Fix**: Replace deleted items with a special marker `AVAILABLE` (or Tombstone). Insertions overwrite `AVAILABLE`, while searches bypass `AVAILABLE` and continue.

### 4.2 Double Hashing Formula & Requirements
- Formula for $i$-th attempt ($i = 0, 1, 2, \dots$):
  $$\text{Index}_i = (h_1(k) + i \cdot h_2(k)) \bmod N$$
- **Requirement**: $h_2(k)$ must NEVER evaluate to 0 and must be **coprime** to table size $N$ so the probe sequence can inspect all $N$ cells.
  - Common choice: $N$ is prime, $h_1(k) = k \bmod N$, $h_2(k) = q - (k \bmod q)$ where $q < N$ is prime.

### 4.3 Cuckoo Hashing Mechanics
- Uses two tables $T_1, T_2$ of size $N$ and two hash functions $h_1, h_2$.
- **Lookup ($k$)**: Check if $T_1[h_1(k)] == k$ or $T_2[h_2(k)] == k$. Takes **at most 2 comparisons** $\implies O(1)$ worst-case time!
- **Insert ($k$)**:
  1. Try placing $k$ in $T_1[h_1(k)]$. If empty, done.
  2. If $T_1[h_1(k)]$ is occupied by key $x$, **evict $x$** and put $k$ in $T_1[h_1(k)]$.
  3. Try placing evicted key $x$ in $T_2[h_2(x)]$. If occupied by $y$, evict $y$ and repeat.
  4. If eviction sequence enters a loop (exceeds max threshold $O(\log N)$ steps), rehash all keys using new hash functions.

---

## 5. Dynamic Resizing (Rehashing)

- When load factor $\alpha$ exceeds threshold (e.g., $\alpha > 0.75$ for chaining, $\alpha > 0.5$ for probing):
  1. Allocate a new array of capacity $N' \approx 2N$ (chosen as a prime).
  2. Recompute hash code & compression index for **every** key in the old table.
  3. Insert all keys into the new table.
- **Complexity**: $O(n)$ time during resize, yielding **$O(1)$ amortized time** per insertion operation.

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"In Cuckoo Hashing, search/lookup operation takes $O(1)$ worst-case time."** | **True** | Guaranteed because key $k$ can only reside at $T_1[h_1(k)]$ or $T_2[h_2(k)]$. |
| **"Separate chaining hash tables cannot store more keys than the array capacity $N$ ($\alpha > 1$)."** | **False** | Chaining stores linked lists in buckets, allowing $\alpha > 1$ (e.g., storing 100 keys in 10 buckets $\alpha = 10$). |
| **"Linear probing suffers from secondary clustering, while quadratic probing suffers from primary clustering."** | **False** | Reversed! Linear probing suffers from **primary** clustering; Quadratic probing suffers from **secondary** clustering. |
| **"When deleting an item from a hash table using linear probing, setting the cell to empty/null preserves search correctness."** | **False** | Must use a sentinel (`AVAILABLE`/tombstone) so search chains for collided items are not broken. |
| **"Rehashing a hash table of size $n$ takes $O(1)$ worst-case time."** | **False** | Rehashing requires allocating a new table and re-inserting all $n$ items, taking $O(n)$ time. |
