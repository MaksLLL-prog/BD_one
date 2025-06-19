# Polynomial Roots Solver

## Description
A C++ program for finding all complex roots of polynomials with complex coefficients. Implements Newton's method with deflation for sequential root finding.

## Key Features

- Support for polynomials with complex coefficients
- Automatic initial guess generation
- Convergence control for each root
- Detailed solution process information
- Templated implementation for multiple numeric types

## Requirements

- C++17 compiler (g++ 7+ or clang++ 5+)
- Standard C++ library

## Installation & Usage

1. Clone the repository:
   ```
   git clone [your-repository-url]
   cd polynomial-roots-solver
   ```

2. Compile the program:
   ```
   make
   ```

3. Run the executable:
   ```
   ./polynomial_roots
   ```

   Or compile and run in one command::
   ```
   make run
   ```

## How to Use

1. Enter polynomial degree (e.g., 3 for cubic equation)
2. Input coefficients for each term (real and imaginary parts separated by space)
3. The program will output found roots with convergence information

Example Input:
```
Enter polynomial degree (e.g., 3): 2
Enter coefficients (real and imaginary parts) from highest to lowest degree:
Coefficient for x^2: 1 0
Coefficient for x^1: -5 0
Coefficient for x^0: 6 0
```

Example Output:
```
Roots found:
Root: (3,0) | Converged: yes | Iterations: 5
Root: (2,0) | Converged: yes | Iterations: 4
```

## Дополнительные команды

- `make debug` - compile with debug information
- `make clean` - emove compiled files

## License

[MIT License](LICENSE)