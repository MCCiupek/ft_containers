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

			reference operator*() const { Iter __tmp = current; return *--__tmp; }
			pointer operator->() const { return std::addressof(operator*()); }
			
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
	bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() < y.base(); }

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() > y.base(); }

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() != y.base(); }

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() >= y.base(); }

	template <class Iter1, class Iter2>
	bool operator+(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() + y.base(); }

	template <class Iter1, class Iter2>
	bool operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() - y.base(); }

	/* ------------------------------------------------------------- */
	/* ---------------------- VECT ITERATOR ------------------------ */
	
	template<typename T>
	class vector_iterator : public iterator <random_access_iterator_tag, T> {

		public:
			typedef typename vector_iterator<T>::reference			reference;
			typedef typename vector_iterator<T>::pointer			pointer;
			typedef typename vector_iterator<T>::difference_type	difference_type;

		protected:
			pointer	current;

		public:

			vector_iterator( void ) : current() {};
			explicit vector_iterator( pointer x ) : current(x) {};
			vector_iterator( const vector_iterator &other ) : current(other.base()) {};
			vector_iterator &operator=( const vector_iterator &other ) { current = other.base(); return *this; };
			~vector_iterator( void ) {};

			pointer base( void ) const { return current; }

			reference operator*( void ) const { pointer __tmp = current; return *++__tmp; }
			pointer operator->( void ) const { return std::addressof(operator*()); }

			reference operator[]( difference_type __n ) const { return *(*this + __n); }

			vector_iterator &operator++( void ) { ++current; return *this; }
			vector_iterator operator++( int ) { vector_iterator __tmp(*this); ++current; return __tmp; }
			vector_iterator &operator+=( difference_type __n ) { current += __n; return *this; }
			vector_iterator operator+( difference_type __n ) const { return vector_iterator(current + __n); }
			vector_iterator &operator--( void ) { --current; return *this; }
			vector_iterator operator--( int ) { vector_iterator __tmp(*this); --current; return __tmp; }
			vector_iterator &operator-=( difference_type __n ) { current -= __n; return *this; }
			vector_iterator operator-( difference_type __n ) const { return vector_iterator(current - __n); }

	}; /* class vector_iterator */

	template <class Iter1, class Iter2>
	bool operator==(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() == y.base(); }

	template <class Iter1, class Iter2>
	bool operator<(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() < y.base(); }

	template <class Iter1, class Iter2>
	bool operator>(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() > y.base(); }

	template <class Iter1, class Iter2>
	bool operator!=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() != y.base(); }

	template <class Iter1, class Iter2>
	bool operator<=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template <class Iter1, class Iter2>
	bool operator>=(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() >= y.base(); }

	template <class Iter1, class Iter2>
	bool operator+(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() + y.base(); }

	template <class Iter1, class Iter2>
	bool operator-(const vector_iterator<Iter1>& x, const vector_iterator<Iter2>& y) { return x.base() - y.base(); }

} /* namespace ft */

#endif /* ITERATOR_HPP */