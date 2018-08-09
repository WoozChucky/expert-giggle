/*
* export-giggle
* Array.hpp
* Created by Nuno Levezinho on 8/9/2018.
* 
* Copyright (c) 2018 [Nuno Levezinho] All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*/

#ifndef EXPORT_GIGGLE_ARRAY_HPP
#define EXPORT_GIGGLE_ARRAY_HPP


#include <cstdio>
#include <array>

namespace giggle::common
{

	/**
	 * @brief STL container like C-style array replacement class.
	 *
	 * This implementation is based on the idea of Nicolai Josuttis.
	 * http://www.josuttis.com/cppcode/array.html
	 */
	template <class T, std::size_t N>
	class Array : public std::array<T, N>
	{
	public:
		Array() : std::array<T,N>()
		{

		}

		template <typename ... X>
		explicit Array(T t, X... xs):
			std::array<T, N>::array { {t, xs...} }
		{

		}

		Array(std::initializer_list<T> list):
			std::array<T, N>::array()
		{

		}

		enum { static_size = N };

		/**
		 * @brief Use array as C array (direct read/write access to data)
		 */
		T* c_array()
		{
			return this->data();
		}

		/**
		 * @brief Assignment with type conversion
		 */
		template <typename Other>
		Array<T, N>& operator= (const Array<Other, N>& rhs)
		{
			std::copy(rhs.begin(), rhs.end(), this->begin());
			return *this;
		}

		/**
		 * @brief Assign one value to all elements
		 * @param l_value The value
		 */
		void Assign(const T& l_value)
		{
			std::fill(this->begin(), this->size(), l_value);
		}
	};

} // namespace common

#endif //EXPORT_GIGGLE_ARRAY_HPP
