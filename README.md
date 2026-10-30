# 💻 Studies in C

This repository serves as my personal laboratory for studying C, algorithms, and data structures. 

The main goal of the implementations here isn't just to solve problems, but to build a solid foundation in low-level software engineering: manual memory management (RAM), pointer manipulation, dynamic allocation (`malloc`/`calloc`), and building non-linear data structures from scratch.

## 📂 Repository Structure

Here is the index of the topics and algorithms studied so far:

### 1. [Shortest Path](./Shortest_Path)
* **Concepts:** Undirected Graphs, Adjacency Lists, Breadth-First Search (BFS).
* **Description:** Implementation of a routing system that finds the shortest path between two nodes in a network. The graph topology is loaded from a text file, and the algorithm calculates the route with the fewest jumps using backtracking.


### 2. [Top 5 Strongly Connected Components (SCCs)](./Top5-SCCs)
* **Concepts:** Directed Graphs, Depth-First Search (DFS), Kosaraju's Algorithm, Graph Transposition.
* **Description:** Implementation of a two-pass algorithm to detect isolated connectivity "bubbles" within a massive directed graph. The system computes vertex finishing times through recursion, transposes the network edges, and executes a targeted DFS to discover, group, and rank the sizes of the five largest Strongly Connected Components.


### 3. [Minimum Cost Routing (Dijkstra)](./Dijkstra_Path)
* **Concepts:** Weighted Directed Graphs, Adjacency Lists, Dijkstra's Algorithm, Data Ingestion/Parsing.
* **Description:** Implementation of a greedy routing engine that calculates the absolute shortest path from a single source to multiple target nodes in a network. The graph is built from a heavily formatted text dataset, utilizing low-level string tokenization for I/O efficiency, and processes edge relaxations to guarantee the mathematically cheapest routes.

### 4. [Median Maintenance](./Median_Maintenance)
* **Concepts:** Heaps (Max-Heap & Min-Heap), Priority Queues, Online Algorithms, Data Streaming.
* **Description:**  A streaming engine that calculates the running median of a massive dataset. It uses a dual-heap architecture to maintain two balanced halves of the data, ensuring median extraction in $\mathcal{O}(1)$ and insertion in $\mathcal{O}(\log N)$, without the need to re-sort the entire set.

### 5. [Dynamic Hash Table](./Dynamic_Hash_Table)
* **Concepts:** Universal Hashing, Open Addressing (Double Probing), Tombstone Deletion, Dynamic Resizing.
* **Description:** A highly resilient hash table engine that autonomously manages memory scaling based on load factors. It implements Universal Hashing and Double Probing to prevent clustering, and utilizes a Tombstone mechanism to safely handle logical deletions. This architecture ensures $\mathcal{O}(1)$ amortized time complexity for insertions, deletions, and lookups, even under continuous data flow.

### 6. [Mass-Scale 2-SUM Search](./2_Sum_Problem)

* **Concepts:** Hash Tables, Open Addressing (Double Hashing), Universal Hashing, Time-Space Tradeoffs, Big Data Processing.
* **Description:** Implementation of an optimized search engine designed to solve the classic 2-SUM problem across a massive dataset of one million integers. It leverages a custom-built hash table featuring Universal Hashing and Double Probing to guarantee uniform data distribution and mitigate clustering. By calculating algebraic complements and executing $O(1)$ lookups, the architecture entirely bypasses $O(N^2)$ brute-force limitations, efficiently processing tens of billions of potential combinations to find valid target sums.

### 7. [High-Performance Minimum Spanning Tree](./Prim_MST)

* **Concepts:** Heaps (Min-Heap with Index Tracking), Priority Queues, Graph Theory, Greedy Algorithms (Prim's).
* **Description:** Implementation of an optimized routing engine designed to compute the exact Minimum Spanning Tree (MST) of complex network graphs. It integrates a custom-built Min-Heap architecture equipped with a real-time vertex positioning array to execute constant-time $O(1)$ decrease-key operations. This robust structural upgrade effectively bypasses standard $O(V^2)$ search bottlenecks, achieving an optimal $O(m \log n)$ time complexity to efficiently process large-scale, sparse data networks.

### 8. [Optimal Prefix-Free Compression (Huffman)](./Huffman_Cost)

* **Concepts:** Greedy Algorithms, Binary Trees, Contiguous Memory Allocation, Data Compression, Integer Overflow Management.
* **Description:** Implementation of a highly optimized greedy compression engine designed to construct an exact Huffman tree for large-scale datasets. Instead of relying on fragmented dynamic memory, the architecture models the entire tree structure within a single, contiguous array of $2N-1$ nodes. It utilizes a custom bottom-up traversal mechanism via parent pointers to bypass traditional recursion overhead, and is strictly fortified with 64-bit precision to prevent integer overflow when processing massive symbol frequencies. The system efficiently fuses nodes to calculate the absolute maximum and minimum encoding depths of the optimal prefix-free code.

------------

## 🛠️ Technologies and Concepts
* **Language:** C
* **Data Structures:** Dynamic Arrays, Linked Lists, Queues, Graphs.
* **Memory Management:** Preventing memory leaks and segmentation faults using `free()` and strict pointer control.
* **Compilation:** GCC via Linux/Unix terminal.

## 🚀 How to run the projects
Each folder contains its own source code. The standard GCC compilation pattern used in this repository is:

```bash
# Compiling the source file
gcc filename.c -o executable_name

# Running the program
./executable_name
