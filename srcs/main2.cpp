#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <stdlib.h>
#include "red_black_tree.hpp"
#include <stdlib.h>


#if TESTED_NAMESPACE_STD
	#include <vector>
	#include <map>
	#include <stack>
	#define TESTED_NAMESPACE std
	#define TEST 0
#endif
#if TESTED_NAMESPACE_FT
	#include "vector.hpp"
	#include "map.hpp"
	#include "stack.hpp"
	#define TESTED_NAMESPACE ft
	#define TEST 1
#endif

#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type
#define _pair TESTED_NAMESPACE::pair

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

int		main(void)
{
	if (TEST == 0)
		std::cout << "std" << std::endl;
	if (TEST == 1)
		std::cout << "ft" << std::endl;

	std::list<T3> lst;

	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	
	TESTED_NAMESPACE::map<T1, T2> m(lst.begin(), lst.end());
	TESTED_NAMESPACE::vector<T1> v;
	TESTED_NAMESPACE::stack<T2> s;
	
	return 0;
}