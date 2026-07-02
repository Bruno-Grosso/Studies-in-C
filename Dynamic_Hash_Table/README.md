# Dynamic Hash Table in C - Universal Hashing & Open Addressing

This project contains the implementation of a dynamic hash table engine in pure C. The main goal of the code is to autonomously manage memory scaling (upscaling and downscaling) based on load factors, utilizing Universal Hashing, Double Probing for collision resolution, and Tombstones for logical deletions.

This project was developed as a personal deep-dive study to solidify concepts learned during the **Stanford University** Algorithms specialization (via Coursera). 

*Note: This implementation is entirely an independent study exercise. It is not affiliated with, nor does it solve, any official programming assignment or challenge from the Stanford course curriculum.*

---

### ⚠️ How to Run and Test the Engine

**How to use the interactive menu:** You can compile and run the code directly in your terminal. Follow these steps:

1. Compile the file using GCC (example): `gcc hash_table.c -o hash_table`
2. Run the compiled executable.
3. The system will first ask you to define the **initial capacity** of the table (it must be a valid positive integer).
4. You will then have access to a real-time menu where you can **Insert**, **Search**, and **Delete** keys to see the dynamic memory resizing and Tombstone mechanics in action.
