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

int main () {

	int r = 50;

	map<int, int> mp;
	map<int, int> mp1;

    for (int i = 0, j = 10; i < 30 * r; ++i, ++j) {
        mp.insert(make_pair(i, j));
    }
	std::cout << "inserted" << std::endl;
    map<int, int> mp2(mp);
	std::cout << "copy" << std::endl;
    mp1 = mp;
	std::cout << "eq" << std::endl;

	print(mp);
	print(mp1);
	print(mp2);

    return 0;
}