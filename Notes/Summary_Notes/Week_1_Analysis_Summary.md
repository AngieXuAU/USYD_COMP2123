# Week 1 Summary Notes: Algorithm Analysis & Asymptotic Notation

**Source PDF**: `Notes/Week 1 - w1_analysis.pdf`  
**Target Exam Focus**: Questions 1 (T/F Concepts), 2 (Complexity Calculations & Tracing), 3 (Complexity & Space Analysis Foundations)

---

## 1. Slide Structure & Content Overview

| Slide Range | Topic / Focus Area | Key Concepts Covered |
| :--- | :--- | :--- |
| **Slides 1–5** | **Three Core Abstractions** | Computational Problem, Algorithm, Data Structure |
| **Slides 6–12** | **Measuring Running Time** | Experimental vs Theoretical Analysis, RAM Model |
| **Slides 13–18** | **Case Analysis** | Worst-Case, Average-Case, Best-Case running times |
| **Slides 19–30** | **Asymptotic Growth & Big-O** | Formal definition of Big-O (\(O\)), constant factors, $n_0$ cutoff |
| **Slides 31–38** | **Big-Omega & Big-Theta** | Lower bounds ($\Omega$), Tight bounds ($\Theta$), Asymptotic properties |
| **Slides 39–44** | **Common Growth Rates** | Ordering functions by asymptotic growth rates |
| **Slides 45–49** | **Analysis Rules** | Primitive operations, loop counting, nested loops, conditional branches |

---

## 2. Key Definitions & Concepts (High Probability T/F & MCQs)

### 2.1 The Three Core Abstractions
1. **Computational Problem**: A formal specification of the desired input/output relationship (e.g., "Given an array of $n$ integers, sort them in non-decreasing order").
2. **Algorithm**: A step-by-step, deterministic, finite procedure for solving a computational problem.
3. **Data Structure**: A concrete organization, management, and storage format for data that enables efficient access and modifications.

> [!IMPORTANT]
> **ADT vs Data Structure**: An Abstract Data Type (ADT) specifies **what** operations are supported (user perspective), while a Data Structure specifies **how** those operations are implemented (programmer perspective).

---

### 2.2 Theoretical vs Experimental Analysis
- **Experimental Analysis**: Implement the algorithm in code, execute with varied inputs, and measure elapsed wall-clock time.
  - *Limitations*: Requires full implementation; dependent on hardware, OS, compiler, and language; limited to tested input instances.
- **Theoretical Analysis**: Characterize running time as a function of input size $n$ using high-level pseudo-code and primitive operation counts.
  - *Advantages*: Independent of hardware/software environment; evaluates performance across all possible inputs.

---

### 2.3 Asymptotic Notations (Formal Definitions)

#### Big-O Notation (Asymptotic Upper Bound)
$$f(n) \in O(g(n)) \iff \exists\, c > 0, n_0 \ge 1 \text{ such that } \forall n \ge n_0,\; f(n) \le c \cdot g(n)$$
- **Interpretation**: $f(n)$ grows no faster than $g(n)$ up to a constant factor for sufficiently large $n$.
- **T/F Trap**: $f(n) = O(g(n))$ is an upper bound, not necessarily a tight bound. If $f(n) = 3n + 5$, it is true that $f(n) \in O(n)$, $f(n) \in O(n^2)$, and $f(n) \in O(2^n)$.

#### Big-Omega Notation (Asymptotic Lower Bound)
$$f(n) \in \Omega(g(n)) \iff \exists\, c > 0, n_0 \ge 1 \text{ such that } \forall n \ge n_0,\; f(n) \ge c \cdot g(n)$$
- **Interpretation**: $f(n)$ grows at least as fast as $g(n)$ up to a constant factor for sufficiently large $n$.

#### Big-Theta Notation (Asymptotic Tight Bound)
$$f(n) \in \Theta(g(n)) \iff f(n) \in O(g(n)) \text{ AND } f(n) \in \Omega(g(n))$$
- **Interpretation**: $f(n)$ grows at the exact same rate as $g(g(n))$ within constant factors.
- Equivalently: $\exists\, c_1 > 0, c_2 > 0, n_0 \ge 1$ such that $\forall n \ge n_0$:
$$c_1 \cdot g(n) \le f(n) \le c_2 \cdot g(n)$$

---

## 3. Asymptotic Function Ordering (Crucial Cheat Sheet)

From slowest growing (most efficient) to fastest growing (least efficient):

$$1 < \log \log n < \log n < \sqrt{n} < n < n \log n < n^2 < n^3 < 2^n < 3^n < n! < n^n$$

### Key Logarithmic & Exponential Properties
- $\log_a n = \Theta(\log_b n)$ for any base constants $a, b > 1$ (base change rule: $\log_a n = \frac{\log_b n}{\log_b a}$).
- $n^k \in O(c^n)$ for any $k > 0$ and $c > 1$ (polynomials always grow slower than exponentials).
- $(\log n)^k \in O(n^\epsilon)$ for any $k > 0$ and $\epsilon > 0$ (polylogarithms always grow slower than any positive power of $n$).

---

## 4. Operational Analysis Rules & Tracing (Question 2 Preparation)

### 4.1 Summation & Loop Patterns

1. **Single Loop (Linear Step)**:
   ```python
   for i in range(n):  # Executed n times -> O(n)
       pass
   ```

2. **Single Loop (Logarithmic Step)**:
   ```python
   i = 1
   while i < n:  # i doubles each time: 1, 2, 4, ..., 2^k >= n -> k = ceil(log2 n)
       i = i * 2  # Executed O(log n) times
   ```

3. **Nested Loops (Dependent Bounds)**:
   ```python
   for i in range(n):
       for j in range(i):
           pass
   ```
   - Total executions: $\sum_{i=0}^{n-1} i = \frac{(n-1)n}{2} = \Theta(n^2)$.

4. **Nested Loops with Multiplication**:
   ```python
   for i in range(n):
       j = 1
       while j < n:
           j = j * 2
   ```
   - Outer loop runs $n$ times; inner loop runs $\lfloor \log_2 n \rfloor + 1$ times.
   - Total executions: $\sum_{i=0}^{n-1} \Theta(\log n) = \Theta(n \log n)$.

---

## 5. Common True/False Exam Statements & Pitfalls

| Statement | T/F | Explanation / Counterexample |
| :--- | :---: | :--- |
| **"If an algorithm runs in $O(n^2)$ time in the worst case, it must take $\Omega(n^2)$ time in the best case."** | **False** | Big-O is an upper bound on worst-case. Best-case can be $O(1)$ (e.g., Insertion Sort on an already sorted array is $O(n)$ best-case, $O(n^2)$ worst-case). |
| **"Big-O notation ignores constant factors and low-order terms."** | **True** | As $n \to \infty$, $3n^2 + 100n + 5000 = \Theta(n^2)$. |
| **"$2^{n+1} \in O(2^n)$"** | **True** | $2^{n+1} = 2 \cdot 2^n \le c \cdot 2^n$ with $c = 2$. |
| **"$2^{2n} \in O(2^n)$"** | **False** | $2^{2n} = (2^n)^2 = 4^n$. Ratio $\frac{4^n}{2^n} = 2^n \to \infty$, so $4^n \notin O(2^n)$. |
| **"If $f(n) = O(g(n))$, then $g(n) = \Omega(f(n))$."** | **True** | Direct equivalence by definition. |
| **"Experimental running time analysis can prove an algorithm's worst-case running time across all inputs."** | **False** | Experiments only test finite input sets, not all possible worst-case inputs. |
