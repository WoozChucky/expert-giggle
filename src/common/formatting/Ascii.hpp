/*
* export-giggle
* Ascii.hpp
* Created by Nuno Levezinho on 23/08/2018.
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

#ifndef EXPORT_GIGGLE_ASCII_HPP
#define EXPORT_GIGGLE_ASCII_HPP

namespace giggle::common::formatting
{

	/**
	 * This class contains enumerations and static
	 * utility function for dealing with ASCII characters
	 * and their properties.
	 *
	 * The classification functions will also work if
	 * non-ASCII character codes are passed to them,
	 * but classification will only check for
	 * ASCII characters.
	 *
	 * This allows the classification methods to be used
	 * on the single bytes of a UTF-8 string, without
	 * causing assertions or inconsistent results (depending
	 * upon the current locale) on bytes outside ASCII range,
	 * as may be produced by Ascii::IsScape(), etc.
	 */
	class Ascii
	{

	public:
		/**
		 * ASCII character properties
		 */
		enum CharacterProperties
		{
			ACP_CONTROL 	= 0x0001,
			ACP_SPACE		= 0x0002,
			ACP_PUNCT		= 0x0004,
			ACP_DIGIT		= 0x0008,
			ACP_HEXGIDIT	= 0x0010,
			ACP_ALPHA		= 0x0020,
			ACP_LOWER		= 0x0040,
			ACP_UPPER		= 0x0080,
			ACP_GRAPH		= 0x0100,
			ACP_PINT		= 0x0200
		};

		/**
		 * Return the ASCII character properties for the
		 * character with the given ASCII value.
		 *
		 * If the character is outside the ASCII range
		 * (0 .. 127), 0 is returned.
		 *
		 * @param l_ch
		 * @return
		 */
		static int Properties(int l_ch);

		static bool HasSomeProperties(int l_ch, int l_properties);

		static bool HasProperties(int l_ch, int l_properties);

		static bool IsAcii(int l_ch);

		static bool IsSpace(int l_ch);

		static bool IsDigit(int l_ch);

		static bool IsHexDigit(int l_ch);

		static bool IsPunct(int l_ch);

		static bool IsAlpha(int l_ch);

	private:
		static const int CHARACTER_PROPERTIES[128];

	};

} // namespace formatting

#endif //EXPORT_GIGGLE_ASCII_HPP
