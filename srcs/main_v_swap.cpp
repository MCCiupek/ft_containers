#include <iostream>
#include <string>
#include <deque>
#if TESTED_NAMESPACE_STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
	#define TEST 0
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
	#define TEST 1
#endif

#include <stdlib.h>

void print_vec( ft::vector<int> v ) {
	ft::vector<int>::const_iterator it = v.begin(), ite = v.end();
	for (; it != ite; it++)
		std::cout << *it << std::endl;
}

int main( void ) {

	// if (TEST == 0)
	// 	std::cout << "std" << std::endl;
	// if (TEST == 1)
	// 	std::cout << "ft" << std::endl;

	ft::vector<int> v;
	ft::vector<int> vector;

	int _ratio = 3;

    vector.assign(1100 * _ratio, 11);
    ft::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);

    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);

	print_vec(v);
	print_vec(vector);
	print_vec(tmp);
	print_vec(tmp2);
	print_vec(tmp3);
	print_vec(tmp4);

    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);

	print_vec(v);
	print_vec(vector);
	print_vec(tmp);
	print_vec(tmp2);
	print_vec(tmp3);
	print_vec(tmp4);

    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    ft::swap(vector, tmp2);

	print_vec(v);
	print_vec(vector);
	print_vec(tmp);
	print_vec(tmp2);
	print_vec(tmp3);
	print_vec(tmp4);

    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    ft::swap(vector, tmp4);

	print_vec(v);
	print_vec(vector);
	print_vec(tmp);
	print_vec(tmp2);
	print_vec(tmp3);
	print_vec(tmp4);

    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

	print_vec(v);
	print_vec(vector);
	print_vec(tmp);
	print_vec(tmp2);
	print_vec(tmp3);
	print_vec(tmp4);
}
