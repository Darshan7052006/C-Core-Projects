# Matrix Master (C)

Matrix Master is a menu-driven matrix calculator written in C.  
The program performs fundamental and advanced matrix operations using modular functions, recursion, and file handling.

This project was built to strengthen core C programming concepts required for systems programming and embedded development.

---

## Features

### Matrix Operations
- Matrix Addition
- Matrix Subtraction
- Matrix Multiplication
- Matrix Transpose

### Advanced Mathematical Operations
- Determinant of matrix (implemented using recursion)
- Matrix Inverse (Adjoint / Cofactor method)

### File Handling
- Save operation results to file
- Append history of calculations
- View previously saved results

---

## Concepts Used

- Functions
- 2D Arrays
- Variable Length Arrays (VLA)
- Recursion
- Matrix Algebra logic
- File Handling in C
- Modular Programming
- Menu-driven CLI design

---

## Program Structure

The program is divided into logical modules:

- Input handling functions
- Matrix operation functions
- Recursive determinant function
- Inverse calculation using cofactors
- File handling functions
- Menu-driven control flow

---

## How to Compile

Using GCC:

```bash
gcc matrix_master.c -o matrix_master