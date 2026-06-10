# Kosaraju's Algorithm in C - Strongly Connected Components

This project contains the implementation of Kosaraju's algorithm in pure C. The main goal of the code is to process massive directed graphs and find their Strongly Connected Components (SCCs).

The base of this project was developed to solve the graph processing challenge from the **Stanford University** Algorithms specialization (via Coursera), handling a dataset of 875,714 vertices and applying low-level techniques for I/O optimization and memory management.

---

## ⚠️ About the Data File (`Graph.txt`)

Due to GitHub's file size limits and versioning best practices (avoiding the upload of heavy datasets), the text file containing the graph's edges **is not included in this repository**.

**Where to find the file:**
The official dataset used to test this code is available on the Coursera platform, within the Graph week materials of the Stanford Algorithms course.

**How to use your own data:**
If you want to test the code, you can create your own file. It must follow these rules:
1. The filename must be exactly `Graph.txt`.
2. It must be placed in the same folder as the `highest_scc.c` file.
3. The format of each line must contain two integers separated by a space, representing the edge's direction (Example: `1 2` means an arrow pointing from vertex 1 to vertex 2).

