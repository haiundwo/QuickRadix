#include "QuickRadix.hpp"
#include <iostream>
#include <chrono>
#include <vector>

unsigned __int64 RandomSeeded(unsigned __int64 Seed) {
	Seed += 89374834578902543;
	Seed *= 238479360345897645;
	Seed ^= 3289740962803580927;
	Seed *= 1098403957438062777;
	Seed = 10661492517761810ULL * (Seed ^ (Seed * (Seed >> 3)));
	return Seed - (Seed * 329397869230767853ULL) + (Seed ^ ((Seed >> 32) | (Seed << 32)) ^ 0x3c4f01355a2a1ba3ULL) - (Seed ^ ((Seed >> 48) | (Seed << 16)));
}

unsigned __int64 RandomStreamNext() {
	// gen next
	static unsigned __int64 RandomSeed = (unsigned __int64)RandomStreamNext * std::rand();
	unsigned __int64 Next = RandomSeeded(RandomSeed);
	RandomSeed = Next;
	return Next;
}

template <typename T> 
T GenRandom() {
	unsigned __int64 CurrentSeed = RandomStreamNext();
	return *(T*)&CurrentSeed;
}

template <typename T>
void Benchmark(size_t size, size_t reps) {
	std::vector<T> values;
	for (size_t i = 0; i < size; i++) values.push_back(GenRandom<T>());

	auto startradix = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < reps; i++) {
		std::vector<T> temp = values;
		QuickRadix(&temp[0], temp.size(), 0, 0);
	}
	auto endradix = std::chrono::high_resolution_clock::now();
	double timeradix = std::chrono::duration_cast<std::chrono::nanoseconds>(endradix - startradix).count() / (double)reps;

	auto startstd = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < reps; i++) {
		std::vector<T> temp = values;
		std::sort(&temp[0], &temp[temp.size()]);
	}
	auto endstd = std::chrono::high_resolution_clock::now();
	double timestd = std::chrono::duration_cast<std::chrono::nanoseconds>(endstd - startstd).count() / (double)reps;

	if (std::is_floating_point_v<T>) {
		std::cout << sizeof(T) << "-byte float: ";
	}
	else {
		if (std::is_unsigned_v<T>) {
			std::cout << sizeof(T) << "-byte unsigned: ";
		}
		else {
			std::cout << sizeof(T) << "-byte: ";
		}
	}
	std::cout << "Radix was " << timestd / timeradix << "x as fast as std::sort for sorting " << size << "x elements " << reps << " times\n";
}

template <typename T>
void RunBasicBenchmark() {
	Benchmark<T>(50, 10000);
	Benchmark<T>(75, 10000);
	Benchmark<T>(100, 10000);
	Benchmark<T>(150, 10000);
	Benchmark<T>(200, 10000);
	Benchmark<T>(250, 10000);
	Benchmark<T>(500, 8000);
	Benchmark<T>(1000, 6000);
	Benchmark<T>(2500, 4000);
	Benchmark<T>(5000, 2000);
	Benchmark<T>(10000, 1000);
	Benchmark<T>(15000, 750);
	Benchmark<T>(25000, 350);
	Benchmark<T>(50000, 200);
	Benchmark<T>(100000, 100);
	Benchmark<T>(250000, 50);
	Benchmark<T>(500000, 25);
	Benchmark<T>(1000000, 10);
}

int main() {
	std::cout << "Random Sort Benchmarks\n\n";

	std::cout << "Integer Tests\n";
	RunBasicBenchmark<char>();
	RunBasicBenchmark<unsigned char>();
	RunBasicBenchmark<short>();
	RunBasicBenchmark<unsigned short>();
	RunBasicBenchmark<int>();
	RunBasicBenchmark<unsigned int>();
	RunBasicBenchmark<__int64>();
	RunBasicBenchmark<unsigned __int64>();

	std::cout << "\nFloat Tests\n";
	RunBasicBenchmark<float>();
	RunBasicBenchmark<double>();
}