# Massive 0/1 Knapsack (Rolling Arrays) in C - Dynamic Programming & Space Optimization

This project contains the implementation of a memory-optimized Dynamic Programming engine in pure C. The main goal of the code is to solve the classic 0/1 Knapsack problem on a massive scale. To bypass the prohibitive RAM requirement of a standard 2D DP table, the architecture implements a dual-buffer rolling array technique that alternates read/write states using parity indexing (`current_item % 2`), effectively slashing memory consumption.

The base of this project was developed to solve the Knapsack Big challenge from the **Stanford University** Algorithms specialization (via Coursera), processing a dataset of 2,000 items and a maximum knapsack capacity of 2,000,000. It compresses space complexity from $\mathcal{O}(N \times W)$ (which would require ~32 GB of RAM) down to $\mathcal{O}(W)$ (~32 MB on the Heap), utilizing 64-bit precision to prevent integer overflow during profit aggregations and low-level stream redirection for zero-overhead data ingestion.

---

## ⚠️ About the Data File (`knapsack_big.txt`)

Due to GitHub's file size limits and versioning best practices (avoiding the upload of massive datasets and raw `.txt` files), the text file containing the item values and weights is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available on the Coursera platform, within the Dynamic Programming week materials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `knapsack_big.txt`.
2. It must be placed in the same folder as the compiled executable file.
3. The first line must contain the total capacity of the knapsack and the total number of items, separated by a space (Example: `2000000 2000`).
4. Each subsequent line must contain two integers separated by a space, representing a single item: `[item_value] [item_weight]`.
