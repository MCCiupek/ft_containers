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

	template <typename> struct _is_integral_ { static const bool value = false; };

	template <> struct _is_integral_<bool> { static const bool value = true; };
	template <> struct _is_integral_<char> { static const bool value = true; };
	template <> struct _is_integral_<unsigned char> { static const bool value = true; };
	template <> struct _is_integral_<wchar_t> { static const bool value = true; };
	template <> struct _is_integral_<short> { static const bool value = true; };
	template <> struct _is_integral_<unsigned short> { static const bool value = true; };
	template <> struct _is_integral_<int> { static const bool value = true; };
	template <> struct _is_integral_<unsigned int> { static const bool value = true; };
	template <> struct _is_integral_<long> { static const bool value = true; };
	template <> struct _is_integral_<unsigned long> { static const bool value = true; };
	template <> struct _is_integral_<long long> { static const bool value = true; };
	template <> struct _is_integral_<unsigned long long> { static const bool value = true; };

	template <typename T> struct is_integral : public _is_integral_<typename remove_const<T>::type> {};

} /* namespace ft */

#endif /* TYPE_TRAITS_HPP */