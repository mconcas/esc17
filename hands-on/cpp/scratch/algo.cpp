#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <chrono>

using Duration = std::chrono::duration<float>;

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& c)
{
  os << "{ ";
  std::copy(
      std::begin(c),
      std::end(c),
      std::ostream_iterator<T>{os, " "}
  );
  os << '}';

  return os;
}

int main()
{
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::mt19937 eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> uniform_dist{1, MAX_N};

  // fill a vector with SIZE random numbers
  int const SIZE = 11;
  std::vector<int> v;
  v.reserve(SIZE);

  auto start = std::chrono::high_resolution_clock::now();
  std::generate_n(std::back_inserter(v), SIZE, [&]() { return uniform_dist(eng); });
  auto end = std::chrono::high_resolution_clock::now();
  auto p = end - start;

  std::cout << v << '\n';
  std::cout <<"Fill a vector with SIZE random numbers: elapsed in: "<< p.count() << "us\n";

  // alternative way to fill the vector (but less efficient, why?)
  start = std::chrono::high_resolution_clock::now();
  std::generate_n(std::begin(v), SIZE, [&]() { return uniform_dist(eng); });
  end = std::chrono::high_resolution_clock::now();
  p = end - start;

  std::cout <<"Alternative way to fill the vector elapsed in: "<< p.count() << "us\n";

  // sum all the elements of the vector
  // use std::accumulate
  start = std::chrono::high_resolution_clock::now();
  auto s = std::accumulate(std::begin(v), std::end(v), 0);
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  
  std::cout <<"Sum all the elements of the vector elapsed in: "<< p.count() <<"us\n";
 
  // multiply all the elements of the vector
  // use std::accumulate

  start = std::chrono::high_resolution_clock::now();
  s = std::accumulate(std::begin(v), std::end(v), 1ll, [](auto const &b, auto const &c){ return b*c; });
  end = std::chrono::high_resolution_clock::now();
  p = end - start;

  std::cout<<"Mult result: "<< s <<" computed in: "<< p.count() <<"us"<<std::endl; 

  // sort the vector in ascending order
  // use std::sort
  start = std::chrono::high_resolution_clock::now();
  std::sort(v.begin(), v.end());
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Sort result: "<<v<<" computed in: "<< p.count() <<"us"<<std::endl;

  // sort the vector in descending order
  // use std::sort
  start = std::chrono::high_resolution_clock::now();
  std::sort(v.begin(), v.end(), [](auto &a, auto &b ){ return a>b; });
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Sort result: "<<v<<" computed in: "<< p.count() <<"us"<<std::endl;

  // move the even numbers at the beginning of the vector
  // use std::partition
  start = std::chrono::high_resolution_clock::now();
  std::partition(v.begin(), v.end(), [](auto &a){ return a%2==0; });
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Partition result: "<<v<<" computed in: "<< p.count() <<"us"<<std::endl;

  // move the three central elements to the beginning of the vector
  // use std::rotate
  start = std::chrono::high_resolution_clock::now();
  std::rotate(v.begin(), v.begin()+SIZE/2-1, v.end());
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Rotation result: "<<v<<" computed in: "<< p.count() <<"us"<<std::endl;

  // find the first element that is multiple of 3 or 7
  // use std::find_if
  start = std::chrono::high_resolution_clock::now();  
  auto result = std::find_if(v.begin(), v.end(), []( const auto &a ){ return a%3==0 || a%7==0;});
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Find_if result: "<<*result<<" computed in: "<< p.count() <<"us"<<std::endl;

  // erase from the vector the multiples of 3 or 7
  // use std::remove_if followed by vector::erase
  start = std::chrono::high_resolution_clock::now();
  v.erase(std::remove_if(v.begin(), v.end(), []( const auto &a ){ return a%3==0 || a%7==0;}), v.end());
  end = std::chrono::high_resolution_clock::now();
  p = end - start;
  std::cout<<"Find_if result: "<<v<<" computed in: "<< p.count() <<"us"<<std::endl;
};
