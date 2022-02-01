#pragma once
#include <iostream>
#include "iterator.hpp"

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------ FT::VECTOR ------------------------- *
	*
	* (constructor):        Construct vector
	* (destructor):         Destruct vector
	* operator=:            Assign vector
	*
	* - Iterators:
	* begin:                Return iterator to beginning
	* end:                  Return iterator to end
	* rbegin:               Return reverse iterator to reverse beginning
	* rend:                 Return reverse iterator to reverse end
	*
	* - Capacity:
	* size:                 Return size
	* max_size:             Return maximum size
	* resize:               Change size
	* capacity:             Return size of allocated storage capacity
	* empty:                Test whether vector is empty
	* reserve:              Request a change in capacity
	*
	* - Element access:
	* operator[]:           Access element
	* at:                   Access element
	* front:                Access first element
	* back:                 Access last element
	*
	* - Modifiers:
	* assign:               Assign vector content
	* push_back:            Add element at the end
	* pop_back:             Delete last element
	* insert:               Insert elements
	* erase:                Erase elements
	* swap:                 Swap content
	* clear:                Clear content
	*
	* - Non-member function overloads:
	* relational operators: Relational operators for vector
	* swap:                 Exchange contents of two vectors
	* ------------------------------------------------------------- *
	*/

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */

		public:

			typedef T 										value_type;
			typedef Alloc									allocator_type;
			typedef vector<T>&								reference;
			typedef vector<T> const&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			typedef std::ptrdiff_t							difference_type;
			typedef size_t									size_type;

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		private:    

			Alloc			_alloc;         // Copy of allocator_type object
			pointer			_vector;        // Pointer to an array of T values
			size_type		_size;          // Number of T values inside the vector
			size_type		_capacity;      // Capacity allocated (can be greater than size)

		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */
		
		public:

			/**
			 *	Empty container constructor (default constructor)
			 *	Constructs an empty container, with no elements.
			 */
			explicit vector (const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(0), _capacity(0) {
				_vector = _alloc.allocate(_capacity);
			};

			/**
			 *	Fill constructor
			 *	Constructs a container with @param n elements. Each element is a copy of @param val.
			 */
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : 
					_alloc(alloc), _size(n), _capacity(n) {
				_vector = _alloc.allocate(_capacity);
                
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(&_vector[i], val);
			};
			
			/**
			 *	Range constructor
			 *	Constructs a container with as many elements as the range [ @param first, @param last ), 
			 *	with each element constructed from its corresponding element in that range, in the same order.
			 */
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
					_alloc(alloc), _size(0), _capacity(0) {
				for (InputIterator it; it != last; it++, _capacity++)
					_size++;

				_vector = _alloc.allocate(_capacity);

				for (int i = 0; first != last; ++first, ++i)
					_alloc.construct(&_vector[i], *first);
            };

			/**
			 * 	Copy constructor
			 * Constructs a container with a copy of each of the elements in @param x, in the same order.
			 */
			vector (const vector& x):
				_alloc(x._alloc), _size(x._size), _capacity(x._capacity)
			{
				_vector = _alloc.allocate(_capacity);

				for (ft::pair<int, const_iterator> i(0, x.begin()); i.second != x.end(); ++i.first, ++i.second)
					_alloc.construct(&_vector[i.first], *i.second);
            };

			/**
			 * 	Vector destructor
			 * 	Destroys the container object.
			 */
			~vector() {
				for (iterator it = begin(); it != end(); ++it)
					_alloc.destroy(&(*it));
				_alloc.deallocate(_vector, _capacity);
			};

			/**
			 * Assign content
			 * Assigns new contents to the container, replacing its current contents, 
			 * and modifying its size accordingly.
			 */
			vector& operator= (const vector& x) {
				vector y(x);
				swap(y);
				return *this;
			};

			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;

			reverse_iterator rend();
			const_reverse_iterator rend() const;

			/* ------------------------------------------------------------- */
			/* ------------------------- CAPACITY -------------------------- */

			size_type size() const;

			size_type max_size() const;

			void resize (size_type n, value_type val = value_type());

			size_type capacity() const;

			bool empty() const;

			void reserve (size_type n);

			/* ------------------------------------------------------------- */
			/* ----------------------- ELEMENT ACCESS ---------------------- */

			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;

			reference at (size_type n);
			const_reference at (size_type n) const;

			reference front();
			const_reference front() const;

			reference back();
			const_reference back() const;

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last);
			void assign (size_type n, const value_type& val);

			void push_back (const value_type& val);

			void pop_back();

			iterator insert (iterator position, const value_type& val);
			void insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last);

			iterator erase (iterator position);
			iterator erase (iterator first, iterator last);

			void swap (vector& x);

			void clear();

			/* ------------------------------------------------------------- */
			/* ------------------------- ALLOCATOR ------------------------- */

			allocator_type get_allocator() const;

	}; // class vector

	/* ------------------------------------------------------------- */
	/* ---------------- NON-MEMBER FUNCTION OVERLOAD --------------- */

	/* 		Relational operaors: */

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	/* 		Swap: */

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

} // namespace ft
