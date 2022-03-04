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

		Node( T key ) : 
			key(key), _up(NULL), down(NULL, NULL), color(RED) {}

		Node( T key, Node & other ) : 
			key(key), _up(&other), down(NULL, NULL), color(RED) {}
		
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
		void			setKey( value_type _key ) { key = _key; };

		int				getColor() const { return color; };
		void			setColor( int _color ) { color = _color; };

		pointer&		up() { return _up; };
		const pointer&	up() const { return _up; };

		pointer&		left() { return down.first; };
		const pointer&	left() const { return down.first; };

		pointer&		right() { return down.second; };
		const pointer&	right() const { return down.second; };

		pointer		uncle() { 
			if ( !_up || !up()->up() )
				return NULL;
			if ( up()->up()->right() == up() )
				return  up()->up()->left();
			return up()->up()->right();
		};
		const pointer	uncle() const { 
			if ( !_up || !up()->up() )
				return NULL;
			if ( up()->up()->right() == up() )
				return  up()->up()->left();
			return up()->up()->right();
		};

		void			swap( Node * other ) {
			value_type new_key = other->getKey();
			(void)new_key;
			//other->setKey(key);
			//this->setKey(new_key);
			//this->key = new_key;
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

		typedef T							value_type;
		typedef	Node<value_type, Compare> 	Node;
		typedef Compare						value_compare;
		typedef Allocator					allocator_type;

	protected:

		Node *						root;
		value_compare				_cmp;

	public:

		BinarySearchTree( value_compare const & cmp = value_compare() ) : root(NULL), _cmp(cmp) {};
		//BinarySearchTree( value_type key, value_compare const & cmp = value_compare() ) : root(&Node(key)), _cmp(cmp) {};
		//BinarySearchTree( Node * node ) : root(node) {};
		BinarySearchTree( const BinarySearchTree & other ) : root(other.root), _cmp(other._cmp) {};
		BinarySearchTree& operator=( const BinarySearchTree & other ) {
			if ( this != &other ) {
				root = other.root;
				_cmp = other._cmp;
			}
			return *this;
		};
		virtual ~BinarySearchTree() { rdelete(root); };

	private:

		Node * rinsert( Node * node, value_type key, Node * prev=NULL ) { 
			if ( !node )
				return new Node(key, *prev);
			if ( key < node->getKey() )
			 	node->left() = rinsert(node->left(), key, node);
			else if ( key > node->getKey() )
			 	node->right() = rinsert(node->right(), key, node);
			return node;
		}

		Node * rremove( Node * node, value_type key ) { 
			if ( !node )
				return NULL;
			if ( key < node->getKey() )
			 	node->left() = rremove(node->left(), key);
			else if ( key > node->getKey() )
			 	node->right() = rremove(node->right(), key);
			else {
				if ( node->left() && node->right() ) {
					Node * _tmp = node->right();
					while ( _tmp->left() )
						_tmp = _tmp->left();
					node->swap(_tmp);
					node->right() = rremove(node->right(), key);
				}
				else if ( !node->left() && !node->right() ) {
					delete node;
					return NULL;
				}
				else if ( node->left() && !node->right() ) {
					node = rremove(node->left(), key);
				}
				else if ( !node->left() && node->right() ) {
					node = rremove(node->right(), key);
				}
			}
			return node;
		}

		size_t rsize( Node * node ) const {
			if ( !node )
				return 0;
			return 1 + rsize(node->left()) + rsize(node->right());
		}

		void rprint_keys( Node * node ) const {
			if (node != NULL) {
				std::cout << "x" << " ";
				//std::cout << node->getKey() << " ";
				rprint_keys(node->left());
				rprint_keys(node->right());
			}
		}

		void rdelete( Node * node ) {
			if (node != NULL) {
				remove(node->getKey());
				rdelete(node->left());
				rdelete(node->right());
			}
		}

		Node * rmin( Node * node ) const {
			if ( !node->left() )
				return node;
			return rmin(node->left());
		}

		Node * rmax( Node * node ) const {
			if ( !node->right() )
				return node;
			return rmax(node->right());
		}

		Node * rsearch( Node * node, value_type key ) {
			if (node == NULL)
				return node;//throw std::out_of_range("KeyError");
			if (node->getKey() == key)
				return node;
			if (node->getKey() < key)
				return rsearch(node->right(), key);
			return rsearch(node->left(), key);
		}

		void rprint_tree( const Node* node, bool isLeft=false, const std::string& prefix="" ) const
		{
			if ( node ) {
				std::cout << prefix + (isLeft ? "├──" : "└──" );
				//std::cout << (node->getColor() == RED ? CRED : CBLACK) << node->getKey() << CRESET << std::endl;
				std::cout << (node->getColor() == RED ? CRED : CBLACK) << "x" << CRESET << std::endl;

				rprint_tree(node->left(), true, prefix + (isLeft ? "│   " : "    "));
				rprint_tree(node->right(), false, prefix + (isLeft ? "│   " : "    "));
			}
		}

	public:

		void	insert( value_type key ) { root = rinsert(root, key); }
		void	remove( value_type key ) { root = rremove(root, key); }
		Node *	search( value_type key ) { return rsearch(root, key); }
		void	print_keys( void ) const { rprint_keys(root); }
		void	print_tree( void ) const { rprint_tree(root); }
		Node *	min( void ) const { return rmin(root); }
		Node *	max( void ) const { return rmax(root); }
		size_t	size( void ) const { return rsize(root); }
		void	clear( void ) { rdelete(root); }
		

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
				this->root = other.root;
			return *this;
		};
		~RedBlackTree() {};

	private:

		void lrotate( Node * x ) {
			Node * y = x->right();

			x->right() = y->left();
			if ( y->left() )
				y->left()->up() = x;
			y->up() = x->up();
			if ( !x->up() )
				this->root = y;
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
			if ( y->right() )
				y->right()->up() = x;
			y->up() = x->up();
			if ( !x->up() )
				this->root = y;
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

			if ( g && g->left() && node == g->left()->right() ) {
				lrotate(p);
				node = node->left();
			} else if ( g && g->right() && node == g->right()->left() ) {
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
			while ( this->root->up() )
			{
				this->root = this->root->up();
			}
			
		}

		void	remove( value_type key ) {
			BinarySearchTree::remove(key);
			insert_repair_tree(this->root);
		}

}; /* class RedBlackTree */


#endif /* RED_BLACK_TREE_HPP */