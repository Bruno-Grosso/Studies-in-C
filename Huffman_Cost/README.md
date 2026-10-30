# Optimal Prefix-Free Compression (Huffman) in C - Greedy Binary Trees & Contiguous Memory

This project contains the implementation of a high-performance greedy compression engine in pure C. The main goal of the code is to construct an exact Huffman tree for large-scale datasets, calculating the absolute maximum and minimum encoding depths of the optimal prefix-free code without relying on fragmented dynamic memory.

The base of this project was developed to solve the Huffman coding challenge from the **Stanford University** Algorithms specialization (via Coursera), processing a dataset of 1,000 unique symbols with high-frequency values while utilizing a contiguous array of $2N-1$ nodes and 64-bit precision to prevent integer overflow.

---

## ⚠️ About the Data File (`huffman.txt`)

Due to GitHub's file size limits and versioning best practices (avoiding the upload of datasets and raw `.txt` files), the text file containing the symbol frequencies is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available onematrials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `huffman.txt`.
2. It must be placed in the same folder as the compiled executable file.
3. The format of the file must start with the total number of symbols on the first line, followed by the frequency integer of each symbol on each subsequent line. (Example: `1000` on the first line, followed by large integer values like `7540662`, `6852892`, etc.).
