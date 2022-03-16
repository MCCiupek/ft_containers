#include <iostream>
#include <string>
#include <deque>
#if TESTED_NAMESPACE_STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	# define NAMESPACE std
	#define TEST 0
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
	#define NAMESPACE ft
	#define TEST 1
#endif

using namespace NAMESPACE;

template <class Key, class T>
void	print(map<Key, T>& lst)
{
	for (typename map<Key, T>::iterator it = lst.begin(); it != lst.end(); it++)
	std::cout << it->first << " => " << it->second << '\n';
}

int main ()
{
	map<char,int>				foo, bar;
	map<int, std::string>			test;
	map<int, int> *				ptr = new map<int,int>();

	foo['x']=100;
	foo['y']=200;
	foo['z']=300;

	delete ptr;

	bar = foo;
	
	map<char,int>				foo_range(foo.begin(), --foo.end());

	test[0]="foo";
	test[1]="bar";

	map<int, std::string>			test_cpy(test);

	print(foo);
	print(bar);
	print(test);
	print(foo_range);
	print(test_cpy);

	return 0;
}
