/*
* export-giggle
* Hash.hpp
* Created by Nuno Levezinho on 22/08/2018.
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

#ifndef EXPORT_GIGGLE_HASH_HPP
#define EXPORT_GIGGLE_HASH_HPP

#include <cstddef>
#include <Types.hpp>
#include <string>

namespace giggle::common::security
{

	std::size_t hash(Int8 n);
	std::size_t hash(UInt8 n);
	std::size_t hash(Int16 n);
	std::size_t hash(UInt16 n);
	std::size_t hash(Int32 n);
	std::size_t hash(UInt32 n);
	std::size_t hash(Int64 n);
	std::size_t hash(UInt64 n);
	std::size_t hash(const std::string& l_str);

	/**
	 * A generic hash function.
	 *
	 * @tparam T
	 */
	template <class T>
	struct Hash
	{
		std::size_t operator () (T l_value) const
		{
			return hash(l_value);
		}
	};

	/**
	 * Inlines
	 */

	inline std::size_t hash(Int8 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(UInt8 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(Int16 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(UInt16 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(Int32 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(UInt32 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(Int64 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

	inline std::size_t hash(UInt64 n)
	{
		return static_cast<std::size_t>(n)*2654435761U;
	}

} // namespace security

#endif //EXPORT_GIGGLE_HASH_HPP
