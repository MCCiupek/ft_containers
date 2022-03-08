#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <stdlib.h>
#include "red_black_tree.hpp"
#include <stdlib.h>

#if 0
	#include <vector>
	#include <map>
	#define TESTED_NAMESPACE std
#else
	#include <vector.hpp>
	#include <map.hpp>
	#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int
#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

# define ADD '+'
# define DELETE '-'

void basic_node( void ) {
	Node<TESTED_TYPE> n;
	Node<TESTED_TYPE> n1(5);
	Node<TESTED_TYPE> n2(n);
	Node<TESTED_TYPE> n3 = n1;

	std::cout << "*** NODE ***" << std::endl;

	std::cout << "node: ---" << std::endl;
	std::cout << n << std::endl;
	std::cout << "---------" << std::endl;
	// std::cout << n1 << std::endl;
	// std::cout << n2 << std::endl;
	// std::cout << n3 << std::endl;
}

void basic_tree( void ) {
	std::cout << std::endl << "*** BST ***" << std::endl;

	BinarySearchTree<TESTED_TYPE> t;
	t.insert(2);
	t.insert(1);
	t.insert(1);
	t.insert(3);

	std::cout << t << std::endl;

	try {
		std::cout << *(t.search(1)) << std::endl;
		std::cout << *(t.search(11)) << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void basic_rbt( void ) {
	
	std::cout << std::endl << "*** RBT ***" << std::endl;

	RedBlackTree<TESTED_TYPE> brt;
	std::cout << "create brt" << std::endl;

	std::cout << brt << std::endl;

	brt.insert(2);
	brt.insert(1);
	std::cout << "insert 2, 1" << std::endl;

	std::cout << brt << std::endl;

	brt.insert(1);
	brt.insert(3);
	std::cout << "insert 3, 1" << std::endl;

	std::cout << brt << std::endl;

	brt.remove(3);
	std::cout << "remove 3" << std::endl;

	std::cout << brt << std::endl;

	brt.remove(-3);
	brt.remove(2);
	std::cout << "remove -3, 2" << std::endl;

	std::cout << brt << std::endl;

	brt.remove(1);
	std::cout << "remove 1" << std::endl;

	std::cout << brt << std::endl;
}

void classic_tree( void ) {

	BinarySearchTree<TESTED_TYPE> tree;
	TESTED_TYPE elem;
	char flag;
	std::string buf;

	std::cin >> buf;

	while ( buf != "exit" ) {
		flag = buf[0];
		elem = std::atoi(&buf[1]);

		if (flag == ADD) {
			tree.insert(elem);
		}
		else if (flag == DELETE) {
			tree.remove(elem);
		} else {
			std::cout << "unknown flag" << std::endl;
		}
		std::cout << tree << std::endl;
		std::cin >> buf;
	}
}

void classic_rbt( void ) {

	RedBlackTree<TESTED_TYPE> brt;
	TESTED_TYPE elem;
	char flag;
	std::string buf;

	std::cin >> buf;

	while ( buf != "exit" ) {
		flag = buf[0];
		elem = std::atoi(&buf[1]);

		if (flag == ADD) {
			brt.insert(elem);
		}
		else if (flag == DELETE) {
			brt.remove(elem);
		} else {
			std::cout << "unknown flag" << std::endl;
		}
		std::cout << brt << std::endl;
		std::cin >> buf;
	}
}

void rand_rbt( int lngth ) {

	RedBlackTree<TESTED_TYPE> brt;

	srand(time(0));
	
	for(int i = 0; i < lngth; ++i)
		brt.insert(rand() % (lngth * 5) + 1);
	
	std::cout << brt << std::endl;

	std::cout << "min = " << *brt.min() << std::endl;
	std::cout << "max = " << *brt.max() << std::endl;
	std::cout << "size = " << brt.size() << std::endl;
}
		

int		main( int argc, char * argv[])
{
	(void)argc;
	(void)argv;
	//basic_node();

	//basic_tree();

	//basic_rbt();

	//classic_tree();

	classic_rbt();

	//if ( argc > 1 )
	//	rand_rbt(std::atoi(argv[1]));

	//TESTED_NAMESPACE::map<int, std::string> mymap;

	return 0;
}
