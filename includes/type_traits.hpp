#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

# pragma once
# include <iostream>
# include <stdint.h>

namespace ft
{
	/* ------------------------------------------------------------- */
	/* ------------------------ ENABLE IF -------------------------- */

	template <bool B, class T = void> struct enable_if {};
	template <class T> struct enable_if<true, T> { typedef T type; };

	/* ------------------------------------------------------------- */
	/* ----------------------- REMOVE CONST ------------------------ */

	template <class T> struct remove_const { typedef T type; };
	template <class T> struct remove_const<const T> { typedef T type; };

	/* ------------------------------------------------------------- */
	/* ------------------------ IS_INTEGRAL ------------------------- */

	template <typename> struct __is_integral { static const bool value = false; };

	template <> struct __is_integral<bool> { static const bool value = true; };
	template <> struct __is_integral<char> { static const bool value = true; };
	template <> struct __is_integral<unsigned char> { static const bool value = true; };
	template <> struct __is_integral<wchar_t> { static const bool value = true; };
	template <> struct __is_integral<short> { static const bool value = true; };
	template <> struct __is_integral<unsigned short> { static const bool value = true; };
	template <> struct __is_integral<int> { static const bool value = true; };
	template <> struct __is_integral<unsigned int> { static const bool value = true; };
	template <> struct __is_integral<long> { static const bool value = true; };
	template <> struct __is_integral<unsigned long> { static const bool value = true; };
	template <> struct __is_integral<long long> { static const bool value = true; };
	template <> struct __is_integral<unsigned long long> { static const bool value = true; };

	template <typename T> struct is_integral : public __is_integral<typename remove_const<T>::type> {};

} /* namespace ft */

#endif /* TYPE_TRAITS_HPP */