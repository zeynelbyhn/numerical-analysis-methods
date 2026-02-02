# 🔢 Numerical Methods Calculator (C)

## 📝 Description
This project is a high-performance command-line application designed to solve complex mathematical problems through various **Numerical Analysis** techniques. 

The standout feature of this tool is its **Infix Expression Evaluator**, which allows users to input mathematical functions as dynamic strings (e.g., `3*x + cos(x)^2`) instead of hardcoding them. It utilizes a custom Stack implementation to parse and calculate function values at runtime.

---

## 🚀 Key Features

### 1. Root Finding Algorithms
* **Bisection Method:** Finds roots by repeatedly bisecting an interval.
* **Regula-Falsi:** Uses linear interpolation for interval-based root finding.
* **Newton-Raphson:** Rapidly converges to a root using derivative approximations.

### 2. Linear Algebra & Matrix Operations
* **Matrix Inversion:** Calculates the inverse of $n \times n$ matrices using Gaussian elimination.
* **Cholesky Decomposition:** Solves $AX = B$ systems via $LU$ decomposition.
* **Gauss-Seidel Method:** An iterative approach for linear systems with adjustable error tolerance.

### 3. Calculus & Interpolation
* **Numerical Differentiation:** Supports Forward, Backward, and Central difference formulas.
* **Numerical Integration:** Includes Trapezoidal Rule, Simpson’s 1/3, and Simpson’s 3/8 methods.
* **Gregory-Newton Interpolation:** Computes values using finite difference tables.

---

## 🧠 Advanced Function Parser
The tool supports a wide range of mathematical expressions thanks to its robust parsing engine:
* **Operators:** `+`, `-`, `*`, `/`, `^`
* **Trigonometry:** `sin`, `cos`, `tan`, `cot` & `arcsin`, `arccos`, `arctan`, `arccot`.
* **Advanced:** Logarithms (custom base via `_`), Euler's number ($e$), and $\pi$ ($P$).

---

## 🛠️ Technologies Used
* **Language:** C (C99/C11 Standard)
* **Libraries:** `stdio.h`, `stdlib.h`, `math.h`
* **Data Structures:** Custom Stack for operands and operators.


---
*Academic Project for Numerical Analysis.*
