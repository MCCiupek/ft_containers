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

	template < class T, class Allocator = std::allocator<T> >
	class vector_base
	{
		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */

		public:

			typedef Allocator										allocator_type;
			// typedef allocator_traits<allocator_type>         		__alloc_traits;
    		typedef typename std::size_t       							size_type;

		protected:

			typedef T 												value_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename std::ptrdiff_t								difference_type;
			typedef typename ft::vector_iterator<T> 				iterator;
			typedef typename ft::vector_iterator<const T> 			const_iterator;

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

			pointer							__begin_;
			pointer							__end_;
			ft::pair<pointer, Allocator>	__end_cap_;

			pointer& __end_cap() { return __end_cap_.first; }
			const pointer& __end_cap() const { return __end_cap_.first; }
		
			allocator_type& __alloc() { return __end_cap_.second; }
			const allocator_type& __alloc() const { return __end_cap_.second; }

		/* ------------------------------------------------------------- */
		/* --------------------------- METHODS ------------------------- */

			vector_base(const allocator_type& __a = Allocator()) : __begin_(nullptr), __end_(nullptr), __end_cap_(nullptr, __a) {};
			
			~vector_base() {
				if (__begin_ != nullptr) {
					clear();
					__alloc().deallocate(__begin_, capacity());
				}
			};

			void clear() { destruct_at_end(__begin_); }
			
			size_type capacity() const { return static_cast<size_type>(__end_cap() - __begin_); }
			
			void destruct_at_end(pointer __new_last) {
				pointer __soon_to_be_end = __end_;
				while (__new_last != __soon_to_be_end)
					__alloc().destroy(--__soon_to_be_end);
				__end_ = __new_last;
			};

		private:

			void copy_assign_alloc(const vector_base& __c) {
				if (__alloc() != __c.__alloc())
				{
					clear();
					__alloc().deallocate(__begin_, capacity());
					__begin_ = __end_ = __end_cap() = nullptr;
				}
				__alloc() = __c.__alloc();
			}

			void move_assign_alloc(vector_base& __c) {
				if (__alloc() != __c.__alloc())
				{
					clear();
					__alloc().deallocate(__begin_, capacity());
					__begin_ = __end_ = __end_cap() = nullptr;
				}
				__alloc() = __c.__alloc();
				__c.clear();
				__c.__alloc().deallocate(__c.__begin_, __c.capacity());
				__c.__begin_ = __c.__end_ = __c.__end_cap() = nullptr;
			}

	}; /* vector_base */

	template < class T, class Allocator = std::allocator<T> >
	class vector : private vector_base<T, Allocator>
	{
		private:

			typedef vector_base<T, Allocator>				__base;
			typedef std::allocator<T>						__default_allocator_type;
			
		public:

			typedef vector									__self;
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef typename __base::reference				reference;
			typedef typename __base::const_reference		const_reference;
			typedef typename __base::size_type				size_type;
			typedef typename __base::difference_type		difference_type;
			typedef typename __base::pointer				pointer;
			typedef typename __base::const_pointer			const_pointer;
			typedef typename __base::iterator				iterator;
			typedef typename __base::const_iterator			const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
		private:

			pointer __end_cap() const { return __base::__end_cap(); };

			void v_allocate(size_type n) {
				begin() = end() = get_allocator().allocate(n);
				__end_cap() = begin() + n;
			}
		
		public:

			/**
			 *	Empty container constructor (default constructor)
			 *	Constructs an empty container, with no elements.
			 */
			explicit vector( const Allocator& alloc = Allocator() ) : __base(alloc) {};

			/**
			 *	Fill constructor
			 *	Constructs a container with @param count elements. Each element is a copy of @param value.
			 */
			explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator() ) : 
				__base(alloc)
			{
				v_allocate(count);
				for (size_t i = 0; i < count; begin()++, i++)
					get_allocator().construct(begin(), value);
			};
			
			/**
			 *	Range constructor
			 *	Constructs a container with as many elements as the range [ @param first, @param last ), 
			 *	with each element constructed from its corresponding element in that range, in the same order.
			 */
			template <class InputIt>
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) :
					__base(alloc)
			{
				size_type count = static_cast<size_type>(last - first);
				v_allocate(count);
				for (; first != last; ++first)
					get_allocator().construct(first, *first);
            };

			/**
			 * 	Copy constructor
			 *  Constructs a container with a copy of each of the elements in @param other, in the same order.
			 */
			vector( const vector& other ) :
				__base(other.__alloc())
			{
				v_allocate(other.size());
				for (size_type i = 0; i < other.size(); i++)
					get_allocator().construct(begin() + i, *(other.begin() + i));
            };

			/**
			 * 	Vector destructor
			 * 	Destroys the container object.
			 */
			~vector() {
				clear();
			};

			/**
			 * Assign content
			 * Assigns new contents to the container, replacing its current contents, 
			 * and modifying its size accordingly.
			 */
			vector& operator= (const vector& other) {
				if (this != &other) {
					__base::copy_assign_alloc(other);
					for (size_type i = 0; i < other.size(); i++)
						get_allocator().construct(begin() + i, *(other.begin() + i));
				}
				return *this;
			};

			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin() { return iterator(__base::__begin_); };
			const_iterator begin() const { return const_iterator(begin()); };

			iterator end() { return iterator(__base::__end_); };
			const_iterator end() const { return const_iterator(end()); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			/* ------------------------------------------------------------- */
			/* ------------------------- CAPACITY -------------------------- */

			size_type size() const { return static_cast<size_type>(this->__end_ - this->__begin_); };

			size_type max_size() const { return static_cast<size_type>(get_allocator().max_size()); };

			void resize (size_type n, value_type val = value_type()) {
				size_type old_size = size();

				if (old_size < n) {
					size_type to_add = static_cast<size_type>(__end_cap() - end());
					size_type room_left = n - old_size;
					if (to_add >= room_left)
						for (; to_add > 0; --to_add)
							get_allocator().construct(end()++, val);
					else
					{
						vector<T, Allocator> __new(n, val);
						for (size_type i = 0; i < size(); i++)
							__new.get_allocator().construct(__new.begin() + i, *(begin() + i));
						clear();
						*this = __new;
					}
				}
				else if (old_size > n)
					erase(iterator(begin() + n), iterator(end()));
			};

			size_type capacity() const { return __base::capacity(); };

			bool empty() const { return begin() == end(); };

			void reserve (size_type n) {
				if (n > capacity()) {
					resize(n);
				}
			};

			/* ------------------------------------------------------------- */
			/* ----------------------- ELEMENT ACCESS ---------------------- */

			reference operator[] (size_type n) {
				if (n < size())
					return this->__begin_[n];
				return *end();
				// ERR: "vector[] index out of bounds";
			};

			const_reference operator[] (size_type n) const{
				if (n < size())
					return this->__begin_[n];
				return *end();
				// ERR: "vector[] index out of bounds";
			};

			reference at (size_type n) {
				if (n >= size())
					return this->__begin_[n];
				return *end();
				// this->__throw_out_of_range();
			};

			const_reference at (size_type n) const {
				if (n >= size())
					return this->__begin_[n];
				return *end();
				// this->__throw_out_of_range();
			};

			reference front() {
				if (!empty())
        			return *begin();
				return *end();
				// ERR: "front() called for empty vector"
			};

			const_reference front() const {
				if (!empty())
        			return *begin();
				return *end();
				// ERR: "front() called for empty vector"
			};

			reference back() {
				if (!empty())
        			return *(end() - 1);
				return *end();
				// ERR: "back() called for empty vector"
			};

			const_reference back() const {
				if (!empty())
        			return *(end() - 1);
				return *end();
				// ERR: "back() called for empty vector"
			};

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				clear();
				*this = vector<T, Allocator>(first, last);
			};
			void assign (size_type n, const value_type& val) {
				clear();
				*this = vector<T, Allocator>(n, val);
			};

			void push_back (const value_type& val) { (void)val; /* TODO */ };

			void pop_back() {}; //TODO

			iterator insert (iterator position, const value_type& val); //TODO
			void insert (iterator position, size_type n, const value_type& val); //TODO
			
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last); //TODO

			iterator erase (iterator position) { return position; }; //TODO
			iterator erase (iterator first, iterator last) { (void)first; return last; }; //TODO

			void swap (vector& x) { (void)x; }; //TODO

			void clear() { erase(begin(), end()); }; //TODO

			/* ------------------------------------------------------------- */
			/* ------------------------- ALLOCATOR ------------------------- */

			allocator_type get_allocator() const { return __base::__alloc(); };

	}; // class vector

	/* ------------------------------------------------------------- */
	/* ---------------- NON-MEMBER FUNCTION OVERLOAD --------------- */

	/* 		Relational operaors: */

	template <class T, class Allocator>
	bool operator== (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	template <class T, class Allocator>
	bool operator!= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	template <class T, class Allocator>
	bool operator<  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	template <class T, class Allocator>
	bool operator<= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	template <class T, class Allocator>
	bool operator>  (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	template <class T, class Allocator>
	bool operator>= (const vector<T,Allocator>& lhs, const vector<T,Allocator>& rhs); //TODO

	/* 		Swap: */

	template <class T, class Allocator>
	void swap (vector<T,Allocator>& x, vector<T,Allocator>& y);

} // namespace ft

#endif