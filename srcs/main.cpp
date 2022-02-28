#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
#else
	#include <vector.hpp>
#endif

#include <stdlib.h>

int main( void ) {

	ft::vector<int> x;
	ft::vector<int> vector_int(4);
	ft::vector<std::string> vector_str;

	ft::vector<int> y = x;

	return (0);
}
