#include <iostream>
#include <vector>
#include "../segment_tree/segment_tree.h"
using namespace std;

template <typename ptr_t>
void print_elements(ptr_t first, ptr_t last)
{
	while (first != last)
		cout << *first++ << "\t";
	cout << std::endl;
}
int main()
{
	vector<float> daily_transactions{100.0, 250.0, 221.5, 455.0, 110.0, 189, 100.0};
	st::SegmentTree<float> transactions(daily_transactions.begin(), daily_transactions.end());
	cout << "Checking the size of the Segment tree. Size is : " << transactions.size() << std::endl;

	// Check if the size of the tree is zero.
	cout << "Check if the size of the tree is zero : " << std::boolalpha << transactions.empty() << std::endl;

	// Finding the Sum of daily transactions.
	cout << "Sum of all the transactions" << std::endl;
	cout << transactions.sum(0, daily_transactions.size()) << std::endl;

	// Print the elements of the tree.
	cout << std::endl
		 << "Elements of the tree" << std::endl;
	print_elements(transactions.begin(), transactions.end());

	// Updating Value of two transactions.
	transactions.update(0, 150.5);
	transactions.update(1, 200);
	cout << "Values after updating: " << std::endl;
	print_elements(transactions.begin(), transactions.end());

	// Copy the Elements into another segment tree.
	cout << std::endl
		 << "Using the copy contructor." << std::endl;
	st::SegmentTree<float> copy_of_transactions(transactions);

	cout << "Size of the copied segment tree : " << copy_of_transactions.size() << std::endl;

	cout << "Original tree " << std ::endl;
	print_elements(transactions.begin(), transactions.end());
	cout << "Copied tree " << std ::endl;
	print_elements(copy_of_transactions.begin(), copy_of_transactions.end());
	cout << std::endl;

	// Updating the copy constructor.
	copy_of_transactions.update(2, 240.5);
	transactions.update(2, 100);

	cout << std::endl
		 << "After updating the copied tree" << std::endl;
	cout << "Original tree " << std ::endl;
	print_elements(transactions.begin(), transactions.end());
	cout << "Copied tree " << std ::endl;
	print_elements(copy_of_transactions.begin(), copy_of_transactions.end());
	cout << std::endl;

	//Number of transaction with value 100
	std::cout << "The number of transactions with the value 100: " << transactions.count(100.0) << std::endl;
	print_elements(transactions.begin(), transactions.end());

	//Sum of transactions in a given range
	std::cout << "Find the Sum of Numbers between the index 2 and 3 : " << transactions.sum(2, 4) << std::endl;

	//Value greater than 240
	std::cout << "Lower Bound of 240 : ";
	auto value2 = transactions.lower_bound(240);
	if (value2 != transactions.end())
		cout << *value2 << std::endl;

	std::cout << "Upper Bound of 240 : ";
	auto value1 = transactions.upper_bound(240);
	if (value1 != transactions.end())
		cout << *value1 << std::endl;

	//Print all the sum values from the calculated from the given range.
	std::cout << std::endl
			  << "Sum of all possible ranges : ";
	cout << std::endl;
	int i = -1;
	int j = 0;
	while (i < transactions.size())
	{
		cout << "Starting from index " << i << ":\t";
		j = ++i;
		while (j < transactions.size())
			cout << transactions.sum(i, ++j) << "\t";
		cout << std::endl;
	}
	std::cout << "Sum of entire input : ";
	cout << transactions.sum(0, transactions.size()) << std::endl;
	return 0;
}