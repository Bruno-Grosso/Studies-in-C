# 💻 Studies in C

This repository serves as my personal laboratory for studying C, algorithms, and data structures. 

The main goal of the implementations here isn't just to solve problems, but to build a solid foundation in low-level software engineering: manual memory management (RAM), pointer manipulation, dynamic allocation (`malloc`/`calloc`), and building non-linear data structures from scratch.

## 📂 Repository Structure

Here is the index of the topics and algorithms studied so far:

### 1. [BFS_Graph](./BFS_Graph)
* **Concepts:** Undirected Graphs, Adjacency Lists, Breadth-First Search (BFS).
* **Description:** Implementation of a routing system that finds the shortest path between two nodes in a network. The graph topology is loaded from a text file, and the algorithm calculates the route with the fewest jumps using backtracking.

---

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
