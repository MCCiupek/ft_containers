#include <iostream>
#include <string>
#include <deque>
#include <list>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <vector>
	namespace ft = std;
	#define TESTED_NAMESPACE std
#else
	#include <vector.hpp>
	#define TESTED_NAMESPACE ft
#endif

#define TESTED_TYPE int

#include <stdlib.h>


#define T_SIZE_TYPE typename TESTED_NAMESPACE::vector<T>::size_type

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = true)
{
	const T_SIZE_TYPE size = vct.size();
	const T_SIZE_TYPE capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();

		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template<typename T>
void print(ft::vector <T> const &a, std::string name="vector", int size=-1) {

	std::cout << name << " (size = " << static_cast<int>(a.size()) << ")" << ": "  << std::endl;

	if (size == -1 || size >= static_cast<int>(a.size()))
		for ( int i = 0; i < static_cast<int>(a.size()); i++ )
			std::cout << "   " << name << "[" << i << "] = " <<  a.at(i)  << std::endl;
	else {
		for ( int i = 0; i < size / 2; i++ )
			std::cout << a.at(i) << ' ';
		std::cout << "...";
		for ( int i = a.size() - size / 2; i < static_cast<int>(a.size()); i++ )
			std::cout << a.at(i) << ' ';
	}

	std::cout << std::endl;
}

void	is_empty(ft::vector<TESTED_TYPE> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}
void	prepost_incdec(TESTED_NAMESPACE::vector<TESTED_TYPE> &vct)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}



int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(7);

	for (unsigned long int i = 0; i < vct.size(); ++i)
	{
		vct.at(i) = (vct.size() - i) * 3;
		std::cout << "vct.at(): " << vct.at(i) << " | ";
		std::cout << "vct[]: " << vct[i] << std::endl;
	}
	printSize(vct);

	TESTED_NAMESPACE::vector<TESTED_TYPE> const vct_c(vct);

	printSize(vct_c);

	std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
	std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

	try {
		vct.at(10) = 42;
	}
	catch (std::out_of_range &e) {
		std::cout << "Catch out_of_range exception!" << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Catch exception: " << e.what() << std::endl;
	}
	return (0);
}
