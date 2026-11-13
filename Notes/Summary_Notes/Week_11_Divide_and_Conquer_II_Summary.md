# Week 11 Summary Notes: Divide and Conquer II (Maxima-Set, Karatsuba, Master Theorem, & Selection)

**Source PDF**: `Notes/Week 11 - w11_divide_and_conquer_ii.pdf`  
**Target Exam Focus**: Questions 1 (T/F Master Theorem cases, Selection Complexities, Karatsuba Recurrence), 2 (Applying Master Theorem formulas, Tracing Maxima-Set combine & Median-of-Medians), 3 (Geometric & Advanced Divide-and-Conquer Algorithm Design, Linear Time Selection)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–3** | **Recap & Framework** | Divide, Recur/Delegate, Conquer structure |
| **Slides 4–18** | **Maxima-Set (Pareto Frontier)** | Problem definition, naive `O(n^2)` check, 2D divide-and-conquer, x-sorting preprocessing, conquer step via max-y filter, `O(n log n)` analysis |
| **Slides 19–31** | **Integer Multiplication (Karatsuba)** | Naive `Theta(n^2)`, 4-call D&C `T(n) = 4T(n/2) + O(n) = O(n^2)`, Gauss/Karatsuba trick with 3 calls, `T(n) = 3T(n/2) + O(n) = O(n^{log_2 3}) approx O(n^{1.585})` |
| **Slides 32–35** | **The Master Theorem** | Formal statement, 3 cases (subproblems dominate, equal/balanced, divide/conquer step dominates), unrolling intuition |
| **Slides 36–45** | **Selection & Median Finding** | Problem statement (k-th smallest), quick-selection `O(n)` expected, deterministic selection, median-of-3 vs median-of-5 medians, proof of linear time `O(n)` |

---

## 2. Geometric Divide and Conquer: Maxima-Set (Pareto Frontier)

### 2.1 Problem Definition
- **Definition**: In a 2D plane, point `p` dominates point `q` if `p.x >= q.x` and `p.y >= q.y` (with at least one strict inequality).
- A point `p` is **maximal** if it is not dominated by any other point in `S` (i.e. every other point has either smaller x-coordinate or smaller y-coordinate).
- **Naive Algorithm**: For every point `p`, compare against all other `n - 1` points `q`. Time complexity: `Theta(n^2)`.

---

### 2.2 Divide-and-Conquer Algorithm (`O(n log n)`)
1. **Preprocessing (Once)**:
   - Sort all points by increasing x-coordinate (break ties by y-coordinate) in `O(n log n)` time.
2. **Divide**:
   - Split sorted array into equal halves: `Left` (first `n/2` points) and `Right` (last `n/2` points).
3. **Recur**:
   - `MS_Left = MaximaSet(Left)`
   - `MS_Right = MaximaSet(Right)`
4. **Conquer (Merge)**:
   - Key Insight 1: Every point in `MS_Right` has a larger x-coordinate than any point in `Left`. Therefore, **no point in `MS_Right` can be dominated by any point in `Left`**. All points in `MS_Right` survive into the global maxima set!
   - Key Insight 2: A point `q in MS_Left` is dominated by some point in `Right` if and only if `q.y <= max_{p in MS_Right} (p.y)`.
   - Find point `p* in MS_Right` with maximum y-coordinate in `O(|MS_Right|) = O(n)` time.
   - Filter `MS_Left`: Retain point `q` iff `q.y > p*.y`.
   - Combined Maxima Set: `Filtered_MS_Left U MS_Right`.
- **Recurrence & Complexity**:
  `T(n) = 2T(n/2) + O(n)  ==>  T(n) = O(n log n)`
  Total time including sorting preprocessing: **`O(n log n)`**.

---

## 3. Fast Integer Multiplication (Karatsuba's Algorithm)

### 3.1 Problem & Naive Divide-and-Conquer
- Multiply two `n`-bit integers `x` and `y`.
- Split into high and low `n/2` bits:
  `x = x_1 * 2^{n/2} + x_0`,  `y = y_1 * 2^{n/2} + y_0`
- Product formula:
  `x * y = x_1 * y_1 * 2^n + (x_1 * y_0 + x_0 * y_1) * 2^{n/2} + x_0 * y_0`
- **Naive 4-call Approach**:
  Computes `x_1 * y_1`, `x_1 * y_0`, `x_0 * y_1`, and `x_0 * y_0` separately.
  - Recurrence: `T(n) = 4T(n/2) + O(n)`
  - Solves to: `T(n) = Theta(n^{log_2 4}) = Theta(n^2)` (No improvement over schoolbook multiplication).

---

### 3.2 Karatsuba's 3-Call Optimization
Notice that:
`(x_1 + x_0)(y_1 + y_0) = x_1 * y_1 + (x_1 * y_0 + x_0 * y_1) + x_0 * y_0`
Therefore, the middle term can be computed using only ONE additional multiplication:
`x_1 * y_0 + x_0 * y_1 = (x_1 + x_0)(y_1 + y_0) - x_1 * y_1 - x_0 * y_0`

- We only need **3 recursive multiplications**:
  1. `A = multiply(x_1, y_1)`
  2. `B = multiply(x_0, y_0)`
  3. `C = multiply(x_1 + x_0, y_1 + y_0)`
  - Middle term is simply `C - A - B`.
- **Recurrence**:
  `T(n) = 3T(n/2) + O(n)`
  - Solves via Master Theorem to:
    `T(n) = Theta(n^{log_2 3}) approx Theta(n^{1.585})` (Strictly faster than `O(n^2)`!).

---

## 4. The Master Theorem

Given recurrence:
`T(n) = a * T(n / b) + f(n)`  (with constants `a >= 1, b > 1`)

Let critical exponent be `c_{crit} = log_b(a)`. Compare `f(n)` against `n^{log_b a}`:

| Case | Condition | Dominant Factor | Solution `T(n)` |
| :---: | :--- | :--- | :---: |
| **Case 1** | `f(n) = O(n^{log_b a - epsilon})` for `epsilon > 0` | Tree leaves / subproblems dominate | **`Theta(n^{log_b a})`** |
| **Case 2** | `f(n) = Theta(n^{log_b a} * log^k n)` for `k >= 0` | Work is evenly distributed across levels | **`Theta(n^{log_b a} * log^{k+1} n)`** |
| **Case 3** | `f(n) = Omega(n^{log_b a + epsilon})` and regularity condition `a * f(n/b) <= delta * f(n)` for `delta < 1` | Root / divide-and-conquer step dominates | **`Theta(f(n))`** |

### Master Theorem Rapid Examples
1. `T(n) = 8T(n/2) + n^2`:
   `a = 8, b = 2 ==> log_2(8) = 3`. `f(n) = n^2 = O(n^{3 - 1})` (Case 1) `==> T(n) = Theta(n^3)`.
2. `T(n) = 2T(n/2) + O(n)` (Merge-Sort):
   `a = 2, b = 2 ==> log_2(2) = 1`. `f(n) = n = Theta(n^1 * log^0 n)` (Case 2, `k = 0`) `==> T(n) = Theta(n log n)`.
3. `T(n) = 2T(n/2) + O(n^2)`:
   `a = 2, b = 2 ==> log_2(2) = 1`. `f(n) = n^2 = Omega(n^{1 + 1})` (Case 3) `==> T(n) = Theta(n^2)`.

---

## 5. Selection & Order Statistics (k-th Smallest Element)

### 5.1 Problem Definition
- **Input**: Unsorted array `A` of `n` numbers and an integer `k` (`1 <= k <= n`).
- **Goal**: Find the `k`-th smallest number in `A`.
- **Trivial Approach**: Sort array and return `A[k]`. Time: `O(n log n)`.

---

### 5.2 Quick-Selection (Randomized Pivot)
1. Pick random pivot `p`.
2. Partition into `L` (`< p`), `E` (`== p`), `G` (`> p`).
3. Recursion:
   - If `k <= |L|`: recur on `L` searching for `k`-th smallest.
   - If `|L| < k <= |L| + |E|`: return `p`.
   - If `k > |L| + |E|`: recur on `G` searching for `(k - |L| - |E|)`-th smallest.
- **Expected Running Time**: **`O(n)`**.
- **Worst-Case Running Time**: `O(n^2)` (when bad pivots are repeatedly chosen).

---

### 5.3 Deterministic Linear-Time Selection: Median-of-Medians

To guarantee worst-case `O(n)` time, choose a pivot that is guaranteed to be close to the true median:

#### Algorithm (Median-of-5 Medians)
1. Divide `n` elements into groups of **5**.
2. Find the median of each group by brute force (`O(1)` per group, `O(n)` total).
3. Recursively find the median of the `n/5` group medians; call this pivot `x`.
4. Partition the entire array around `x`.
5. Recur on the appropriate half.

#### Why Groups of 5 (and NOT 3)?
- **Median of 3 Medians**:
  - Elements guaranteed smaller/larger than `x`: at least `n/3`.
  - Remaining subproblem size: at most `2n/3`.
  - Recurrence: `T(n) = T(n/3) + T(2n/3) + O(n)`.
  - Sum of fractional coefficients: `1/3 + 2/3 = 1`.
  - By unrolling, work per level is `c * n`, yielding **`O(n log n)`** (No improvement over sorting!).

- **Median of 5 Medians**:
  - Elements guaranteed smaller/larger than `x`: at least `3 * (n/10) = 3n/10`.
  - Remaining subproblem size: at most `7n/10`.
  - Recurrence: `T(n) = T(n/5) + T(7n/10) + O(n)`.
  - Sum of fractional coefficients: `1/5 + 7/10 = 9/10 < 1`!
  - Work shrinks geometrically at each level: `c * n * (1 + 9/10 + (9/10)^2 + ...) = O(n)`.
  - **Worst-Case Running Time**: **`O(n)`** guaranteed!

---

## 6. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"The recurrence `T(n) = 4T(n/2) + O(n)` solves to `O(n log n)`."** | **False** | By Master Theorem Case 1, `log_2(4) = 2`, so `T(n) = Theta(n^2)`. |
| **"Karatsuba's algorithm multiplies two `n`-bit integers in `Theta(n^{1.585})` time."** | **True** | It reduces recursive multiplications from 4 to 3, giving `T(n) = 3T(n/2) + O(n) = Theta(n^{log_2 3})`. |
| **"Median-of-3 Medians deterministic selection finds the k-th smallest element in `O(n)` worst-case time."** | **False** | Median-of-3 yields recurrence `T(n) = T(n/3) + T(2n/3) + O(n)`, which solves to `O(n log n)`. Median-of-5 is required for `O(n)`. |
| **"Quick-Selection has a worst-case running time of `O(n log n)`."** | **False** | Quick-Selection has an `O(n)` expected running time, but its worst case is `O(n^2)`. |
| **"In 2D Maxima-Set, every point in the right half's maxima set is guaranteed to be in the overall maxima set."** | **True** | All points in the right half have larger x-coordinates than any point in the left half, so left points cannot dominate right points. |
| **"Master Theorem Case 2 applies to `T(n) = 2T(n/2) + n log n`."** | **True** | Here `a = 2, b = 2 ==> log_b a = 1`. `f(n) = n^1 * log^1 n` (`k = 1`), solving to `Theta(n log^2 n)`. |

