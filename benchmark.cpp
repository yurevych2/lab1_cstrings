#include <benchmark/benchmark.h>
#include "my_str_t.h"
#include <string>
#include <fstream>
#include <sstream>

// Helper function to load a file into std::string
std::string LoadFileToStdString(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Helper function to load a file into my_str_t
my_str_t LoadFileToMyStr(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return my_str_t(buffer.str().c_str());
}

// Helper function to load a file by size into std::string
std::string LoadFileBySizeToStdString(size_t size) {
    std::string filename = std::to_string(size) + "mb.txt";
    return LoadFileToStdString(filename);
}

// Helper function to load a file by size into my_str_t
my_str_t LoadFileBySizeToMyStr(size_t size) {
    std::string filename = std::to_string(size) + "mb.txt";
    return LoadFileToMyStr(filename);
}

// Benchmark: Loading file into std::string with size argument
static void BM_LoadFileToStdStringBySize(benchmark::State& state) {
    for (auto _ : state) {
        std::string str = LoadFileBySizeToStdString(state.range(0));
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_LoadFileToStdStringBySize)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Loading file into my_str_t with size argument
static void BM_LoadFileToMyStrBySize(benchmark::State& state) {
    for (auto _ : state) {
        my_str_t str = LoadFileBySizeToMyStr(state.range(0));
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_LoadFileToMyStrBySize)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Appending to std::string with size argument
static void BM_AppendStdString(benchmark::State& state) {
    std::string str = LoadFileBySizeToStdString(state.range(0));
    for (auto _ : state) {
        str.append("extra data");
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_AppendStdString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Appending to my_str_t with size argument
static void BM_AppendMyStr(benchmark::State& state) {
    my_str_t str = LoadFileBySizeToMyStr(state.range(0));
    for (auto _ : state) {
        str.append("extra data");
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_AppendMyStr)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Operator= for std::string with size argument
static void BM_OperatorAssignStdString(benchmark::State& state) {
    for (auto _ : state) {
        std::string str1 = LoadFileBySizeToStdString(state.range(0));
        std::string str2;
        str2 = str1;
        benchmark::DoNotOptimize(str2);
    }
}
BENCHMARK(BM_OperatorAssignStdString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Operator= for my_str_t (mystring.cpp) with size argument
static void BM_OperatorAssignMyStr1(benchmark::State& state) {
    for (auto _ : state) {
        my_str_t str1 = LoadFileBySizeToMyStr(state.range(0));
        my_str_t str2{0, 'i'};
        str2 = str1;
        benchmark::DoNotOptimize(str2);
    }
}
BENCHMARK(BM_OperatorAssignMyStr1)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Swap for std::string with size argument
static void BM_SwapStdString(benchmark::State& state) {
    std::string str1 = LoadFileBySizeToStdString(state.range(0));
    std::string str2 = "temporary";
    for (auto _ : state) {
        std::swap(str1, str2);
        benchmark::DoNotOptimize(str1);
        benchmark::DoNotOptimize(str2);
    }
}
BENCHMARK(BM_SwapStdString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: Swap for my_str_t (mystring.cpp) with size argument
static void BM_SwapMyStr1(benchmark::State& state) {
    my_str_t str1 = LoadFileBySizeToMyStr(state.range(0));
    my_str_t str2{"temporary"};
    for (auto _ : state) {
        std::swap(str1, str2);
        benchmark::DoNotOptimize(str1);
        benchmark::DoNotOptimize(str2);
    }
}
BENCHMARK(BM_SwapMyStr1)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: shrink_to_fit for std::string with size argument
static void BM_ShrinkToFitStdString(benchmark::State& state) {
    std::string str = LoadFileBySizeToStdString(state.range(0));
    for (auto _ : state) {
        str.shrink_to_fit();
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_ShrinkToFitStdString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: shrink_to_fit for my_str_t (mystring.cpp) with size argument
static void BM_ShrinkToFitMyStr1(benchmark::State& state) {
    my_str_t str = LoadFileBySizeToMyStr(state.range(0));
    for (auto _ : state) {
        str.shrink_to_fit();
        benchmark::DoNotOptimize(str);
    }
}
BENCHMARK(BM_ShrinkToFitMyStr1)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: find for std::string with size argument
static void BM_FindStdString(benchmark::State& state) {
    std::string str = LoadFileBySizeToStdString(state.range(0));
    for (auto _ : state) {
        auto pos = str.find("search_term");
        benchmark::DoNotOptimize(pos);
    }
}
BENCHMARK(BM_FindStdString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: find for my_str_t (mystring.cpp) with size argument
static void BM_FindMyStr1(benchmark::State& state) {
    my_str_t str = LoadFileBySizeToMyStr(state.range(0));
    for (auto _ : state) {
        auto pos = str.find("search_term");
        benchmark::DoNotOptimize(pos);
    }
}
BENCHMARK(BM_FindMyStr1)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

// Benchmark: find for C string (using strstr)
static void BM_FindCString(benchmark::State& state) {
    const char* str = LoadFileToStdString("8mb.txt").c_str();
    for (auto _ : state) {
        auto pos = strstr(str, "search_term");
        benchmark::DoNotOptimize(pos);
    }
}
BENCHMARK(BM_FindCString)->Arg(8)->Arg(10)->Arg(12)->Arg(14)->Arg(16)->Iterations(500);

BENCHMARK_MAIN();
