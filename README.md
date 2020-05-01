# Generic-Implementation-of-Segment-Trees-in-Cpp
A segment tree is a data structure that has primarily the following features.
1.  It allows answering range queries over an sequence of elements effectively. Some applications are ~
    *  Finding the sum of consecutive array elements in O(log n) time.
    *  Finding the minimum element of a sequence in O(log n) time.
2.   It is flexible enough to allow modifying the elements of the sequence.

Segment trees can be generalized to larger dimensions. 2D segment trees can be used for answering sum or min queries over a sub-section of a matrix in O(log<sup>2</sup>n) time.

My notes on segment trees can be found [here](https://docs.google.com/document/d/e/2PACX-1vS-ScTjtsW0UN2GmZnL8J_GBJdi4U3_7I6Gb5MRbbzNblQ-9QHwYFCLs6n95obU_zSdZBqL__4Pt4qE/pub).

___

### Simple Segment Tree

While   more   complex   implementations   of   a   segment tree  do  exist,  the scope of this  project is limited to  implementing  a  simple  segment  tree  with  the  following functionalities:

Given an sequence a[0. . .  n -1]
1.  find the sum of elements between indices l and r in O(log n) time.
2.  handle  changing  values  of  the  elements  of  the  array in O(log n) time

####  Operations
1.  find -  Get iterator to element (public member function)
```cpp
/**
 *  @brief  Finds the first element that matches key.
 *  @param  key  Element to located.
 *  @return Iterator to an element with key equivalent to key.
 * 	If no such element is found, past-the-end iterator is returned.
 */
 iterator find(const T key);
```
  
2.  count -  Count elements with a specific value (public member function)
```cpp
/**
 *  @brief  Finds the number of elements.
 *  @param  key   Element to located.
 *  @return Number of elements with specified key.
 */
int count(const T &key);
```
3.  lower_bound - Return iterator to lower bound (public member function)
```cpp
/**
 *  @brief  Finds the beginning of a subsequence matching given key.
 *  @param  key  Element to be located.
 *  @return Iterator pointing to first element equal to or greater than key, or end().
 */
iterator lower_bound(const T &key);
```
4.  upper_bound - Return iterator to upper bound (public member function)
```cpp
/**
 *  @brief  Finds the end of a subsequence matching given key.
 *  @param  key   Element to be located.
 *  @return Iterator pointing to the first element greater than key, or end().
 */
iterator upper_bound(const T &key);
```
5.  equal_range - Get range of equal elements (public member function)
```cpp
/**
 *  @brief	Returns an iterator that points one past the last element in the container. 
 *  @param  key  Key to be located.
 *  @return Iterator pointing to the first element greater than key, or end().
 *
 *	This is equivalent to make_pair(c.lower_bound(val), c.upper_bound(val))
 */
std::pair<iterator, iterator> equal_range(const T &key)
```
####  Iterators Supported
This implementation supports bidirectional iterators.

1.  begin -   Returns an iterator referring to the first element in the container.
2.  end   -   Returns an iterator referring to the first element in the container.
3.  rbegin -  Returns a reverse iterator referring to the last element in the container.
4.  rend -    Returns a reverse iterator referring to one past the first element in the container.

