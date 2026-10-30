# Optimal Prefix-Free Compression (Huffman) in C - Greedy Binary Trees & Contiguous Memory

This project contains the implementation of a high-performance greedy compression engine in pure C. The main goal of the code is to construct an exact Huffman tree for large-scale datasets, calculating the absolute maximum and minimum encoding depths of the optimal prefix-free code without relying on fragmented dynamic memory.

This project was developed as a personal deep-dive study to solidify concepts learned during the **Stanford University** Algorithms specialization (via Coursera). 

*Note: This implementation is entirely an independent study exercise. It is not affiliated with, nor does it solve, any official programming assignment or challenge from the Stanford course curriculum.*

---

### ⚠️ How to Run and Test the Engine

**How to use the execution flow:** You can compile and run the code directly in your terminal, using a structured input file for the symbol frequencies. Follow these steps:

1. Ensure the `huffman.txt` dataset file is in the same directory as the source code.
2. Compile the file using GCC with optimization flags (example): `gcc -O3 huffman.c -o huffman`
3. Run the compiled executable: `./huffman`
4. The system will automatically parse the dataset, build the contiguous $2N-1$ node tree structure bottom-up, process the symbol frequencies using 64-bit precision to prevent overflow, and output the minimum and maximum encoding depths alongside memory cleanup validation.
5. 
