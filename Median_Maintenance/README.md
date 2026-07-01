# Median Maintenance in C

This project contains the implementation of a real-time statistical analysis engine in pure C. The goal is to calculate the running median of a massive data stream using a dual-heap architecture.

The base of this project was developed to solve the median maintenance challenge from the **Stanford University** Algorithms specialization (via Coursera), processing a dataset of 10,000 integers while maintaining $\mathcal{O}(\log N)$ insertion efficiency.

---

## ⚠️ About the Data File ( `Median.txt` )

Due to GitHub's file size limits and versioning best practices, the text file containing the input stream is not included in this repository.

**Where to find the file:** The official dataset used to test this code is available on the Coursera platform, within the Median Maintenance week materials of the Stanford Algorithms course.

**How to use your own data:** If you want to test the code, you can create your own file. It must follow these rules:

1. The filename must be exactly `Median.txt`.
2. It must be placed in the same folder as the `median_maintenance.c` file.
3. The format must contain one integer per line, representing the sequence of numbers in the data stream.
