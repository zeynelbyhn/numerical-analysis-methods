# 🔢 Numerical Methods Calculator (C)

A powerful command-line application developed in **C** to solve complex mathematical problems using numerical analysis methods. This project features a custom-built **Infix Expression Parser** that allows users to input mathematical functions directly as strings (e.g., `sin(x) + x^2 - 5`).

## 🚀 Key Features

### 1. Root Finding Algorithms
* **Bisection Method:** Finds roots by repeatedly bisecting an interval.
* **Regula-Falsi (False Position):** A closed-bracket method using linear interpolation for root discovery.
* **Newton-Raphson:** An open-bracket method using derivatives for fast convergence towards a root.

### 2. Linear Algebra & Matrix Operations
* **Matrix Inversion:** Calculates the inverse of $n \times n$ matrices using Gaussian elimination.
* **Cholesky Decomposition:** Solves $AX = B$ systems by decomposing matrices into Lower and Upper ($LU$) forms.
* **Gauss-Seidel Method:** An iterative method for solving systems of linear equations with built-in tolerance control.

### 3. Calculus & Interpolation
* **Numerical Differentiation:** Calculates derivatives at a specific point using forward, backward, and central difference formulas.
* **Numerical Integration:**
  * **Trapezoidal Rule:** Approximates the definite integral under a curve.
  * **Simpson's 1/3 Rule:** Uses quadratic segments for more accurate integration.
  * **Simpson's 3/8 Rule:** Employs cubic segments for specialized integration tasks.
* **Gregory-Newton Interpolation:** Estimates values between known data points using difference tables.

---

## 🧠 Advanced Function Parser

This tool includes a custom-built **Mathematical Expression Evaluator** using Stack data structures, allowing dynamic function input during runtime. It supports:
* **Operators:** `+`, `-`, `*`, `/`, `^` (power)
* **Trigonometry:** `sin`, `cos`, `tan`, `cot` and their inverses (`arcsin`, `arccos`, `arctan`, `arccot`).
* **Logarithms:** Support for custom base logarithms using `_` notation.
* **Constants:** Support for $e$ (Euler's number) and $P$ ($\pi$).

---

## 🛠️ Technologies Used

* **Language:** C (Standard C99/C11)
* **Libraries:** `stdio.h`, `stdlib.h`, `math.h`
* **Paradigm:** Procedural Programming & Custom Stack Implementation

## 🚀 How to Run

1. **Compile the code:**
   ```bash
   gcc numerical_calc.c -o numcalc -lm
