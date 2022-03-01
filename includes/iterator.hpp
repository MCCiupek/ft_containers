#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# pragma once
# include <iostream>

namespace ft
{
	/* ------------------------------------------------------------- */
	/* ---------------------------- TAGS --------------------------- */

	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* ------------------------------------------------------------- */
	/* -------------------------- TRAITS --------------------------- */

	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	}; /* struct iterator_traits */

	template<class T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;
	}; /* struct iterator_traits<T*> */

	template<class T>
	struct iterator_traits<const T*> {
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef random_access_iterator_tag				iterator_category;
	}; /* struct iterator_traits<const T*> */

	/* ------------------------------------------------------------- */
	/* ---------------------- BASE ITERATOR ------------------------ */

	template<
		class Category,
		class T,
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
	struct iterator
	{
		typedef Category								iterator_category;
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
	}; /* struct iterator */

	/* ------------------------------------------------------------- */
	/* ------------------ ITERATORS OPERATIONS --------------------- */

	template <class InputIterator, class Distance>
	void advance( InputIterator& i, Distance n ) {
		for (; n > 0; --n)
			++i;
	}; /* advance */

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
		distance( InputIterator first, InputIterator last ) {
			typename iterator_traits<InputIterator>::difference_type __r(0);
			for (; first != last; ++first)
				++__r;
			return __r;
		}; /* distance */

	template <class InputIterator>
	InputIterator next( InputIterator x,
		typename iterator_traits<InputIterator>::difference_type n = 1 ) {
			if (n >= 0)
				advance(x, n);
			return x;
		}; /* next */

	template <class BidirectionalIterator>
	// TODO: Enable if bidirectional iterator
	BidirectionalIterator prev( BidirectionalIterator x,
		typename iterator_traits<BidirectionalIterator>::difference_type n = 1 ) {
			if (n >= 0)
				advance(x, -n);
			return x;
		}; /* prev */

	/* ------------------------------------------------------------- */
	/* ------------------ REVERSE ITERATORS --------------------- */

	template <class Iter>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iter>::iterator_category,
						typename iterator_traits<Iter>::value_type,
						typename iterator_traits<Iter>::difference_type,
						typename iterator_traits<Iter>::pointer,
						typename iterator_traits<Iter>::reference>
	{

		protected:
			Iter current;

		public:
			typedef Iter                                            iterator_type;
			typedef typename iterator_traits<Iter>::difference_type difference_type;
			typedef typename iterator_traits<Iter>::reference       reference;
			typedef typename iterator_traits<Iter>::pointer         pointer;

			reverse_iterator() : current() {}
			explicit reverse_iterator(Iter x) : current(x) {}

			template<class U>
			reverse_iterator( const reverse_iterator<U>& other )  : current(other.base()) {}

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other) { current = other.base(); return *this; }

			Iter base() const { return current; }

			reference operator*() const { iterator_type tmp(current); return *(--tmp); }
			pointer operator->() const { return &(operator*()); }
			
			reference         operator[]( difference_type __n ) const { return *(*this + __n); }

			reverse_iterator& operator++() { --current; return *this; }
			reverse_iterator  operator++( int ) { reverse_iterator __tmp(*this); --current; return __tmp; }
			reverse_iterator& operator--() { ++current; return *this; }
			reverse_iterator  operator--( int ) { reverse_iterator __tmp(*this); ++current; return __tmp; }
			reverse_iterator  operator+( difference_type __n ) const { return reverse_iterator(current - __n); }
			reverse_iterator& operator+=( difference_type __n ) { current -= __n; return *this; }
			reverse_iterator  operator-( difference_type __n ) const { return reverse_iterator(current + __n); }
			reverse_iterator& operator-=( difference_type __n ) { current += __n; return *this; }
			
	}; /* class reverse iterator */

	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() == y.base(); }

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() > y.base(); }

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() < y.base(); }

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() != y.base(); }

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() >= y.base(); }

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template<typename T>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T> &x, const reverse_iterator<T> &y) { return y.base() - x.base(); }

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return y.base() - x.base(); }

	template<typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type __n, const reverse_iterator<T> &i) { return i + __n; }

	/* ------------------------------------------------------------- */
	/* ---------------------- VECT ITERATOR ------------------------ */
	
	template<typename T>
	class random_access_iterator : public iterator <random_access_iterator_tag, T> {

		public:

			typedef typename random_access_iterator<T>::reference		reference;
			typedef typename random_access_iterator<T>::pointer			pointer;
			typedef typename random_access_iterator<T>::difference_type	difference_type;

		protected:

			pointer	current;

		public:

			random_access_iterator( void ) : current() {};
			explicit random_access_iterator( pointer x ) : current(x) {};
			random_access_iterator( const random_access_iterator &other ) : current(other.base()) {};
			random_access_iterator &operator=( const random_access_iterator &other ) { current = other.base(); return *this; };
			~random_access_iterator( void ) {};

			pointer base( void ) const { return current; }

			reference operator*( void ) const { return *current; }
			pointer operator->( void ) const { return &(operator*()); }

			reference operator[]( difference_type __n ) const { return *(*this + __n); }

			random_access_iterator &operator++( void ) { ++current; return *this; }
			random_access_iterator operator++( int ) { random_access_iterator __tmp(*this); ++current; return __tmp; }
			random_access_iterator &operator+=( difference_type __n ) { current += __n; return *this; }
			random_access_iterator operator+( difference_type __n ) const { return random_access_iterator(current + __n); }
			random_access_iterator &operator--( void ) { --current; return *this; }
			random_access_iterator operator--( int ) { random_access_iterator __tmp(*this); --current; return __tmp; }
			random_access_iterator &operator-=( difference_type __n ) { current -= __n; return *this; }
			random_access_iterator operator-( difference_type __n ) const { return random_access_iterator(current - __n); }

			operator random_access_iterator<const T>( void ) const { return random_access_iterator<const T>(current); }

	}; /* class random_access_iterator */

	template <class Iter1, class Iter2>
	bool operator==(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() == y.base(); }

	template <class Iter1, class Iter2>
	bool operator<(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() < y.base(); }

	template <class Iter1, class Iter2>
	bool operator>(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() > y.base(); }

	template <class Iter1, class Iter2>
	bool operator!=(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() != y.base(); }

	template <class Iter1, class Iter2>
	bool operator<=(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template <class Iter1, class Iter2>
	bool operator>=(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() >= y.base(); }

	template<typename T>
	typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &x, const random_access_iterator<T> &y) { return x.base() - y.base(); }

	template <class Iter1, class Iter2>
	typename random_access_iterator<Iter1>::difference_type operator-(const random_access_iterator<Iter1>& x, const random_access_iterator<Iter2>& y) { return x.base() - y.base(); }

	template<typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type __n, const random_access_iterator<T> &i) { return i + __n; }

} /* namespace ft */

#endif /* ITERATOR_HPP */