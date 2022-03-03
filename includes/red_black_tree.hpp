#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# pragma once
# include <iostream>
# include <iomanip>
# include "utility.hpp"

# define BLACK	0
# define RED	1

# define ARROWS "   /\\   "


template<typename T>
class Node {

	private:

		typedef T					value_type;
		typedef	Node<T> *			pointer;

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
		
		~Node() {
			// if ( !left() && right() )
			// 	*this = *right();
			// else if ( !right() && left() )
			// 	*this = *left();
			// else if ( right() && left() ) {
			// 	pointer _tmp = this->right();
			// 	while ( _tmp->left() )
			// 		_tmp = _tmp->left();
			// 	this->key = _tmp->getKey();
			// 	//_tmp->remove();
			// } else {
			// 	return;
			// 	// std::cout << "del node " << (up()->right() == this ? "right" : "left") << std::endl;
			// 	// std::cout << "parent: " << up()->getKey() << std::endl;
			// 	// Node * p = up();
			// 	// if ( p->right() == this )
			// 	// 	p->right() = NULL;
			// 	// else
			// 	// 	p->left() = NULL;
			// }
		}

		T				getKey() const { return key; };
		void			setKey( value_type _key ) { key = _key; };

		int				getColor() const { return color; };
		void			setColor( int _color ) { color = _color; };

		pointer&		up() { return _up; };
		const pointer&	up() const { return _up; };

		pointer&		left() { return down.first; };
		const pointer&	left() const { return down.first; };

		pointer&		right() { return down.second; };
		const pointer&	right() const { return down.second; };

		void			swap( Node * other ) {
			value_type new_key = other->getKey();
			other->setKey(key);
			key = new_key;
		}

		// void			remove( void ) {
		// 	if ( !left() && right() )
		// 		*this = *right();
		// 	else if ( !right() && left() )
		// 		*this = *left();
		// 	else if ( right() && left() ) {
		// 		pointer _tmp = this;
		// 		_tmp = _tmp->right();
		// 		while ( _tmp->left() )
		// 			_tmp = _tmp->left();
		// 		this->key = _tmp->getKey();
		// 		_tmp->remove();
		// 	} else {
		// 		std::cout << "del node " << (up()->right() == this ? "right" : "left") << std::endl;
		// 		std::cout << "parent: " << up()->getKey() << std::endl;
		// 		Node * p = up();
		// 		if ( p->right() == this )
		// 			p->right() = NULL;
		// 		else
		// 			p->left() = NULL;
		// 		delete this;
		// 	}
		// }

}; /* class Node */

template<typename T>
std::ostream & operator<<( std::ostream &os, const Node<T> & node ) { 
	os << std::setw(4) << node.getKey() << std::setw(4) << " " << std::endl;
	os << ARROWS << std::endl;
	return os;            
}

template<typename T>
class BinarySearchTree {

	public:	

		typedef T					value_type;
		typedef	Node<value_type> 	Node;

	protected:

		Node *						root;

	public:

		BinarySearchTree() : root(NULL) {};
		BinarySearchTree( value_type key ) : root(&Node(key)) {};
		BinarySearchTree( Node * node ) : root(node) {};
		BinarySearchTree( const BinarySearchTree & other ) : root(other.root) {};
		BinarySearchTree& operator=( const BinarySearchTree & other ) {
			if ( this != &other )
				root = other.root;
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

		void rprint_keys( Node * node ) const {
			if (node != NULL) {
				rprint_keys(node->left());
				std::cout << node->getKey() << " ";
				rprint_keys(node->right());
			}
		}

		void rdelete( Node * node ) {
			if (node != NULL) {
				rprint_keys(node->left());
				remove(node->getKey());
				rprint_keys(node->right());
			}
		}

		Node * rsearch( Node * node, int key ) {
			if (node == NULL)
				throw std::out_of_range("KeyError");
			if (node->getKey() == key)
				return node;
			if (node->getKey() < key)
				return rsearch(node->right(), key);
			return rsearch(node->left(), key);
		}

		void rprint_tree( const Node* node, bool isLeft=false, const std::string& prefix="" ) const
		{
			if ( node )
			{
				std::cout << prefix + (isLeft ? "├──" : "└──" );
				std::cout << node->getKey() << std::endl;

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

		

}; /* class BinarySearchTree */

template<typename T>
std::ostream & operator<<( std::ostream &os, const BinarySearchTree<T> & tree ) { 
	
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

template<typename T>
class RedBlackTree : public BinarySearchTree<T> {

	public:

		typedef BinarySearchTree<T>						BinarySearchTree;
		typedef typename BinarySearchTree::value_type	value_type;
		typedef	typename BinarySearchTree::Node			Node;

	public:

		RedBlackTree() : BinarySearchTree() {};
		RedBlackTree( value_type key ) : BinarySearchTree(key) {};
		RedBlackTree( Node * node ) : BinarySearchTree(node) {};
		RedBlackTree( const BinarySearchTree & other ) : BinarySearchTree(other) {};
		RedBlackTree& operator=( const RedBlackTree & other ) {
			if ( this != &other )
				this->root = other.root;
			return *this;
		};
		~RedBlackTree() {};

	private:

		void lrotate(Node * x) {
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

		void rrotate(Node * x) {
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

		void recolor(Node * x) {
			if ( x->getColor() == RED )
				x->setColor(BLACK);
			else
				x->setColor(RED);
		}

	public:

		void	insert( value_type key ) {

			BinarySearchTree::insert(key);

			Node * _uncle;
			Node * _new = this->search(key);

			std::cout << "insert ok" << std::endl;


			while ( _new->up() && _new->up()->getColor() == RED ) {
				if (_new->up()->up() && _new->up() == _new->up()->up()->right() ) {
					_uncle = _new->up()->up()->left();
					if ( _uncle->getColor() == RED ) {
						_uncle->setColor(BLACK);
						_new->up()->setColor(BLACK);
						_new->up()->up()->setColor(RED);
						_new = _new->up()->up();
					}
					else if ( _new == _new->up()->left() ) {
						_new = _new->up();
						rrotate(_new);
					}
					_new->up()->setColor(BLACK);
					_new->up()->up()->setColor(RED);
					lrotate(_new->up()->up());
				} else {
					_uncle = _new->up()->up()->right();
					if ( _uncle->getColor() == RED ) {
						_uncle->setColor(BLACK);
						_new->up()->setColor(BLACK);
						_new->up()->up()->setColor(RED);
						_new = _new->up()->up();
					}
					else if ( _new == _new->up()->right() ) {
						_new = _new->up();
						lrotate(_new);
					}
					_new->up()->setColor(BLACK);
					_new->up()->up()->setColor(RED);
					rrotate(_new->up()->up());
				}
				if (_new == this->root)
					break;
			}

			this->root->setColor(BLACK);
		};


}; /* class RedBlackTree */


#endif /* RED_BLACK_TREE_HPP */