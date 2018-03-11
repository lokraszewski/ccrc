/*
* @Author: lu
* @Date:   25-01-2018
* @Last Modified by:   lu
* @Last Modified time: 11-03-2018
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
#include <cstring>
#include <thread>
#include <utility>
#include <vector>
#include "cpp-crc.hpp"

static void BM_slow_crc32(benchmark::State &state)
{
	using namespace cpp_crc::slow;
	uint8_t *data = new uint8_t[state.range(0)];

	for (auto i = 0; i < state.range(0); ++i)
	{
		data[i] = rand();
	}

	crc<uint32_t> c32(0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true );

	for (auto _ : state)
		benchmark::DoNotOptimize(c32.get(data, state.range(0)));

	state.SetComplexityN(state.range(0));

	delete[] data;
}
BENCHMARK(BM_slow_crc32)->RangeMultiplier(2)->Range(8, 1<<18)->Complexity(benchmark::oN);

static void BM_slow_crc8(benchmark::State &state)
{
	using namespace cpp_crc::slow;
	uint8_t *data = new uint8_t[state.range(0)];

	for (auto i = 0; i < state.range(0); ++i)
	{
		data[i] = rand();
	}

	crc<uint8_t> c8(0x07, 0x00, 0x00, false, false);

	for (auto _ : state)
		benchmark::DoNotOptimize(c8.get(data, state.range(0)));

	state.SetComplexityN(state.range(0));

	delete[] data;
}
BENCHMARK(BM_slow_crc8)->RangeMultiplier(2)->Range(8, 1<<18)->Complexity(benchmark::oN);

static void BM_fast_crc32(benchmark::State &state)
{
	using namespace cpp_crc::fast;
	uint8_t *data = new uint8_t[state.range(0)];

	for (auto i = 0; i < state.range(0); ++i)
	{
		data[i] = rand();
	}

	crc<uint32_t> c32(0x4C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true );

	for (auto _ : state)
		benchmark::DoNotOptimize(c32.get(data, state.range(0)));

	state.SetComplexityN(state.range(0));

	delete[] data;
}
BENCHMARK(BM_fast_crc32)->RangeMultiplier(2)->Range(8, 1<<18)->Complexity(benchmark::oN);

static void BM_fast_crc8(benchmark::State &state)
{
	using namespace cpp_crc::fast;
	uint8_t *data = new uint8_t[state.range(0)];

	for (auto i = 0; i < state.range(0); ++i)
	{
		data[i] = rand();
	}

	crc<uint8_t> c8(0x07, 0x00, 0x00, false, false);

	for (auto _ : state)
		benchmark::DoNotOptimize(c8.get(data, state.range(0)));

	state.SetComplexityN(state.range(0));

	delete[] data;
}
BENCHMARK(BM_fast_crc8)->RangeMultiplier(2)->Range(8, 1<<18)->Complexity(benchmark::oN);


BENCHMARK_MAIN();
