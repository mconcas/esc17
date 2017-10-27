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
uniform_int_distribution<char> d_char;

#ifdef PACKED

struct P
{
  int  n;
  char c1;
  char c2;
};

static_assert(sizeof(P) == 8, "");

P make_P()
{
  return { d(e), d_char(e), d_char(e) };
}

inline bool operator<(P const& l, P const& r) {
  return tie(r.n, r.c1, r.c2) < tie(l.n, l.c1, l.c2);
}

#else

struct P
{
  char c1;
  int  n;
  char c2;
};

static_assert(sizeof(P) == 12, "");

P make_P()
{
  return { d_char(e), d(e), d_char(e) };
}

inline bool operator<(P const& l, P const& r) {
  return tie(r.c1, r.n, r.c2) < tie(l.c1, l.n, l.c2);
}

#endif

int main()
{
  int const N = 10000000;
  vector<P> v;
  generate_n(back_inserter(v), N, make_P);
  
  auto start = chrono::high_resolution_clock::now();

  sort(v.begin(), v.end());

  cout << chrono::duration<double>(chrono::high_resolution_clock::now() - start).count() << " s\n";
}
