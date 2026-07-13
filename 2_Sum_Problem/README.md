## 🔗 Mass-Scale 2-SUM Search in C

This project contains the implementation of an optimized search engine in pure C. The goal is to solve the classic 2-SUM problem across a massive dataset using a custom-built hash table featuring Open Addressing and Double Hashing.

The base of this project was developed to solve the 2-SUM challenge from the **Stanford University** Algorithms specialization (via Coursera), processing a dataset of 1,000,000 integers while bypassing $O(N^2)$ brute-force limitations to maintain $O(1)$ amortized search efficiency.

---

### ⚠️ About the Data File ( `prob-2sum.txt` )

Due to GitHub's file size limits and versioning best practices, the text file containing the massive input dataset is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available on the Coursera platform, within the 2-SUM week materials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `prob-2sum.txt` .
2. It must be placed in the same folder as the C source file.
3. The format must contain one integer per line, representing the array of numbers (both positive and negative values are supported).
