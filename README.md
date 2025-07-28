Shamir's Secret Sharing (C++ Implementation)
This project implements a simplified version of Shamir's Secret Sharing Scheme using Lagrange Interpolation over a large prime field. The secret is reconstructed from encoded shares stored in a JSON file.

Features
✅ Supports variable base decoding (binary, octal, decimal, hex, etc.)

✅ Handles large integers using Boost Multiprecision

✅ Modular Inverse using Extended Euclidean Algorithm

✅ Accurate reconstruction using Lagrange Polynomial Interpolation

✅ Parses shares from JSON input format


How It Works
Parses JSON input containing base-encoded secret shares.

Decodes the values to Big Integers.

Selects the first k valid points.

Reconstructs the original secret using Lagrange Interpolation at x = 0.

Outputs the reconstructed secret.

Concepts Used
Lagrange Interpolation

Finite Field Arithmetic

Base conversion

Modular Inverse

Big Integer Arithmetic (via Boost)
