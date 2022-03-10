#ifndef STACK_HPP
# define STACK_HPP

#pragma once

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack {

		/* ------------------------------------------------------------- */
		/* -------------------------- ALIASES -------------------------- */

		public:

			typedef Container							container_type;
			typedef typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
		
		/* ------------------------------------------------------------- */
		/* ----------------------- ATTRIBUTES -------------------------- */

		protected:

			container_type								_c;

		/* ------------------------------------------------------------- */
		/* ---------------- CONSTRUCTORS & DESTRUCTOR ------------------ */
		
		public:

			explicit stack(const Container &cont = Container()) : _c(cont) {};
			~stack() {};

		/* ------------------------------------------------------------- */
		/* ----------------------- ELEMENT ACCESS ---------------------- */

		bool empty(void) const { return _c.empty(); }

		size_type size() const { return _c.size(); }

		value_type &top() { return _c.back(); }
		const value_type &top() const { return _c.back(); }

		template <class T1, class Container1>
		friend bool operator==(const stack<T1,Container1> &lhs, const stack<T1,Container1> &rhs);

		template <class T1, class Container1>
		friend bool operator<(const stack<T1,Container1> &lhs, const stack<T1,Container1> &rhs);

		/* ------------------------------------------------------------- */
		/* ------------------------- MODIFIERS ------------------------- */

		void pop(void) { _c.pop_back(); };

		void push (const value_type &val) { _c.push_back(val); };

	}; // class stack


	/* ------------------------------------------------------------- */
	/* ---------------- NON-MEMBER FUNCTION OVERLOAD --------------- */

	/* 		Relational operators: */

	template <class T, class Container>
	bool operator==(const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return lhs._c == rhs._c;
	}

	template <class T, class Container>
	bool operator < (const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return lhs._c < rhs._c;
	}

	template <class T, class Container>
	bool operator != (const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return rhs < lhs;
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container> &lhs, const stack<T,Container> &rhs) {
		return !(lhs < rhs);
	}

} // namespace ft

#endif /* STACK_HPP */