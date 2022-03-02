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
		Node						*up;
		ft::pair<pointer, pointer>	down;
		int							color;

	public: 

		Node( void ) : 
			key(T()), up(NULL), down(NULL, NULL), color(BLACK) {}

		Node( T key ) : 
			key(key), up(NULL), down(NULL, NULL), color(BLACK) { std::cout << "item created!" << std::endl; }
		
		Node( const Node & other ) : 
			key(other.key), up(other.up), down(other.down), color(other.color) {}

		Node& operator=( const Node & other ) {
				if ( this != &other ) {
					key = other.key;
					up = other.up;
					color = other.color;
				}
				return *this;
			};
		
		~Node() {}

		T				getKey() const { return key; };

		pointer&		left() { return down.first; };
		const pointer&	left() const { return down.first; };

		pointer&		right() { return down.second; };
		const pointer&	right() const { return down.second; };

}; /* class Node */

template<typename T>
std::ostream & operator<<( std::ostream &os, const Node<T> & node ) { 
	os << std::setw(4) << node.getKey() << std::setw(4) << " " << std::endl;
	os << ARROWS << std::endl;
	return os;            
}


template<typename T>
class Tree {

	private:

		typedef T					value_type;
		typedef	Node<value_type> 	Node;

		Node *						root;

	public:

		Tree() : root(NULL) {};
		Tree( value_type key ) : root(&Node(key)) {};
		Tree( Node * node ) : root(node) {};

	private:

		Node * rinsert( Node * node, value_type key ) { 
			if ( !node )
				return new Node(key);
			if ( key < node->getKey() )
			 	node->left() = rinsert(node->left(), key);
			else if ( key > node->getKey() )
			 	node->right() = rinsert(node->right(), key);
			return node;
		}

		void rprint_keys( Node *node ) {
			if (node != NULL){
				rprint_keys(node->left());
				std::cout << node->getKey() << std::endl;
				rprint_keys(node->right());
		   }
		}

		Node * rsearch( Node* node, int key ) {
			if (node == NULL)
				throw std::out_of_range("KeyError");
			if (node->getKey() == key)
				return node;
			if (node->getKey() < key)
				return rsearch(node->right(), key);
			return rsearch(node->left(), key);
		}

	public:

		void	insert( value_type key ) { root = rinsert(root, key); }
		Node *	search( value_type key ) { return rsearch(root, key); }
		void	print_keys( void ) { rprint_keys(root); }

}; /* class Tree */

#endif /* RED_BLACK_TREE_HPP */