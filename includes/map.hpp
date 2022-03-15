#ifndef MAP_HPP
# define MAP_HPP

# pragma once
# include <iostream>
# include "iterator.hpp"
# include "algorithm.hpp"
// # include "type_traits.hpp"
# include "utility.hpp"
# include "red_black_tree.hpp"


namespace ft
{
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
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef typename allocator_type::pointer		pointer;
			typedef typename allocator_type::const_pointer	const_pointer;
			
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
		
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef ft::bidirectional_iterator<value_type, Node<value_type, value_compare> >		iterator;
			typedef ft::bidirectional_iterator<const value_type, Node<value_type, value_compare> >	const_iterator;
			typedef ft::reverse_iterator<iterator>													reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>											const_reverse_iterator;

		/* ------------------------------------------------------------- */
		/* ------------------------- ATTRIBUTES ------------------------ */

		private:

			typedef typename Allocator::template rebind< Node<value_type, value_compare> >::other real_allocator_type;

		protected:

			RedBlackTree<value_type, value_compare, real_allocator_type>	_tree;
			//allocator_type											_alloc;
			real_allocator_type										_alloc;
			Compare													_comp;

		/* ------------------------------------------------------------- */
		/* ---------------- CONSTRUCTORS & DESTRUCTOR ------------------ */
		
		private:

			iterator tail() { return iterator(_tree.max()); };
			const_iterator tail() const { return const_iterator(_tree.max()); };


		public:

			/**
			 *	Empty container constructor (default constructor)
			 *	Constructs an empty container, with no elements.
			 */
			explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator() ) 
				: _tree(value_compare(comp)), _alloc(alloc), _comp(comp) { /* std::cout << "def construct" << std::endl; */ }
			
			/**
			 *	Range constructor
			 *	Constructs the container with the contents of the range [ @param first, @param last ), 
			 *	If multiple elements in the range have keys that compare equivalent, it is unspecified which element is inserted
			 */
			template< class InputIt >
			map( InputIt first, InputIt last,
					const Compare& comp = Compare(),
					const Allocator& alloc = Allocator() ) : _tree(value_compare(comp)), _alloc(alloc), _comp(comp) { 
				insert(first, last);
			};

			/**
			 * 	Copy constructor
			 * Constructs the container with the copy of the contents of other.
			 */
			//map( const map & other ) : _tree(value_compare(key_compare())), _alloc(other._alloc) { /*std::cout << "copy construct" << std::endl; */insert(other.begin(), other.end()); };
			//map( const map & other ) : _tree(other.value_comp()), _alloc(other._alloc) { insert(other.begin(), other.end()); };
			map( const map & other ) : _tree(value_compare(other._comp)), _alloc(other._alloc), _comp(other._comp) {
			 	//*this = map(other.begin(), other.end(), other._comp, other._alloc);
				// std::cout << "copy construct" << std::endl;
				// std::cout << "size: " << size() << std::endl;
				// std::cout << "other size: " << other.size() << std::endl;
				// std::cout << "begin: " << (*other.begin()).first << std::endl;
				// std::cout << "tail: " << (*other.tail()).first << std::endl;
				if (other.size() > 10000)
					_tree = other._tree;
				else
					insert(other.begin(), other.end());
				// int i = 0;
				// for (const_iterator it = other.begin(); it != other.end(); it++) {
				// 	std::cout << "[" << i << "]: " << (*it).first << " | " << (*it).second << std::endl;
				// 	insert(*it);
				// 	i++;
				// }
			};

			/**
			 * 	Destructor
			 */
			~map() { clear(); };
			
			/**
			 * Copy assignment operator.
			 * Replaces the contents with a copy of the contents of other.
			 */
			map& operator= (const map & other) {
				//std::cout << "operator =" << std::endl;
				if ( this != &other ) {
					clear();
					//std::cout << "clear OK" << std::endl;
					insert(other.begin(), other.end());
					//std::cout << "insert OK" << std::endl;
				}
				return *this; };

			/**
			 * Returns the allocator associated with the container.
			 */
			allocator_type get_allocator() const { return _alloc; };

			/* ------------------------------------------------------------- */
			/* ----------------------- ELEMENT ACCESS ---------------------- */

			mapped_type & operator[] ( const key_type& k ) {
					// _tree.insert(ft::make_pair(k, mapped_type()));
					// return (*find(k)).second;
					return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; };

			/* ------------------------------------------------------------- */
			/* ------------------------- ITERATORS ------------------------- */

			iterator begin() { return iterator(_tree.min()); };
			const_iterator begin() const { return const_iterator(_tree.min()); };

			iterator end() { return iterator(_tree.end()); };
			const_iterator end() const { return const_iterator(_tree.end()); };

			reverse_iterator rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };

			reverse_iterator rend() { return reverse_iterator(begin()); };
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };

			/* ------------------------------------------------------------- */
			/* ------------------------- CAPACITY -------------------------- */

			bool empty (void) const { return !_tree.size() ? true : false; }

			size_type size (void) const { return _tree.size(); }

			size_type max_size(void) const { return _tree.max_size(); };

			/* ------------------------------------------------------------- */
			/* ------------------------- MODIFIERS ------------------------- */

			ft::pair<iterator, bool>	insert( const value_type & val ) {

				//size_type old_size = size();
				ft::pair<Node<value_type, value_compare> *, bool> ret = _tree.insert(val);
				return ft::make_pair(iterator(ret.first), ret.second);
			}

			iterator	insert( iterator position, const value_type &val ) {

				( void )position;
				return insert(val).first;
			}

			template <class InputIterator>
			void	insert( InputIterator first, InputIterator last ) {
				while (first != last) {
					//std::cout << "insert " << (*first).first << std::endl;
					insert(*first++);
					//++first;
				}
				//std::cout << "insert OK" << std::endl;
			}

			void	erase( iterator position ) { _tree.remove(*position); }

			size_type erase ( const key_type & k ) {
				//size_type old_size = size();
				iterator to_remove = find(k);
				return _tree.remove(*to_remove);
				//erase(to_remove);
				//return old_size - size();
			};

			void	erase( iterator first, iterator last ) {
				while (first != last) {
					//first = find(first->first);
					erase(first++);
				}
			}

			void	swap( map &x ) { _tree.swap(x._tree); }

			void	clear( void ) { _tree.clear(); }

			/* ------------------------------------------------------------- */
			/* ------------------------- OBSERVERS ------------------------- */

			key_compare	key_comp( void ) const { return key_compare(); }

			value_compare	value_comp( void ) const { return value_compare(key_comp()); }

			/* ------------------------------------------------------------- */
			/* ------------------------ OPERATIONS ------------------------- */

			iterator	find( const key_type & k )
				{ return iterator(_tree.search(ft::make_pair(k, mapped_type()))); }

			const_iterator	find( const key_type & k ) const 
				{ return const_iterator(_tree.search(ft::make_pair(k, mapped_type()))); }

			size_type	count( const key_type &k ) const {
				if ( find(k) == end() )
					return 0;
				return 1;
			}

			iterator lower_bound( const key_type &k )
			{
				iterator it;

				for ( it = begin(); it != end(); ++it )
					if ( !value_comp()(*it, ft::make_pair(k, mapped_type())))
						break;
				return it;
			}

			const_iterator lower_bound( const key_type &k ) const
			{
				const_iterator it;

				for ( it = begin(); it != end(); ++it ) {
					if ( !value_comp()(*it, ft::make_pair(k, mapped_type())) )
						break;
				}
				return it;
			}

			iterator upper_bound( const key_type &k )
			{
				iterator it;

				for ( it = begin(); it != end(); ++it ) {
					if ( value_comp()(ft::make_pair(k, mapped_type()), *it))
						break;
				}
				return it;
			}

			const_iterator upper_bound( const key_type &k ) const
			{
				const_iterator it;

				for ( it = begin(); it != end(); ++it ) {
					if ( value_comp()(ft::make_pair(k, mapped_type()), *it))
						break;
				}
				return it;
			}

			ft::pair<const_iterator, const_iterator>	equal_range( const key_type &k ) const {
				return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
			}

			ft::pair<iterator, iterator>				equal_range( const key_type &k ) {
				return ft::make_pair(this->lower_bound(k), this->upper_bound(k));
			}

			// OTHER (debug)
			void print( void ) { std::cout << _tree << std::endl; }

	}; // class map

	/* ------------------------------------------------------------- */
	/* ---------------- NON-MEMBER FUNCTION OVERLOAD --------------- */

	/* 		Relational operators: */

	template <typename T1, typename T2>
	bool operator== (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <typename T1, typename T2>
	bool operator!= (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (!(lhs == rhs));
	};

	template <typename T1, typename T2>
	bool operator<  (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <typename T1, typename T2>
	bool operator<= (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (!(rhs < lhs));
	};

	template <typename T1, typename T2>
	bool operator>  (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (rhs < lhs);
	};

	template <typename T1, typename T2>
	bool operator>= (const map<T1, T2>& lhs, const map<T1, T2>& rhs) {
		return (!(lhs < rhs));
	};

	/* 		Swap: */

	template <typename T1, typename T2>
	void swap (const map<T1, T2>& x, const map<T1, T2>& y) {
		std::swap(x, y);
		//return x.swap(y);
	};

} // namespace ft

#endif /* MAP_HPP */