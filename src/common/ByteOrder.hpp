/*
* export-giggle
* ByteOrder.hpp
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

#ifndef EXPORT_GIGGLE_BYTEORDER_HPP
#define EXPORT_GIGGLE_BYTEORDER_HPP

#include <Types.hpp>
#include <algorithm>

namespace giggle::common
{
	/**
	 * @brief This class contains a number of static methods
	 * to convert between big-endian and little-endian
	 * integers of various sizes.
	 */
	class ByteOrder
	{
	public:
		static Int16 flipBytes(Int16 value);
		static UInt16 flipBytes(UInt16 value);
		static Int32 flipBytes(Int32 value);
		static UInt32 flipBytes(UInt32 value);
		static float flipBytes(float value);
		static double flipBytes(double value);

		static Int64 flipBytes(Int64 value);
		static UInt64 flipBytes(UInt64 value);


		static Int16 toBigEndian(Int16 value);
		static UInt16 toBigEndian (UInt16 value);
		static Int32 toBigEndian(Int32 value);
		static UInt32 toBigEndian (UInt32 value);

		static Int64 toBigEndian(Int64 value);
		static UInt64 toBigEndian (UInt64 value);


		static Int16 fromBigEndian(Int16 value);
		static UInt16 fromBigEndian (UInt16 value);
		static Int32 fromBigEndian(Int32 value);
		static UInt32 fromBigEndian (UInt32 value);

		static Int64 fromBigEndian(Int64 value);
		static UInt64 fromBigEndian (UInt64 value);


		static Int16 toLittleEndian(Int16 value);
		static UInt16 toLittleEndian (UInt16 value);
		static Int32 toLittleEndian(Int32 value);
		static UInt32 toLittleEndian (UInt32 value);

		static Int64 toLittleEndian(Int64 value);
		static UInt64 toLittleEndian (UInt64 value);


		static Int16 fromLittleEndian(Int16 value);
		static UInt16 fromLittleEndian (UInt16 value);
		static Int32 fromLittleEndian(Int32 value);
		static UInt32 fromLittleEndian (UInt32 value);

		static Int64 fromLittleEndian(Int64 value);
		static UInt64 fromLittleEndian (UInt64 value);


		static Int16 toNetwork(Int16 value);
		static UInt16 toNetwork (UInt16 value);
		static Int32 toNetwork(Int32 value);
		static UInt32 toNetwork (UInt32 value);

		static Int64 toNetwork(Int64 value);
		static UInt64 toNetwork (UInt64 value);


		static Int16 fromNetwork(Int16 value);
		static UInt16 fromNetwork (UInt16 value);
		static Int32 fromNetwork(Int32 value);
		static UInt32 fromNetwork (UInt32 value);

		static Int64 fromNetwork(Int64 value);
		static UInt64 fromNetwork (UInt64 value);

	private:
		template <typename T>
		static T Flip(T value)
		{
			T 			flip 		= value;
			std::size_t halfSize 	= sizeof(T) / 2;
			char*		flipP		= reinterpret_cast<char*>(&flip);

			for(std::size_t i = 0; i < halfSize; i++)
				std::swap(flipP[i], flipP[sizeof(T) - i - 1]);
			return flip;
		}

	};

	inline UInt16 ByteOrder::flipBytes(UInt16 value)
	{
		return static_cast<UInt16>(((value >> 8) & 0x00FF) | ((value << 8) & 0xFF00));
	}

	inline Int16 ByteOrder::flipBytes(Int16 value)
	{
		return Int16(flipBytes(UInt16(value)));
	}

	inline UInt32 ByteOrder::flipBytes(UInt32 value)
	{
		return ((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00)
			   | ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000);
	}

	inline Int32 ByteOrder::flipBytes(Int32 value)
	{
		return Int32(flipBytes(UInt32(value)));
	}


	inline float ByteOrder::flipBytes(float value)
	{
		return Flip(value);
	}


	inline double ByteOrder::flipBytes(double value)
	{
		return Flip(value);
	}

	inline UInt64 ByteOrder::flipBytes(UInt64 value)
	{
		auto hi = UInt32(value >> 32);
		auto lo = UInt32(value & 0xFFFFFFFF);
		return UInt64(flipBytes(hi)) | (UInt64(flipBytes(lo)) << 32);
	}


	inline Int64 ByteOrder::flipBytes(Int64 value)
	{
		return Int64(flipBytes(UInt64(value)));
	}

	/**
	 * Some macro trickery to automate the method implementation.
	 */

#define COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, type)	\
	inline type ByteOrder::op(type value) \
	{										\
		return value;							\
	}
#define COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, type) \
	inline type ByteOrder::op(type value)		\
	{											\
		return flipBytes(value);				\
	}

#define COMMON_IMPLEMENT_BYTEORDER_NOOP(op) \
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, Int16)	\
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, UInt16)	\
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, Int32)	\
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, UInt32)	\
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, Int64)	\
		COMMON_IMPLEMENT_BYTEORDER_NOOP_(op, UInt64)
#define COMMON_IMPLEMENT_BYTEORDER_FLIP(op) \
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, Int16)	\
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, UInt16)	\
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, Int32)	\
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, UInt32)	\
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, Int64)	\
		COMMON_IMPLEMENT_BYTEORDER_FLIP_(op, UInt64)


/*
 * This piece of code should be used for BigEndian Architectures
 * #define COMMON_IMPLEMENT_BYTEORDER_BIG COMMON_IMPLEMENT_BYTEORDER_NOOP
 * #define COMMON_IMPLEMENT_BYTEORDER_LIT COMMON_IMPLEMENT_BYTEORDER_FLIP
 */
#define COMMON_IMPLEMENT_BYTEORDER_BIG COMMON_IMPLEMENT_BYTEORDER_FLIP
#define COMMON_IMPLEMENT_BYTEORDER_LIT COMMON_IMPLEMENT_BYTEORDER_NOOP

	COMMON_IMPLEMENT_BYTEORDER_BIG(toBigEndian)
	COMMON_IMPLEMENT_BYTEORDER_BIG(fromBigEndian)
	COMMON_IMPLEMENT_BYTEORDER_BIG(toNetwork)
	COMMON_IMPLEMENT_BYTEORDER_BIG(fromNetwork)
	COMMON_IMPLEMENT_BYTEORDER_LIT(toLittleEndian)
	COMMON_IMPLEMENT_BYTEORDER_LIT(fromLittleEndian)
}


#endif //EXPORT_GIGGLE_BYTEORDER_HPP
