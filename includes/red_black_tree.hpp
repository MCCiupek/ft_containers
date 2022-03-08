#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# pragma once
# include <iostream>
# include <iomanip>
# include "utility.hpp"
# include "type_traits.hpp"

# define BLACK	0
# define RED	1
# define CRESET       "\033[0m"
# define CBLACK       "\033[30m"             /* Black */
# define CRED         "\033[31m"             /* Red */

# define ARROWS "   /\\   "

template< class T, class Compare = std::less<T> >
class Node {

	private:

		typedef T					value_type;
		typedef	Node<T, Compare> *	pointer;

		T							key;
		pointer						_up;
		ft::pair<pointer, pointer>	down;
		int							color;

	public: 

		Node( void ) :
			key(T()), _up(NULL), down(NULL, NULL), color(RED) {}

		Node( const T & _key ) : 
		 	key(_key), _up(NULL), down(NULL, NULL), color(RED) {}

		Node( const T & _key, Node & parent ) : 
			key(_key), _up(&parent), down(NULL, NULL), color(RED) {}
		
		Node( const Node & other ) : 
			key(other.key), _up(other._up), down(other.down), color(other.color) {}

		Node& operator=( const Node & other ) {
			if ( this != &other ) {
				key = other.key;
				_up = other._up;
				down = other.down;
				color = other.color;
			}
			return *this;
		};
		
		~Node() {}

		T&				getKey() { return key; };
		T const &		getKey() const { return key; };
		void			setKey( value_type & _key ) { key = _key; };

		int				getColor() const { return color; };
		void			setColor( int _color ) { color = _color; };

		pointer&		up() { return _up; };
		const pointer&	up() const { return _up; };

		pointer&		left() { return down.first; };
		const pointer&	left() const { return down.first; };

		pointer&		right() { return down.second; };
		const pointer&	right() const { return down.second; };

		pointer		uncle() { 
			if ( !up() || !up()->up() )
				return NULL;
			if ( up()->up()->right() == up() )
				return  up()->up()->left();
			return up()->up()->right();
		};
		const pointer	uncle() const { 
			if ( !up() || !up()->up() )
				return NULL;
			if ( up()->up()->right() == up() )
				return  up()->up()->left();
			return up()->up()->right();
		};

		void			swap( pointer & other ) {

			pointer tmp_up = other->up();
			pointer tmp_right = other->right();
			pointer tmp_left = other->left();

			other->up() = up();
			other->right() = right();
			other->left() = left();

			up() = tmp_up;
			right() = tmp_right;
			left() = tmp_left;
		}

}; /* class Node */

template <class T, class Compare>
std::ostream & operator<<( std::ostream &os, const Node<T, Compare> & node ) { 
	os << std::setw(4) << node.getKey() << std::setw(4) << " " << std::endl;
	os << ARROWS << std::endl;
	return os;
}

template <class T, class Compare>
bool operator<(const T & x, const T & y) { return Compare(x, y); }

template <class T, class Compare>
bool operator>(const T & x, const T & y) { return Compare(y, x); }


template< class T, class Compare = std::less<T>, class Allocator = std::allocator<Node<T, Compare> > >
class BinarySearchTree {

	public:	

		typedef T									value_type;
		typedef	Node<value_type, Compare> 			Node;
		typedef Compare								value_compare;
		typedef Allocator							allocator_type;
		typedef typename allocator_type::size_type	size_type;
		typedef typename allocator_type::pointer	pointer;

	protected:

		Node *						_root;
		value_compare				_cmp;
		Node *						_null;
		allocator_type				_alloc;

	public:

		BinarySearchTree( value_compare const & cmp = value_compare() ) : _root(NULL), _cmp(cmp) {
			_null = _alloc.allocate(1);
			std::cout << "allocate" << " ";
			std::cout << "construct" << std::endl;
			_alloc.construct(_null, Node());
			_root = _null;
		};
		BinarySearchTree( const BinarySearchTree & other ) : _root(other._root), _cmp(other._cmp) {};
		BinarySearchTree& operator=( const BinarySearchTree & other ) {
			if ( this != &other ) {
				_root = other._root;
				_cmp = other._cmp;
			}
			return *this;
		};
		virtual ~BinarySearchTree() { clear(); };

	private:

		Node * rinsert( Node * node, value_type key, Node * prev=NULL ) { 
			if ( !node || node == _null ) {					
				Node * new_node = allocator_type().allocate(1);
				std::cout << "allocate" <<  " ";
				std::cout << "construct" << std::endl;
				if ( !prev )
					allocator_type().construct(new_node, Node(key));
				else
					allocator_type().construct(new_node, Node(key, *prev));
				new_node->right() = _null;
				new_node->left() = _null;
				_null->up() = new_node;
				return new_node;
			}
			if ( key < node->getKey() )
			 	node->left() = rinsert(node->left(), key, node);
			else if ( key > node->getKey() )
			 	node->right() = rinsert(node->right(), key, node);
			return node;
		}

		Node * rremove( Node * node, value_type key ) { 
			if ( !node || node == _null )
				return _null;
			if ( key < node->getKey() )
			 	node->left() = rremove(node->left(), key);
			else if ( key > node->getKey() )
			 	node->right() = rremove(node->right(), key);
			else {
				if ( node->left() != _null && node->right() != _null ) {
					Node * _tmp = node->right();
					while ( _tmp->left() != _null )
						_tmp = _tmp->left();
					node->swap(_tmp);
					node->right() = rremove(node->right(), key);
				}
				else if ( node->left() == _null && node->right() == _null ) {
					std::cout << "destroy " << std::endl;
					allocator_type().destroy(node->left());
					allocator_type().deallocate(node->left(), 1);
					std::cout << *this << std::endl;
					std::cout << "destroy" << std::endl;
					allocator_type().destroy(node->right());
					allocator_type().deallocate(node->right(), 1);
					// std::cout << *this << std::endl;
					// std::cout << "destroy deallocate node " << node->getKey().first << " ";
					// allocator_type().destroy(node);
					// allocator_type().deallocate(node, 1);
					node = _null;
					std::cout << *this << std::endl;
					//return _null;
				}
				else if ( node->left() != _null && node->right() == _null ) {
					node = rremove(node->left(), key);
				}
				else if ( node->left() == _null && node->right() != _null ) {
					node = rremove(node->right(), key);
				}
			}
			return node;
		}

		size_type rsize( Node * node ) const {
			if ( !node || node == _null )
				return 0;
			return 1 + rsize(node->left()) + rsize(node->right());
		}

		void rprint_keys( Node * node ) const {
			if ( node != _null ) {
				std::cout << node->getKey().first << " ";
				//std::cout << node->getKey() << " ";
				rprint_keys(node->left());
				rprint_keys(node->right());
			}
		}

		void rdelete( Node * node ) {
			if ( node != _null ) {
				remove(node->getKey());
				rdelete(node->left());
				rdelete(node->right());
			}
		}

		Node * rmin( Node * node ) const {
			if ( node->left() == _null )
				return node;
			return rmin(node->left());
		}

		Node * rmax( Node * node ) const {
			if ( node->right() == _null )
				return node;
			return rmax(node->right());
		}

		Node * rsearch( Node * node, value_type key ) {
			if ( node == _null )
				return node;
			if ( node->getKey() == key )
				return node;
			if ( node->getKey() < key )
				return rsearch(node->right(), key);
			return rsearch(node->left(), key);
		}

		void rprint_tree( const Node* node, bool isLeft=false, const std::string& prefix="" ) const
		{
			if ( node != NULL ) {
				
				std::cout << prefix + (isLeft ? "├──" : "└──" );
				//std::cout << (node->getColor() == RED ? CRED : CBLACK) << node->getKey() << CRESET << std::endl;
				if ( node  == _null )
					std::cout << (node->getColor() == RED ? CRED : CBLACK) << "NULL" << CRESET << std::endl;
				else
					std::cout << (node->getColor() == RED ? CRED : CBLACK) << node->getKey().first << CRESET << std::endl;
				rprint_tree(node->left(), true, prefix + (isLeft ? "│   " : "    "));
				rprint_tree(node->right(), false, prefix + (isLeft ? "│   " : "    "));
			}
		}

	public:

		void	insert( value_type key ) { _root = rinsert(_root, key); }
		void	remove( value_type key ) { _root = rremove(_root, key); }
		Node *	search( value_type key ) { return rsearch(_root, key); }
		void	print_keys( void ) const { rprint_keys(_root); }
		void	print_tree( void ) const { rprint_tree(_root); }
		Node *	min( void ) const { return rmin(_root); }
		Node *	max( void ) const { return rmax(_root); }
		Node *	root( void ) const { return _root; }
		Node *	end( void ) const { return _null; }
		size_type	size( void ) const { return rsize(_root); }
		size_type	max_size( void ) const { return _alloc.max_size(); }
		void	clear( void ) { rdelete(_root); _root->setColor(RED); }
		

}; /* class BinarySearchTree */

template< class T, class Compare >
std::ostream & operator<<( std::ostream &os, const BinarySearchTree<T, Compare> & tree ) { 
	
	os << "=========" << std::endl;
	os << "keys: ---" << std::endl;
	tree.print_keys();
	os << std::endl;
	os << "---------" << std::endl;

	os << "tree: ---" << std::endl;
	tree.print_tree();
	os << "---------" << std::endl;
	os << "=========";
	return os;            
}

template< class T, class Compare = std::less<T>, class Alloc = std::allocator<Node<T> >  >
class RedBlackTree : public BinarySearchTree<T, Compare> {

	public:

		typedef BinarySearchTree<T,Compare>				BinarySearchTree;
		typedef typename BinarySearchTree::value_type	value_type;
		typedef	typename BinarySearchTree::Node			Node;
		typedef Compare									value_compare;

	public:

		RedBlackTree( value_compare const & cmp = value_compare() ) : BinarySearchTree( cmp ) {};
		//RedBlackTree( value_type key ) : BinarySearchTree(key) {};
		//RedBlackTree( Node * node ) : BinarySearchTree(node) {};
		RedBlackTree( const BinarySearchTree & other ) : BinarySearchTree(other) {};
		RedBlackTree& operator=( const RedBlackTree & other ) {
			if ( this != &other )
				this->_root = other._root;
			return *this;
		};
		~RedBlackTree() {};

	private:

		void lrotate( Node * x ) {
			Node * y = x->right();

			x->right() = y->left();
			y->left()->up() = x;
			y->up() = x->up();
			if ( !x->up() )
				this->_root = y;
			else if ( x == x->up()->left() )
				x->up()->left() = y;
			else
				x->up()->right() = y;
			y->left() = x;
			x->up() = y;
		}

		void rrotate( Node * x ) {
			Node * y = x->left();

			x->left() = y->right();
			y->right()->up() = x;
			y->up() = x->up();
			if ( !x->up() )
				this->_root = y;
			else if ( x == x->up()->right() )
				x->up()->right() = y;
			else
				x->up()->left() = y;
			y->right() = x;
			x->up() = y;
		}

		void recolor( Node * x ) {
			if ( x->getColor() == RED )
				x->setColor(BLACK);
			else
				x->setColor(RED);
		}

		void insert_case1( Node * node ) {
			if ( !node->up() )
				node->setColor(BLACK);
		}

		void insert_case2( Node * node ) {
			(void)node;
			return;
		}

		void insert_case3( Node * node ) {
			if ( node->up() && node->up()->up() ) {
				node->up()->setColor(BLACK);
				node->uncle()->setColor(BLACK);
				node->up()->up()->setColor(RED);
				insert_repair_tree(node->up()->up());
			} else {
				insert_repair_tree(NULL);
			}
		}

		void insert_case4step2( Node *node ) {
			
			Node * p = node->up();
			Node * g = node->up() ? node->up()->up() : NULL;

			if ( p && node == p->left() )
				rrotate(g);
			else
				lrotate(g);
			if ( p )
				p->setColor(BLACK);
			if ( g )
				g->setColor(RED);
		}


		void insert_case4( Node *node ) {

			Node * p = node->up();
			Node * g = node->up() ? node->up()->up() : NULL;

			if ( g && g->left() != this->_null && node == g->left()->right() ) {
				lrotate(p);
				node = node->left();
			} else if ( g && g->right() != this->_null && node == g->right()->left() ) {
				rrotate(p);
				node = node->right();
			}
			insert_case4step2(node);
		}

		void insert_repair_tree( Node *node ) {
			if ( !node->up() )
				insert_case1(node);
			else if ( node->up() && node->up()->getColor() == BLACK )
				insert_case2(node);
			else if ( node->uncle() && node->uncle()->getColor() == RED)
				insert_case3(node);
			else
				insert_case4(node);
		}

	public:

		void	insert( value_type key ) {
			Node * _new;

			BinarySearchTree::insert(key);
			_new = this->search(key);
			insert_repair_tree(_new);
			while ( this->_root->up() )
			{
				this->_root = this->_root->up();
			}
			
		}

		void	remove( value_type key ) {
			BinarySearchTree::remove(key);
			insert_repair_tree(this->_root);
		}

}; /* class RedBlackTree */


#endif /* RED_BLACK_TREE_HPP */