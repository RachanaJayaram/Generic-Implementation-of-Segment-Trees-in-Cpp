#include "iterator.h"
#include <algorithm>
namespace st
{
/*
CLASS SUMMARY
	// Constructors / Destructors.
	SegmentTree();
	SegmentTree(const SegmentTree& x);
	SegmentTree(const T *input, int n);
	SegmentTree(_InputIterator first, _InputIterator last);
	~SegmentTree();

	// Copy operator.
	SegmentTree& operator=(const SegmentTree& x);

	// Iterators.
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	// Operations - Standard algorithms.
	int count(const T &key);
	iterator find(const T key);
	iterator lower_bound(const T &key);
	iterator upper_bound(const T &key);
	std::pair<iterator, iterator> equal_range(const T &key);

	// Capacity 
	bool empty();
	int size();

	// Specialized algorithms.
	T sum(int queryLeft, int queryRight);
	void update(int index, T newVal);

	// Util functions for the segment tree.
	void build(int currentVertice, int rangeLeft, int rangeRight);
	T sum_util(int queryLeft, int queryRight, int currentVertice, int rangeLeft, int rangeRight);
	void update_util(int index, T newVal, int currentVertice, int rangeLeft, int rangeRight);
*/
template <typename T>
class SegmentTree
{
public:
	// Iterator-related typedefs.
	typedef Iterator<T> iterator;
	typedef ReverseIterator<T> reverse_iterator;

private:
	// Underlying data structure for the segment tree.
	T *cont_;
	T *tree_;
	int n_;

public:
	// Constructors/Destructors.

	/**
	 *  @brief  Creates a Segment Tree with no elements.
	 */
	explicit SegmentTree() : cont_(nullptr), tree_(nullptr), n_(0) {}

	/**
	 *  @brief  Copy constructor.
	 */
	SegmentTree(const SegmentTree &x) : cont_(new T[x.n_]), tree_(new T[4 * x.n_]), n_(x.n_)
	{
		for (int i = 0; i < n_; i++)
		{
			cont_[i] = x.cont_[i];
		}
		for (int i = 0; i < 4 * n_; i++)
		{
			tree_[i] = x.tree_[i];
		}
	}

	/**
       *  @brief  SegmentTree assignment operator.
       *  @param  x  A SegmentTree of identical element and allocator types.
       *
       *  All the elements of @a x are copied, but unlike the copy constructor,
       *  the allocator object is not copied.
       */
	SegmentTree &operator=(const SegmentTree &x)
	{
		cont_ = new T[x.n_];
		tree_ = new T[4 * x.n_];
		n_ = x.n_;

		for (int i = 0; i < n_; i++)
		{
			cont_[i] = x.cont_[i];
		}
		for (int i = 0; i < 4 * n_; i++)
		{
			tree_[i] = x.tree_[i];
		}
		return *this;
	}

	/**
	 *  @brief  Creates a segment tree from an input array.
	 *  @param  input  Input array whose elements are used to build the segment tree.
	 *  @param  n  Number of elements of input array to use.
	 * 
	 *   Create a segment tree consisting of copies of the elements from 0 to n - 1.
	 * 	 This is linear in N. 
	 *   A segment tree has at max 4*n number of nodes, where n is the size of the input.
	 */
	explicit SegmentTree(const T *input, int n) : cont_(new T[n]), tree_(new T[4 * n]), n_(n)
	{
		for (int i = 0; i < n; ++i)
		{
			cont_[i] = input[i];
		}
		if (n_ > 0)
			build(0, 0, n_ - 1);
	}

	/**
	 *  @brief  Builds a segment tree from a range.
	 *  @param  first  An input iterator.
	 *  @param  last  An input iterator.
	 *
	 *  Create a segment tree consisting of copies of the elements from [first,last).
	 *  This is linear in N if the range is already sorted, and NlogN
	 *  otherwise (where N is distance(first,last)).
	 */
	template <typename _InputIterator>
	explicit SegmentTree(_InputIterator first, _InputIterator last)
	{
		n_ = last - first;
		cont_ = new T[n_];
		tree_ = new T[4 * n_];
		int i = 0;
		while (first != last)
		{
			cont_[i] = *first;
			++first;
			++i;
		}
		if (n_ > 0)
			build(0, 0, n_ - 1);
	}

	/**
	 *  @brief  Destructor for segment tree.
	 */
	~SegmentTree()
	{
		delete[] cont_;
		delete[] tree_;
		n_ = 0;
	}

	/**
	 *  Returns an iterator referring to the first element in the container.
	 */
	iterator begin() { return iterator(cont_); }

	/**
	 * Returns an iterator that points one past the last element in the container. 
	 */
	iterator end() { return iterator(cont_ + n_); }

	/**
	 *  Returns a reverse iterator referring to the last element in the container.
	 */
	reverse_iterator rbegin() { return reverse_iterator(cont_ + n_ - 1); }

	/**
	 *  Returns a reverse iterator referring to one past the first element in the container.
	 */
	reverse_iterator rend() { return reverse_iterator(cont_ - 1); }

	/**
	 *  @brief  Finds the number of elements.
	 *  @param  key  Element to located.
	 *  @return	Number of elements with specified key.
	 */
	int count(const T &key)
	{
		iterator first = begin(), last = end();
		int count = 0;
		while (first != last)
		{
			if (*first == key)
				++count;
			++first;
		}
		return count;
	}

	/**
	 *  @brief  Finds the first element that matches key.
	 *  @param  key  Element to located.
	 *  @return Iterator to an element with key equivalent to key.
	 * 			If no such element is found, past-the-end iterator is returned.
	 */
	iterator find(const T key)
	{
		iterator first = begin(), last = end();
		while (first != last && *first != key)
		{
			++first;
		}
		return first;
	}

	/**
	 *  @brief	Finds the beginning of a subsequence matching given key.
	 *  @param  key  Key to be located.
	 *  @return Iterator pointing to first element equal to or greater than key, or end().
	 *
	 *  This function returns the first element of a subsequence of elements
	 *  that matches the given key.  If unsuccessful it returns an iterator
	 *  pointing to the first element that has a greater value than given key
	 *  or end() if no such element exists.
	 */
	iterator lower_bound(const T &key)
	{
		iterator first = begin(), last = end();
		while (first != last && *first < key)
		{
			++first;
		}
		return first;
	}

	/**
	 *  @brief	Finds the end of a subsequence matching given key.
	 *  @param  key  Key to be located.
	 *  @return Iterator pointing to the first element greater than key, or end().
	 */
	iterator upper_bound(const T &key)
	{
		iterator first = begin(), last = end();
		while (first != last && *first <= key)
		{
			++first;
		}
		return first;
	}

	/**
	 * Returns an iterator that points one past the last element in the container. 
	 * 		std::make_pair(c.lower_bound(val), c.upper_bound(val))
	 */
	std::pair<iterator, iterator> equal_range(const T &key)
	{
		return std::make_pair(lower_bound(key), upper_bound(key));
	}

	///  Returns true if the SegmentTree is empty.
	bool empty() const { return n_ == 0; }

	///  Returns the size of the SegmentTree.
	int size() const { return n_; }

	/**
	 *  @brief Finds sum of consecutive elements in a range [queryLeft,queryRight).
	 *  @param  queryLeft Left index of range for which sum has to be found.
	 *  @param  queryRight Right index of range (Non-inclusive) for which sum has to be found.
	 *  @return  Sum of range of consecutive elements from [queryLeft, queryRight)
	 *
	 *  Takes O(logN) time.
	 */
	T sum(int queryLeft, int queryRight)
	{
		if (n_ > 0 && queryLeft < queryRight)
			return sum_util(queryLeft, queryRight - 1, 0, 0, n_ - 1);
		return 0;
	}

	/**
	 *  @brief Modify a specific element in the tree.
	 *  @param  index Index of element to be updated.
	 *  @param  newVal New value of the element.
	 *  Takes O(logN) time.
	 */
	void update(int index, T newVal)
	{
		if (n_ > 0 && index <= newVal)
		{
			cont_[index] = newVal;
			update_util(index, newVal, 0, 0, n_ - 1);
		}
	}

private:
	/**
	 *  @brief Build the segment tree.
	 *  @param  currentVertice Indice of current vertice in the segment tree.
	 *  @param  rangeLeft Left indice in the input array of range spanned by current vertice.
	 *  @param  rangeRight Right indice in the input array of range spanned by current vertice.
	 *
	 *  Takes O(N) time - linear in size of input.
	 */
	void build(int currentVertice, int rangeLeft, int rangeRight)
	{
		if (rangeLeft == rangeRight)
		{
			tree_[currentVertice] = cont_[rangeLeft];
		}
		else
		{
			int mid = rangeLeft + (rangeRight - rangeLeft) / 2;
			build(currentVertice * 2 + 1, rangeLeft, mid);
			build(currentVertice * 2 + 2, mid + 1, rangeRight);
			tree_[currentVertice] = tree_[currentVertice * 2 + 1] + tree_[currentVertice * 2 + 2];
		}
	}

	/**
	 *  @brief  Util function to find sum of consecutive elements in a range.
	 *  @param  queryLeft Left indice in the input array of query range.
	 *  @param  queryRight Right indice in the input array of query range (inclusive).
	 *  @param  currentVertice Indice of current vertice in the segment tree.
	 *  @param  rangeLeft Left indice in the input array of range spanned by current vertice.
	 *  @param  rangeRight Right indice in the input array of range spanned by current vertice.
	 *  @return  Sum of range of consecutive elements from [queryLeft, queryRight]
	 * 
	 *  Takes O(logN) time.
	 */
	T sum_util(int queryLeft, int queryRight, int currentVertice, int rangeLeft, int rangeRight)
	{
		if (queryLeft > queryRight)
			return 0;
		if (queryLeft == rangeLeft && queryRight == rangeRight)
		{
			return tree_[currentVertice];
		}
		int mid = rangeLeft + (rangeRight - rangeLeft) / 2;

		return sum_util(queryLeft, std::min(queryRight, mid), currentVertice * 2 + 1, rangeLeft, mid) +
			   sum_util(std::max(queryLeft, mid + 1), queryRight, currentVertice * 2 + 2, mid + 1, rangeRight);
	}

	/**
	 *  @brief  Util function to modify a specific element in the tree.
	 *  @param  index Index of element to be updated.
	 *  @param  newVal New value of the element.
	 *  @param  currentVertice Indice of current vertice in the segment tree.
	 *  @param  rangeLeft Left indice in the input array of range spanned by current vertice.
	 *  @param  rangeRight Right indice in the input array of range spanned by current vertice.
	 *
	 *  Takes O(logN) time.
	 */
	void update_util(int index, T newVal, int currentVertice, int rangeLeft, int rangeRight)
	{
		if (rangeLeft == rangeRight)
		{
			tree_[currentVertice] = newVal;
		}
		else
		{
			int mid = rangeLeft + (rangeRight - rangeLeft) / 2;
			if (index <= mid)
				update_util(index, newVal, currentVertice * 2 + 1, rangeLeft, mid);
			else
				update_util(index, newVal, currentVertice * 2 + 2, mid + 1, rangeRight);

			tree_[currentVertice] = tree_[currentVertice * 2 + 1] + tree_[currentVertice * 2 + 2];
		}
	}
};
} // namespace st