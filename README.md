# Analysis of K Means Clustering written in Python and C

### Project Structure

```bash
K-Means-Clustering-Analysis/        
                    C Implementation/               # Contains C implementation.
                        kmeans.c                    # Contains kmeans functions.
                        utilities.c                 # Contains utility functions.
                        main.c                      # Driver
                    Python Implementation/          # Contains Python implementation.
                        KMeansClustering.ipynb      # Contains scikit-learn implementation. 
```

### C Build

[![Build Status](https://travis-ci.com/mabdullahsoyturk/K-Means-Clustering-Analysis.svg?branch=master)](https://travis-ci.com/mabdullahsoyturk/K-Means-Clustering-Analysis)

```sh
$ git clone https://github.com/mabdullahsoyturk/K-Means-Clustering-Analysis.git
$ cd K-Means-Clustering-Analysis/C_Implementation
$ make
```

### C Run
```sh
$ ./output
```

### Running times with Iris Dataset

Complexity of the algorithm: O(n^(dk+1)) where n is the number of rows in the dataset, k is the number of clusters and d is the dimension.

| Python | C |
| ------ | ------ |
| 29.3 ms | 0.245 ms |

### Development

Want to contribute? Great!

[Contact Me](http://muhammetsoyturk.com/)
