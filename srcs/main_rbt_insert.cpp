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
#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT 20//(MAX_RAM / (int)sizeof(Buffer))


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if ( nl )
		o << std::endl;
	return "";
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	size_t i = 0;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it) {
			std::cout << "- " << printPair(it, false) << std::endl;
			if ( i++ > mp.size() )
				break;
		}
	}
	std::cout << "###############################################" << std::endl;
}


int main( void ) {
	
	ft::map<int, int> map_int;

	// Case 1
	map_int.insert(ft::make_pair(61, 61));

	std::cout << "###############################################" << std::endl;

	// Case 2
	map_int.insert(ft::make_pair(52, 52));
	std::cout << "###############################################" << std::endl;
	
	// Case 2
	map_int.insert(ft::make_pair(85, 85));
	std::cout << "###############################################" << std::endl;
	
	//map_int.insert(ft::make_pair(76, 76));
	//std::cout << "###############################################" << std::endl;
	
	
	// Case 31
	// map_int.insert(ft::make_pair(93, 93));
	// std::cout << "###############################################" << std::endl;
	// map_int.insert(ft::make_pair(100, 100));
	// std::cout << "###############################################" << std::endl;

	// Case 322
	// map_int.insert(ft::make_pair(93, 93));
	// std::cout << "###############################################" << std::endl;
	// map_int.insert(ft::make_pair(87, 87));
	// std::cout << "###############################################" << std::endl;

	// Case 323
	// map_int.insert(ft::make_pair(70, 70));
	// std::cout << "###############################################" << std::endl;
	// map_int.insert(ft::make_pair(69, 69));
	// std::cout << "###############################################" << std::endl;

	// Case 324
	map_int.insert(ft::make_pair(70, 70));
	std::cout << "###############################################" << std::endl;
	map_int.insert(ft::make_pair(75, 75));
	std::cout << "###############################################" << std::endl;


	printSize(map_int);



	//ft::map<int, int> copy = map_int;

	std::cout << "ok" << std::endl;

	return (0);
}