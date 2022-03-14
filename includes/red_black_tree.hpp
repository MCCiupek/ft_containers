#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# pragma once
# include <iostream>
# include <sstream>
# include <iomanip>
# include "utility.hpp"
# include "type_traits.hpp"

# define BLACK	0
# define RED	1
# define CRESET       "\033[0m"
# define CBLACK       "\033[30m"             /* Black */
# define CRED         "\033[31m"             /* Red */


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

		T &				getKey() { return key; };
		const T &		getKey() const { return key; };
		
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

		void			swap( pointer & other, pointer & _null ) {

			pointer	tmp = other;
			pointer tmp_up = other->up();
			pointer tmp_right = other->right();
			pointer tmp_left = other->left();

			// std::cout << "--- BF SWAP ---" << std::endl;
			// std::cout << "*this : " << std::endl;
			// std::cout << n(this, _null) << std::endl;
			// std::cout << "other : " << std::endl;
			// std::cout << n(other, _null) << std::endl;

			if ( other->right() && other->right() != _null && other->right() != this )
				other->right()->up() = this;
				
			if ( other->left() && other->left() != _null && other->left() != this )
				other->left()->up() = this;
			
			if ( other->up() && other->up() != this ) {
				if ( other->up()->right() == other )
					other->up()->right() = this;
				if ( other->up()->left() == other )
					other->up()->left() = this;
			}

			if ( this->right() && this->right() != tmp )
				this->right()->up() = tmp;
			
			if ( this->left() && this->left() != tmp )
				this->left()->up() = tmp;
			
			if ( this->up() && this->up() != tmp ) {
				if ( this->up()->right() == this )
					this->up()->right() = tmp;
				if ( this->up()->left() == this )
					this->up()->left() = tmp;
			}

			if ( up() != other )
				other->up() = up();
			else
				other->up() = this;
			if ( right() != other )
				other->right() = right();
			else
				other->right() = this;
			if ( left() != other )
				other->left() = left();
			else
				other->left() = this;

			if ( tmp_up != this )
				up() = tmp_up;
			else
				up() = other;
			if ( tmp_right != this )
				right() = tmp_right;
			else
				right() = other;
			if ( tmp_left != this )
				left() = tmp_left;
			else
				left() = other;
			
			// std::cout << "--- AF SWAP ---" << std::endl;
			// std::cout << "*this : " << std::endl;
			// std::cout << n(this, _null) << std::endl;
			// std::cout << "other : " << std::endl;
			// std::cout << n(other, _null) << std::endl;
		}

}; /* class Node */

template <class T, class Compare>
std::string p( Node<T, Compare> * node, Node<T, Compare> * _null  ) {
	std::stringstream os;

	if ( !node )
		os << "NULL";
	else if ( node == _null )
		os << "_null";
	else
		os << node->getKey().first;
	return os.str();
}

template <class T, class Compare>
std::string n( Node<T, Compare> * node, Node<T, Compare> * _null  ) {
	std::stringstream os;

	if (!node)
		return "  - [NULL NODE]\n";
	os << "  -key : " <<  p(node, _null) << std::endl;
	os << "  -up : " << p(node->up(), _null) << std::endl;
	os << "  -left : " << p(node->left(), _null) << std::endl;
	os << "  -right : " << p(node->right(), _null) << std::endl;
	if (node->left())
		os << "  -left->up() : " << p(node->left()->up(), _null) << std::endl;
	if (node->right())
		os << "  -right->up() : " << p(node->right()->up(), _null) << std::endl;
	if (node->up())
		os << "  -up->left : " << p(node->up()->left(), _null) << std::endl;
	if (node->up())
		os << "  -up->right : " << p(node->up()->right(), _null) << std::endl;
	return os.str();
}

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
		ft::pair<Node *, bool>		_insert_return;
		bool						_remove_return;

	public:

		BinarySearchTree( value_compare const & cmp = value_compare(), const Allocator& alloc = Allocator() ) : _root(NULL), _cmp(cmp), _alloc(alloc) {
			//std::cout << "new BST" << std::endl;
			_null = _alloc.allocate(1);
			_alloc.construct(_null, Node());
			_root = _null;
		};
		BinarySearchTree( const BinarySearchTree & other ) : _root(other._root), _cmp(other._cmp), _null(other._null), _alloc(other._alloc) {};
		BinarySearchTree& operator=( const BinarySearchTree & other ) {
			if ( this != &other ) {
				_root = other._root;
				_cmp = other._cmp;
				_alloc = other._alloc;
				_null = other._null;
			}
			return *this;
		};
		virtual ~BinarySearchTree() { 
			clear();
			_alloc.destroy(_root);
			_alloc.deallocate(_root, 1);
		};

	private:

		Node * rinsert( Node * node, value_type key, Node * prev=NULL ) { 
			if ( !node || node == _null ) {
				//std::cout << "construct & allocate " << key.first << std::endl;
				Node * new_node = _alloc.allocate(1);
				if ( !prev )
					_alloc.construct(new_node, Node(key));
				else
					_alloc.construct(new_node, Node(key, *prev));
				new_node->right() = _null;
				new_node->left() = _null;
				_null->up() = new_node;
				_insert_return = ft::make_pair(new_node, true);
				return new_node;
			}
			if ( _cmp(key, node->getKey()) )
			 	node->left() = rinsert(node->left(), key, node);
			else if ( _cmp(node->getKey(), key) )
			 	node->right() = rinsert(node->right(), key, node);
			else
				_insert_return = ft::make_pair(node, false);
			return node;
		}

		Node * rremove( Node * node, value_type key, Node * prev=NULL ) { 
			if ( node == _null ) {
				return _null;
			}
			if ( _cmp(key, node->getKey()) )
			 	node->left() = rremove(node->left(), key, node);
			else if ( _cmp(node->getKey(), key) )
			 	node->right() = rremove(node->right(), key, node);
			else {
				if ( node->left() == _null && node->right() == _null ) {
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					_remove_return = true;
					return _null;
				}
				else if ( node->left() != _null && node->right() == _null ) {
					Node * tmp = node->left();
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					_remove_return = true;
					if ( prev )
						tmp->up() = prev;
					return tmp;
				}
				else if ( node->left() == _null && node->right() != _null ) {
					Node * tmp = node->right();
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
					_remove_return = true;
					if ( prev )
						tmp->up() = prev;
					return tmp;
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
			if ( node && node != _null ) {
				std::cout << node->getKey().first << " ";
				rprint_keys(node->left());
				rprint_keys(node->right());
			}
		}

		void rdelete( Node * node ) {
			if ( node != _null ) {
				rdelete(node->left());
				rdelete(node->right());
				remove(node->getKey());
			}
		}

		Node * rmin( Node * node ) const {
			if ( !node->left() || node->left() == _null )
				return node;
			return rmin(node->left());
		}

		Node * rmax( Node * node ) const {
			if ( !node->right() || node->right() == _null )
				return node;
			return rmax(node->right());
		}

		Node * rsearch( Node * node, value_type key ) const {
			if ( node == _null )
				return node;
			if ( _cmp(node->getKey(), key) )
				return rsearch(node->right(), key);
			if ( _cmp(key, node->getKey()) )
				return rsearch(node->left(), key);
			return node;
		}

		void rprint_tree( const Node* node, bool isLeft=false, const std::string& prefix="" ) const
		{
			if ( node ) {
				
				std::cout << prefix + (isLeft ? "├──" : "└──" );
				if ( node  == _null )
					std::cout << (node->getColor() == RED ? CRED : CRESET) << "NULL" << CRESET << std::endl;
				else
					std::cout << (node->getColor() == RED ? CRED : CRESET) << node->getKey().first << CRESET << std::endl;
				rprint_tree(node->left(), true, prefix + (isLeft ? "│   " : "    "));
				rprint_tree(node->right(), false, prefix + (isLeft ? "│   " : "    "));
			}
		}

	public:

		ft::pair<Node *, bool>		insert( value_type key ) { _root = rinsert(_root, key); return _insert_return; }
		Node *		search( value_type key ) const { return rsearch(_root, key); }
		void		print_keys( void ) const { rprint_keys(_root); }
		void		print_tree( void ) const { rprint_tree(_root); }
		Node *		min( void ) const { return rmin(_root); }
		Node *		max( void ) const { return rmax(_root); }
		Node *		root( void ) const { return _root; }
		Node *		end( void ) const { return _null; }
		size_type	size( void ) const { return rsize(_root); }
		size_type	max_size( void ) const { return _alloc.max_size(); }
		void		clear( void ) { rdelete(_root); }

		bool		remove( value_type key ) {
			Node * to_remove = search(key);
			_remove_return = false;
			if ( !to_remove || to_remove == _null )
				return _remove_return;
			if ( to_remove->right() != _null && to_remove->left() != _null ) {
				Node * _tmp = rmin(to_remove->right());
				to_remove->swap(_tmp, _null);
				if ( this->_root == to_remove )
					this->_root = _tmp;
				_tmp->right() = rremove(_tmp->right(), key);
				return _remove_return;
			}
			_root = rremove(_root, key);
			return _remove_return;
		}
		
		void		swap( BinarySearchTree & other ) {
			pointer tmp_root = _root;
			pointer tmp_null = _null;

			_root = other._root;
			_null = other._null;

			other._root = tmp_root;
			other._null = tmp_null;
		}
		

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

		RedBlackTree( value_compare const & cmp = value_compare(), const Alloc& alloc = Alloc() ) : BinarySearchTree( cmp, alloc ) {};
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

		void insert_case4step2( Node * node ) {
			
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
			if ( !node->up() || node->up() == this->_null )
				insert_case1(node);
			else if ( node->up() && node->up() != this->_null && node->up()->getColor() == BLACK )
				insert_case2(node);
			else if ( node->uncle() && node->uncle()->getColor() == RED)
				insert_case3(node);
			else
				insert_case4(node);
		}

	public:

		ft::pair<Node *, bool>	insert( value_type key ) {
			//Node * _new;

			return BinarySearchTree::insert(key);
			// std::cout << *this << std::endl;
			//_new = this->search(key);
			// insert_repair_tree(_new);
			// std::cout << *this << std::endl;
			// std::cout << "root: " << this->_root->getKey().first << std::endl;
			// while ( this->_root->up() && this->_root->up() != this->_null )
			// {
			// 	this->_root = this->_root->up();
			// }
			
		}

		bool	remove( value_type key ) {
			return BinarySearchTree::remove(key);
			// insert_repair_tree(this->_root);
		}

}; /* class RedBlackTree */


#endif /* RED_BLACK_TREE_HPP */