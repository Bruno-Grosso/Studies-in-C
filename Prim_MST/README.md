# 🔗 High-Performance Minimum Spanning Tree in C

This project contains the implementation of an optimized routing engine in pure C. The goal is to compute the exact Minimum Spanning Tree (MST) of a complex network graph using a custom-built Min-Heap architecture equipped with a real-time vertex positioning array (Index Tracking).

The base of this project was developed to solve the Minimum Spanning Tree challenge from the **Stanford University** Algorithms specialization (via Coursera), processing a dataset of 500 vertices and 2,184 edges while bypassing $O(V^2)$ search bottlenecks to maintain an optimal $O(m \log n)$ time complexity.

---

### ⚠️ About the Data File ( `Prim_MST_edges.txt` )

Due to GitHub's file size limits and versioning best practices, the text file containing the input graph dataset is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available on the Coursera platform, within the Greedy Algorithms (Course 3) week materials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `Prim_MST_edges.txt` .
2. It must be placed in the same folder as the C source file.
3. The first line must contain the total number of vertices and edges separated by a space (e.g., `500 2184`).
4. Each subsequent line must contain three integers separated by spaces, representing an undirected edge: `[node_1] [node_2] [edge_cost]` (both positive and negative weights are supported).
