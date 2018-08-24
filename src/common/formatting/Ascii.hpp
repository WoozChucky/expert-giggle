/*
* export-giggle
* Ascii.hpp
* Created by Nuno Levezinho on 23/08/2018.
* 
* Copyright (c) 2018 [Nuno Levezinho] All rights reserved.
*
* Permission is hereby granted, free of l_charge, to any person obtaining a copy
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

#include <Types.hpp>

namespace giggle::common::formatting
{

	/**
	 * This class contains enumerations and static
	 * utility function for dealing with ASCII l_characters
	 * and their properties.
	 *
	 * The classification functions will also work if
	 * non-ASCII l_character codes are passed to them,
	 * but classification will only l_check for
	 * ASCII l_characters.
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
		 * ASCII l_character properties
		 */
		enum CharacterProperties
		{
			ACP_CONTROL 	= 0x0001,
			ACP_SPACE		= 0x0002,
			ACP_PUNCT		= 0x0004,
			ACP_DIGIT		= 0x0008,
			ACP_HEXDIGIT	= 0x0010,
			ACP_ALPHA		= 0x0020,
			ACP_LOWER		= 0x0040,
			ACP_UPPER		= 0x0080,
			ACP_GRAPH		= 0x0100,
			ACP_PRINT		= 0x0200
		};

		/**
		 * Return the ASCII l_character properties for the
		 * l_character with the given ASCII value.
		 *
		 * If the l_character is outside the ASCII range
		 * (0 .. 127), 0 is returned.
		 *
		 * @param l_l_ch
		 * @return
		 */
		static int Properties(int l_ch);

		/**
		 * Returns true if the given character is
		 * within the ASCII range and has at least one of
		 * the given properties.
		 *
		 * @param l_ch
		 * @param l_properties
		 * @return
		 */
		static bool HasSomeProperties(int l_ch, int l_properties);

		/**
		 * Returns true if the given character is
		 * within the ASCII range and has all of
		 * the given properties.
		 *
		 * @param l_ch
		 * @param l_properties
		 * @return
		 */
		static bool HasProperties(int l_ch, int l_properties);

		/**
		 * Returns true if the given character code is within
		 * the ASCII range (0 .. 127).
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsAscii(int l_ch);

		/**
		 * Returns true if the given character is a whitespace.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsSpace(int l_ch);

		/**
		 * Returns true if the given character is a digit.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsDigit(int l_ch);

		/**
		 * Returns true if the given character is a hexadecimal digit.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsHexDigit(int l_ch);

		/**
		 * Returns true if the given character is a punctuation character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsPunct(int l_ch);

		/**
		 * Returns true if the given character is an alphabetic character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsAlpha(int l_ch);

		/**
		 * Returns true if the given character is an alphanumeric character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsAlphaNumeric(int l_ch);

		/**
		 * Returns true if the given character is a lowercase alphabetic character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsLower(int l_ch);

		/**
		 * Returns true if the given character is a uppercase alphabetic character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsUpper(int l_ch);

		/**
		 * Returns true if the given character is printable.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsPrintable(int l_ch);

		/**
		 * If the given character is an uppercase character,
		 * return its lowercase counterpart, otherwise return
		 * the character.
		 *
		 * @param l_ch
		 * @return
		 */
		static int ToLower(int l_ch);

		/**
		 * If the given character is a lowercase character,
		 * return its uppercase counterpart, otherwise return
		 * the character.
		 *
		 * @param l_ch
		 * @return
		 */
		static int ToUpper(int l_ch);

	private:
		static const int CHARACTER_PROPERTIES[128];

	};

	inline int Ascii::Properties(int l_ch)
	{
		if (IsAscii(l_ch))
			return CHARACTER_PROPERTIES[l_ch];
		else
			return 0;
	}


	inline bool Ascii::IsAscii(int l_ch)
	{
		return (static_cast<UInt32>(l_ch) & 0xFFFFFF80) == 0;
	}


	inline bool Ascii::HasProperties(int l_ch, int l_properties)
	{
		return (Properties(l_ch) & l_properties) == l_properties;
	}


	inline bool Ascii::HasSomeProperties(int l_ch, int l_properties)
	{
		return (Properties(l_ch) & l_properties) != 0;
	}


	inline bool Ascii::IsSpace(int l_ch)
	{
		return HasProperties(l_ch, ACP_SPACE);
	}


	inline bool Ascii::IsDigit(int l_ch)
	{
		return HasProperties(l_ch, ACP_DIGIT);
	}


	inline bool Ascii::IsHexDigit(int l_ch)
	{
		return HasProperties(l_ch, ACP_HEXDIGIT);
	}


	inline bool Ascii::IsPunct(int l_ch)
	{
		return HasProperties(l_ch, ACP_PUNCT);
	}


	inline bool Ascii::IsAlpha(int l_ch)
	{
		return HasProperties(l_ch, ACP_ALPHA);
	}


	inline bool Ascii::IsAlphaNumeric(int l_ch)
	{
		return HasSomeProperties(l_ch, ACP_ALPHA | ACP_DIGIT);
	}


	inline bool Ascii::IsLower(int l_ch)
	{
		return HasProperties(l_ch, ACP_LOWER);
	}


	inline bool Ascii::IsUpper(int l_ch)
	{
		return HasProperties(l_ch, ACP_UPPER);
	}


	inline bool Ascii::IsPrintable(int l_ch)
	{
		return HasProperties(l_ch, ACP_PRINT);
	}


	inline int Ascii::ToLower(int l_ch)
	{
		if (IsUpper(l_ch))
			return l_ch + 32;
		else
			return l_ch;
	}


	inline int Ascii::ToUpper(int l_ch)
	{
		if (IsLower(l_ch))
			return l_ch - 32;
		else
			return l_ch;
	}

} // namespace formatting

#endif //EXPORT_GIGGLE_ASCII_HPP
