#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <iterator>
#include <tuple>

using namespace std;

default_random_engine e { std::random_device{}() };
uniform_int_distribution<> d;

#ifndef EXTSIZE
#define EXTSIZE 0
#endif

constexpr int const ExtSize = EXTSIZE;

struct S
{
  int n;
  char ext[ExtSize];
};

int main()
{
  int const N = 10000000;

  vector<S> v;
  generate_n(back_inserter(v), N, []() { return S { d(e) }; });

  auto start = chrono::high_resolution_clock::now();

  sort(v.begin(), v.end(), [](S const& l, S const& r) { return l.n < r.n; });

  cout << chrono::duration<double>(chrono::high_resolution_clock::now() - start).count() << " s\n";
}
