# Locality Sensitive Hashing (LSH) in C++

This repository contains two implementations of **Locality Sensitive Hashing (LSH)** for efficient approximate nearest neighbor search in high-dimensional data.

## Overview

LSH hashes similar data points into the same buckets with high probability, reducing exhaustive comparisons.

## Files

### LSH_1.cpp
- Binary vectors  
- Random index-based hashing  
- Hamming distance  

### LSH_2.cpp
- Real-valued vectors  
- Random hyperplane hashing  
- Cosine similarity  

## How It Works

1. Generate dataset  
2. Create hash functions  
3. Build hash tables  
4. Hash query  
5. Search within bucket  
6. Return nearest neighbor  

## 🛠️ Compilation & Run

```bash
g++ LSH_1.cpp -o lsh1
./lsh1

g++ LSH_2.cpp -o lsh2
./lsh2
```

## Applications

- Information retrieval  
- Recommendation systems  
- Similarity search  
