# Dijkstra's Algorithm in C - Shortest Path Calculation

This project contains the implementation of Dijkstra's algorithm in pure C. The main goal of the code is to process weighted directed graphs and find the shortest path from a single source vertex to all other vertices.

The base of this project was developed to solve the graph processing challenge from the **Stanford University** Algorithms specialization (via Coursera), handling a dataset of 200 vertices and applying low-level techniques for string parsing (`strtok`, `sscanf`) and memory management.

---

## ⚠️ About the Data File (`dijkstraData.txt`)

Due to GitHub's file size limits and versioning best practices (avoiding the upload of datasets and raw `.txt` files), the text file containing the graph's edges is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available on the Coursera platform, within the Graph week materials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `dijkstraData.txt`.
2. It must be placed in the same folder as the compiled executable file.
3. The format of each line must start with the origin vertex, followed by space-separated tuples of `destination,weight`. (Example: `1 80,982 163,8164` means an arrow pointing from vertex 1 to vertex 80 with a weight of 982, and another to vertex 163 with a weight of 8164).
