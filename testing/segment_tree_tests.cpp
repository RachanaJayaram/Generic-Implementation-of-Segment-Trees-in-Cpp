#include <vector>
#include <iostream>
#include "../segment_tree/segment_tree.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
using namespace st;

template <typename T>
void print_time(std::vector<T> &vect, SegmentTree<T> &seg, long int l, long int r);

template <typename T, typename ptr_t>
T accumulate(ptr_t first, ptr_t last, T init);

/** Default Constructor.
 * 
 * Check if container size is 0.
 * Check if sum returns 0.
 */
TEST_CASE("Default Constructor")
{
  SegmentTree<float> segmentTree1;
  CHECK(segmentTree1.size() == 0);
  CHECK(segmentTree1.empty() == 1);
  CHECK(segmentTree1.sum(0, 4) == 0);
}

/** Constructor from input array.
 * 
 * Check if size matches.
 * Check if all elements are found.
 */
TEST_CASE("Constructor from input array")
{
  float arr1[] = {1.0, 2.1, 3.2, 4.5, 4.5};
  SegmentTree<float> segmentTree1(arr1, 5);
  CHECK(segmentTree1.size() == 5);
  CHECK(segmentTree1.count(1.0) == 1);
  CHECK(segmentTree1.count(2.1) == 1);
  CHECK(segmentTree1.count(3.2) == 1);
  CHECK(segmentTree1.count(4.5) == 2);
  CHECK(segmentTree1.count(6.0) == 0);
}

/** Constructor from segment tree from a range.
 * 
 * Check if size matches.
 * Check if all elements are found.
 * Check if iterators match.
 */
TEST_CASE("Constructor from input array")
{
  std::vector<int> a(5);
  for (int i = 0; i < 5; ++i)
  {
    a[i] = i * i;
  }

  SegmentTree<int> segmentTree1(a.begin(), a.end());
  CHECK(segmentTree1.size() == 5);
  CHECK(segmentTree1.count(0) == 1);
  CHECK(segmentTree1.count(1) == 1);
  CHECK(segmentTree1.count(4) == 1);
  CHECK(segmentTree1.count(9) == 1);
  CHECK(segmentTree1.count(16) == 1);
  CHECK(segmentTree1.count(25) == 0);
  CHECK(*(segmentTree1.begin()) == *(a.begin()));
  CHECK(*(segmentTree1.rbegin()) == *(a.rbegin()));
}

/** Copy Constructor.
 * 
 * Check if size matches.
 * Check if all elements are found.
 * Check if iterators work.
 */
TEST_CASE("Copy Constructor")
{
  std::vector<int> a(5);
  for (int i = 0; i < 5; ++i)
  {
    a[i] = i * i;
  }

  SegmentTree<int> segmentTree1(a.begin(), a.end());
  SegmentTree<int> segmentTree2(segmentTree1);

  CHECK(segmentTree2.size() == 5);
  CHECK(segmentTree2.count(0) == 1);
  CHECK(segmentTree2.count(1) == 1);
  CHECK(segmentTree2.count(4) == 1);
  CHECK(segmentTree2.count(9) == 1);
  CHECK(segmentTree2.count(16) == 1);
  CHECK(segmentTree2.count(25) == 0);
  CHECK(*(segmentTree2.begin()) == *(a.begin()));
  CHECK(*(segmentTree2.rbegin()) == *(a.rbegin()));

  SegmentTree<int> segmentTree3 = segmentTree1;

  CHECK(segmentTree3.size() == 5);
  CHECK(segmentTree3.count(0) == 1);
  CHECK(segmentTree3.count(1) == 1);
  CHECK(segmentTree3.count(4) == 1);
  CHECK(segmentTree3.count(9) == 1);
  CHECK(segmentTree3.count(16) == 1);
  CHECK(segmentTree3.count(25) == 0);
  CHECK(*(segmentTree3.begin()) == *(a.begin()));
  CHECK(*(segmentTree3.rbegin()) == *(a.rbegin()));
}

/** Iterators.
 * 
 * Check if iterators are functioning.
 * Compare each element by means of iterator.
 */
TEST_CASE("Iterators")
{
  std::vector<float> a(5);
  for (int i = 0; i < 5; ++i)
  {
    a[i] = i / 20;
  }
  SegmentTree<float> segmentTree1(a.begin(), a.end());
  CHECK(segmentTree1.size() == a.size());

  SegmentTree<float>::iterator s_first = segmentTree1.begin();
  std::vector<float>::iterator v_first = a.begin();
  while (s_first != segmentTree1.end())
  {
    CHECK(*s_first == *v_first);
    ++s_first;
    ++v_first;
  }
}

/** Reverse iterators.
 * 
 * Check if reverse iterators are functioning.
 * Compare each element by means of reverse iterator.
 */
TEST_CASE("Reverse Iterators")
{
  std::vector<float> a(5);
  for (int i = 0; i < 5; ++i)
  {
    a[i] = i / 20;
  }
  SegmentTree<float> segmentTree1(a.begin(), a.end());
  CHECK(segmentTree1.size() == a.size());

  SegmentTree<float>::reverse_iterator s_rfirst = segmentTree1.rbegin();
  std::vector<float>::reverse_iterator v_rfirst = a.rbegin();
  while (s_rfirst != segmentTree1.rend())
  {
    CHECK(*s_rfirst == *v_rfirst);
    ++s_rfirst;
    ++v_rfirst;
  }
}

/*
 * Testing count function.
 */
TEST_CASE("count function")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  CHECK(segmentTree1.count(1) == 0);

  int b[] = {3, 3, 3, 3, 3};
  SegmentTree<int> segmentTree2(b, 5);
  CHECK(segmentTree2.count(3) == 5);
}

/*
 * Testing find function.
 */
TEST_CASE("find function")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  CHECK(segmentTree1.find(1) == segmentTree1.end());

  int b[] = {3, 3, 3, 3, 3};
  SegmentTree<int> segmentTree2(b, 5);
  CHECK(segmentTree2.find(3) == segmentTree2.begin());
}

/*
 * Testing lower_bound function.
 */
TEST_CASE("lower_bound function")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  CHECK(segmentTree1.lower_bound(1) == segmentTree1.end());

  int b[] = {2, 3, 3, 3, 4};
  SegmentTree<int> segmentTree2(b, 5);
  CHECK(segmentTree2.lower_bound(2) == segmentTree2.begin());
  CHECK(segmentTree2.lower_bound(3) == segmentTree2.begin() + 1);
  CHECK(segmentTree2.lower_bound(4) == segmentTree2.begin() + 4);
  CHECK(segmentTree2.lower_bound(5) == segmentTree2.end());
}

/* 
 * Testing upper_bound function.
 */
TEST_CASE("upper_bound function")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  CHECK(segmentTree1.upper_bound(1) == segmentTree1.end());

  int b[] = {2, 3, 3, 3, 4};
  SegmentTree<int> segmentTree2(b, 5);
  CHECK(segmentTree2.upper_bound(2) == segmentTree2.begin() + 1);
  CHECK(segmentTree2.upper_bound(3) == segmentTree2.begin() + 4);
  CHECK(segmentTree2.upper_bound(4) == segmentTree2.end());
  CHECK(segmentTree2.upper_bound(5) == segmentTree2.end());
}

/*
 * Testing equal_range function.
 */
TEST_CASE("upper_bound function")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  auto range = segmentTree1.equal_range(1);
  CHECK(range.first == segmentTree1.end());
  CHECK(range.second == segmentTree1.end());

  int b[] = {2, 3, 3, 3, 4};
  SegmentTree<int> segmentTree2(b, 5);
  range = segmentTree2.equal_range(3);
  CHECK(range.first == segmentTree2.lower_bound(3));
  CHECK(range.second == segmentTree2.upper_bound(3));
}

/*
 * Testing sum function.
 */
TEST_CASE("sum")
{
  int a[] = {};
  SegmentTree<int> segmentTree1(a, 0);
  CHECK(segmentTree1.sum(0, 1) == 0);

  int b[] = {1, 2, 3, 4};
  SegmentTree<int> segmentTree2(b, b + 4);
  CHECK(segmentTree2.sum(0, 4) == 10);
  CHECK(segmentTree2.sum(0, 3) == 6);
  CHECK(segmentTree2.sum(0, 2) == 3);
  CHECK(segmentTree2.sum(1, 4) == 9);
  CHECK(segmentTree2.sum(2, 4) == 7);
  CHECK(segmentTree2.sum(0, 2) == 3);
  CHECK(segmentTree2.sum(0, 1) == 1);
  CHECK(segmentTree2.sum(1, 2) == 2);
  CHECK(segmentTree2.sum(2, 3) == 3);
  CHECK(segmentTree2.sum(3, 4) == 4);

  CHECK(segmentTree2.sum(0, 0) == 0);
}

/*
 * Testing update function.
 */
TEST_CASE("update")
{
  int b[] = {1, 2, 3, 4};
  SegmentTree<int> segmentTree1(b, b + 4);

  segmentTree1.update(0, 10);
  CHECK(segmentTree1.sum(0, 4) == 19);

  segmentTree1.update(3, 10);
  CHECK(segmentTree1.sum(0, 4) == 25);
  CHECK(segmentTree1.sum(2, 4) == 13);
}

TEST_CASE("Time Complexity")
{
  long int size = 100000;
  std::vector<long int> a(size);
  for (long int i = 0; i < size; ++i)
  {
    a[i] = i;
  }
  SegmentTree<long int> segmentTree1(a.begin(), a.end());
  print_time(a, segmentTree1, 0, size);
  print_time(a, segmentTree1, 0, size / 2);
  print_time(a, segmentTree1, 0, size / 4);
  print_time(a, segmentTree1, 0, size / 8);
  print_time(a, segmentTree1, 0, size / 16);
  print_time(a, segmentTree1, 0, size / 32);
  print_time(a, segmentTree1, 0, size / 64);
  print_time(a, segmentTree1, 0, size / 128);
  print_time(a, segmentTree1, size / 2, size);
  print_time(a, segmentTree1, 1234, 5678);
  print_time(a, segmentTree1, 1234, 2500);
}
template <typename T>
void print_time(std::vector<T> &vect, SegmentTree<T> &seg, long int l, long int r)
{
  auto t1 = std::chrono::high_resolution_clock::now();

  T stSum = seg.sum(l, r);

  auto t2 = std::chrono::high_resolution_clock::now();
  auto stDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

  t1 = std::chrono::high_resolution_clock::now();

  long int init = 0;
  T vectSum = accumulate(vect.begin() + l, vect.begin() + r, init);

  t2 = std::chrono::high_resolution_clock::now();
  auto vectDuration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

  std::cout << "\n\nMicroseconds taken to find sum of an array in range[" << l << ", " << r << "]\n";

  std::cout << "Linear:\t" << vectDuration << "\t| Sum:\t" << vectSum << "\n";
  std::cout << "S_tree:\t" << stDuration << "\t| Sum:\t" << stSum << "\n";
}

template <typename T, typename ptr_t>
T accumulate(ptr_t first, ptr_t last, T init)
{
  while (first != last)
  {
    init = init + *first;
    ++first;
  }
  return init;
}
