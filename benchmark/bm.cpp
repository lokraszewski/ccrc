/*
* @Author: lu
* @Date:   25-01-2018
* @Last Modified by:   lu
* @Last Modified time: 26-01-2018
*/

#include <benchmark/benchmark.h>

#include <assert.h>
#include <math.h>
#include <stdint.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// static void BM_StringCreation(benchmark::State &state)
// {
	// for (auto _ : state)
		// std::string empty_string;
// }
// Register the function as a benchmark
// BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State &state)
{
	std::string x = "hello";

	for (auto _ : state)
		std::string copy(x);
}
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();

// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	return 0;
// }
