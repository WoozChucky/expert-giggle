/*
* export-giggle
* HashFunction.hpp
* Created by Nuno Levezinho on 24/08/2018.
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

#ifndef EXPORT_GIGGLE_HASHFUNCTION_HPP
#define EXPORT_GIGGLE_HASHFUNCTION_HPP

#include <Types.hpp>
#include "Hash.hpp"

namespace giggle::common::security
{

	template <class T>
	struct HashFunction
	{
		/**
		 * A generic hash function.
		 *
		 * @param key
		 * @param l_maxValue
		 * @return
		 */
		UInt32 operator () (T l_key, UInt32 l_maxValue) const
		{
			return static_cast<UInt32>(Hash(l_key)) % l_maxValue;
		}
	};

	template <>
	struct HashFunction<std::string>
	{
		/**
		 * A generic hash function.
		 *
		 * @param key
		 * @param l_maxValue
		 * @return
		 */
		UInt32 operator () (const std::string& l_key, UInt32 l_maxValue) const
		{
			return static_cast<UInt32>(Hash(l_key)) % l_maxValue;
		}
	};

} // namespace security

#endif //EXPORT_GIGGLE_HASHFUNCTION_HPP
