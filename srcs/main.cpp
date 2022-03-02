#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <stdlib.h>
#include "red_black_tree.hpp"

#if 0
	#include <vector>
	#define TESTED_NAMESPACE std
#else
	#include <vector.hpp>
	#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type


int		main(void)
{
	Node<TESTED_TYPE> n;
	Node<TESTED_TYPE> n1(5);
	Node<TESTED_TYPE> n2(n);
	Node<TESTED_TYPE> n3 = n1;

	std::cout << n << std::endl;
	std::cout << n1 << std::endl;
	std::cout << n2 << std::endl;
	std::cout << n3 << std::endl;

	Tree<TESTED_TYPE> t;
	t.insert(2);
	t.insert(1);
	t.insert(1);
	t.insert(3);

	t.print_keys();

	try {
		std::cout << *(t.search(1)) << std::endl;
		std::cout << t.search(11) << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return (0);
}
