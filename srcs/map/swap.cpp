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

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	map<char, int>::const_iterator tmp = foo.begin();
	map<char, int>::iterator tmp1 = foo.begin();

	std::cout << tmp->first << std::endl;
	std::cout << tmp1->first << std::endl;
	print(foo);
	print(bar);

 	swap(bar, foo);
	
	std::cout << tmp->first << std::endl;
	std::cout << tmp1->first << std::endl;
	print(foo);
	print(bar);

	return 0;
}
