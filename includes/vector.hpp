#ifndef VECTOR_HPP
# define VECTOR_HPP

# pragma once
# include <iostream>
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "utility.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */

		public:

			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename ft::random_access_iterator<T> 			iterator;
			typedef typename ft::random_access_iterator<const T> 	const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		protected:

			pointer							__begin_;
			pointer							__end_;
			ft::pair<pointer, Allocator>	__end_cap_;

		private:

			pointer& __end_cap() { return __end_cap_.first; }
			const pointer& __end_cap() const { return __end_cap_.first; }
		
			allocator_type& __alloc() { return __end_cap_.second; }
			const allocator_type& __alloc() const { return __end_cap_.second; }

			void v_allocate(size_type n) {
				__begin_ = __alloc().allocate(n);
				__end_cap()  = __end_ = __begin_ + n;
			}

			template <typename InputIt>
			void range_init(pointer position, InputIt first, InputIt last) {
				for (; first != last; first++)
					__alloc().construct(position++, *first);
			}

			void value_init(pointer position, size_type n, const value_type& value) {
				for (size_type i = 0; i < n; i++)
					__alloc().construct(position++, value);
			}

			void realloc(size_type n) {
				pointer begin_new, end_new;
				if ( size() + n > max_size() ) {
					throw std::length_error("vector::reserve");
				}
				begin_new = end_new = __alloc().allocate(n);
				if (!empty())
				{
					for (pointer begin = __begin_; begin != __end_; begin++)
						__alloc().construct(end_new++, *begin);
				}
				this->~vector();
				__begin_ = begin_new;
				__end_ = end_new;
				__end_cap() = __begin_ + n;
			}

			difference_type insert_shared(pointer position, size_type n) {
				if ( !n )
					return -1;
				difference_type idx = position - __begin_;
				if ((__end_ + n > __end_cap()) || !__begin_)
				{
					realloc(std::max(size() + n, capacity() * 2));
					position = __begin_ + idx;
				}
				for (difference_type i = __end_ - position - 1; i >= 0; i--)
				{
					__alloc().construct(position + i + n, *(position + i));
					__alloc().destroy(position + i);
				}
				__end_ += n;
				return idx;
			}
		
		/* ------------------------------------------------------------- */
		/* ---------------- CONSTRUCTORS & DESTRUCTOR ------------------ */

		public:

			/**
			 *	Empty container constructor (default constructor)
			 *	Constructs an empty container, with no elements.
			 */
			explicit vector( const Allocator& alloc = Allocator() ) : 
				__begin_(NULL), __end_(NULL), __end_cap_(NULL, alloc) {};

			/**
			 *	Fill constructor
			 *	Constructs a container with @param count elements. Each element is a copy of @param value.
			 */
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) : 
				__begin_(NULL), __end_(NULL), __end_cap_(NULL, alloc)
			{
				v_allocate(count);
				value_init(__begin_, count, value);
			};
			
			/**
			 *	Range constructor
			 *	Constructs a container with as many elements as the range [ @param first, @param last ), 
			 *	with each element constructed from its corresponding element in that range, in the same order.
			 */
			template <class InputIt>
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0 ) :
					__begin_(NULL), __end_(NULL), __end_cap_(NULL, alloc)
			{
				difference_type n = ft::distance(first, last);
				v_allocate(n);
				range_init(__begin_, first, last);
            };

			/**
			 * 	Copy constructor
			 *  Constructs a container with a copy of each of the elements in @param other, in the same order.
			 */
			vector( const vector& other ) :
				__begin_(NULL), __end_(NULL), __end_cap_(NULL, other.get_allocator())
			{
				v_allocate(other.size());
				range_init(__begin_, other.begin(), other.end());
            };

			/**
			 * 	Vector destructor
			 * 	Destroys the container object.
			 */
			~vector() {
				clear();
				__alloc().deallocate(__begin_, capacity());
			};

			/**
			 * Assign content
			 * Assigns new contents to the container, replacing its current contents, 
			 * and modifying its size accordingly.
			 */
			vector& operator= (const vector& other) {
				if (this != &other)
					assign(other.begin(), other.end());
				return *this;
			};

			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin() { return iterator(__begin_); };
			const_iterator begin() const { return const_iterator(__begin_); };

			iterator end() { return iterator(__end_); };
			const_iterator end() const { return const_iterator(__end_); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			/* ------------------------------------------------------------- */
			/* ------------------------- CAPACITY -------------------------- */

			size_type size() const { return static_cast<size_type>(this->__end_ - this->__begin_); };

			size_type max_size() const { return static_cast<size_type>(get_allocator().max_size()); };

			void resize (size_type n, value_type val = value_type()) {
				if ( n < size() )
					erase(iterator(__begin_ + n), iterator(__end_));
				else
					insert(end(), n - size(), val);
			};

			size_type capacity() const { return static_cast<size_type>(__end_cap() - __begin_); };

			bool empty() const { return begin() == end(); };

			void reserve (size_type n) {
				if (n > capacity()) {
					realloc(n);
				}
			};

			/* ------------------------------------------------------------- */
			/* ----------------------- ELEMENT ACCESS ---------------------- */

			reference operator[] (size_type n) { return __begin_[n]; };

			const_reference operator[] (size_type n) const { return __begin_[n]; };

			reference at (size_type n) {
				if (n < 0 || n >= size())
					throw std::out_of_range("vector");
				return this->__begin_[n];
			};

			const_reference at (size_type n) const {
				if (n < 0 || n >= size())
					throw std::out_of_range("vector");
				return this->__begin_[n];
			};

			reference front() {
				if (!empty())
        			return *begin();
				return *end();
			};

			const_reference front() const {
				if (!empty())
        			return *begin();
				return *end();
			};

			reference back() {
				if (!empty())
        			return *(end() - 1);
				return *end();
			};

			const_reference back() const {
				if (!empty())
        			return *(end() - 1);
				return *end();
			};

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				difference_type size = ft::distance(first, last);

				clear();
				reserve(size);
				__end_ += size;
				range_init(__begin_, first, last);
			};

			void assign (size_type n, const value_type& val) {
				clear();
				reserve(n);
				__end_ += n;
				value_init(__begin_, n, val);
			};

			void push_back (const value_type& val) { insert(end(), val); };

			void pop_back() { erase(iterator(__end_ - 1), end()); };

			iterator insert (iterator position, const value_type& val) {
				difference_type idx = position.base() - __begin_;
				insert(position, 1, val);
				return (iterator(__begin_ + idx));
			};

			void insert (iterator position, size_type n, const value_type& val) {
				difference_type idx = insert_shared(position.base(), n);
				value_init(__begin_ + idx, n, val);
			};

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				difference_type size = ft::distance(first, last);
				difference_type idx = insert_shared(position.base(), size);
				range_init(__begin_ + idx, first, last);
			};

			iterator erase (iterator position) { return erase(position, position + 1); };

			iterator erase (iterator first, iterator last) { 
				iterator ret = first;
				iterator tmp = first;
				while (first != last)
				{
					__alloc().destroy(&(*first));
					first++;
				}
				for (int i = 0; i < __end_ - &(*last); i++)
				{
					__alloc().construct(&(*tmp) + i, *(&(*last) + i));
					__alloc().destroy(&(*last) + i);
				}
				__end_ -= (&(*last) - &(*tmp));
				return (ret);
			};

			void swap (vector& x) {
				std::swap(__begin_, x.__begin_);
				std::swap(__end_, x.__end_);
				std::swap(__end_cap(), x.__end_cap());
				std::swap(__alloc(), x.__alloc());
			};

			void clear() { erase(begin(), end()); };

			/* ------------------------------------------------------------- */
			/* ------------------------- ALLOCATOR ------------------------- */

			allocator_type get_allocator() const { return __alloc(); };

	}; // class vector

	/* ------------------------------------------------------------- */
	/* ---------------- NON-MEMBER FUNCTION OVERLOAD --------------- */

	/* 		Relational operators: */

	template <class T, class Allocator>
	bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Allocator>
	bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (!(lhs == rhs));
	};

	template <class T, class Allocator>
	bool operator<  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Allocator>
	bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (!(rhs < lhs));
	};

	template <class T, class Allocator>
	bool operator>  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (rhs < lhs);
	};

	template <class T, class Allocator>
	bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs) {
		return (!(lhs < rhs));
	};

	/* 		Swap: */

	template <class T, class Allocator>
	void swap (vector<T,Allocator>& x, vector<T,Allocator>& y) {
		x.swap(y);
	};

} // namespace ft

#endif