# Lab work 1: C strings
Authors (team): [Yurevych Nataliia](https://github.com/yurevych2)<br>
## Prerequisites

Compiler Clang/MinGW, CMake.

### Compilation

Use an IDE.

### Usage

To run an example program launch сstrings_yurevych target.

To run benchmarks launch g_benchmark target.

### Results

I have created my_str_t class that implements strings with behavior similar to std::string. Additionally, I run Google benchmarks on a 16MB file with random words (I created it using Python) and got such results:
```
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------.
BM_LoadFileToStdString      89402 ns        76730 ns        11200
BM_LoadFileToMyStr          89235 ns        75331 ns         7467
BM_AppendStdString           72.4 ns         60.9 ns     10000000
BM_AppendMyStr                549 ns          472 ns      1723077~~
```

**BM_LoadFileToStdString and BM_LoadFileToMyStr**
Loading file to std::string took 76,730 nanoseconds and loading file to my_str_t took 75,331 nanoseconds.
So that my_str_t handles file-loading operations almost as efficiently as the highly-optimized std::string, at least for this specific test.

**BM_AppendStdString and BM_AppendMyStr**
Appending to std::string is significantly faster, taking 60.9 nanoseconds for each append operation.
Appending to my_str_t took 472 nanoseconds, which is 7.7 times slower compared to std::string.
Appending data with my_str_t being considerably slower than std::string.

# Additional tasks
Порівняння my_str_t та std::string з google benchmarks
