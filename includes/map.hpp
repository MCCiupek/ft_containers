#pragma once
#include <iostream>
// #include "iterator.hpp"

namespace ft
{
	/**
	* ------------------------------------------------------------- *
	* ------------------------ FT::MAP ------------------------- *
	* ------------------------------------------------------------- *
	*/

	template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >
	>
	class map {

		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */

		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef std::pair<const Key, T>					value_type;
			typedef size_t									size_type;
			typedef ptrdiff_t								difference_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			// typedef map_iterator<key_type, value_type, mapped_type>;		iterator;
			// typedef map_const_iterator<key_type, value_type, mapped_type>;	const_iterator;
			// typedef std::reverse_iterator<iterator>;						reverse_iterator;
			// typedef std::reverse_iterator<const_iterator>;					const_reverse_iterator;

		/* ------------------------------------------------------------- */
		/* ---------------- CONSTRUCTORS & DESTRUCTOR ------------------ */
		
		public:

			/**
			 *	Empty container constructor (default constructor)
			 *	Constructs an empty container, with no elements.
			 */
			explicit map( const Compare& comp,
							const Allocator& alloc = Allocator() );
			
			/**
			 *	Range constructor
			 *	Constructs the container with the contents of the range [ @param first, @param last ), 
			 *	If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted
			 */
			template< class InputIt >
			map( InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator() );

			/**
			 * 	Copy constructor
			 * Constructs the container with the copy of the contents of other.
			 */
			map( const map& other );

			/**
			 * 	Destructor
			 */
			~map();
			
			/**
			 * Copy assignment operator.
			 * Replaces the contents with a copy of the contents of other.
			 */
			map& operator= (const map&);

			/**
			 * Returns the allocator associated with the container.
			 */
			allocator_type get_allocator() const;
	};
}