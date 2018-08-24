/*
* export-giggle
* UTF8.hpp
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

#ifndef EXPORT_GIGGLE_UTF8STRING_HPP
#define EXPORT_GIGGLE_UTF8STRING_HPP

#include <string>

namespace giggle::common::formatting
{

	/**
	 * This class provides static methods that are UTF-8 capable variants
	 * of the same functions in common/String.h.
	 *
	 * The various variants of icompare() provide case insensitive comparison
	 * for UTF-8 encoded strings.
	 *
	 * toUpper(), toUpperInPlace(), toLower() and toLowerInPlace() provide
	 * Unicode-based character case transformation for UTF-8 encoded strings.
	 *
	 * removeBOM() removes the UTF-8 Byte Order Mark sequence (0xEF, 0xBB, 0xBF)
	 * from the beginning of the given string, if it's there.
	 */
	struct UTF8
	{
		static int ICompare(const std::string &str, std::string::size_type pos, std::string::size_type n,
							std::string::const_iterator it2, std::string::const_iterator end2);
		static int ICompare(const std::string &str1, const std::string &str2);
		static int ICompare(const std::string &str1, std::string::size_type n1, const std::string &str2,
							std::string::size_type n2);
		static int ICompare(const std::string &str1, std::string::size_type n, const std::string &str2);
		static int ICompare(const std::string &str1, std::string::size_type pos, std::string::size_type n,
							const std::string &str2);
		static int ICompare(const std::string &str1, std::string::size_type pos1, std::string::size_type n1,
							const std::string &str2, std::string::size_type pos2, std::string::size_type n2);
		static int ICompare(const std::string &str1, std::string::size_type pos1, std::string::size_type n,
							const std::string &str2, std::string::size_type pos2);
		static int ICompare(const std::string &str, std::string::size_type pos, std::string::size_type n,
							const std::string::value_type *ptr);
		static int ICompare(const std::string &str, std::string::size_type pos, const std::string::value_type *ptr);
		static int ICompare(const std::string &str, const std::string::value_type *ptr);

		static std::string ToUpper(const std::string &str);
		static std::string& ToUpperInPlace(std::string &str);
		static std::string ToLower(const std::string &str);
		static std::string& ToLowerInPlace(std::string &str);

		/**
		 * Remove the UTF-8 Byte Order Mark sequence (0xEF, 0xBB, 0xBF)
		 * from the beginning of the string, if it's there.
		 *
		 * @param str
		 */
		static void RemoveBOM(std::string &str);

		/**
		 * Escapes a string. Special characters like tab, backslash, ... are
		 * escaped. Unicode characters are escaped to \uxxxx.
		 * If strictJSON is true, \a and \v will be escaped to \\u0007 and \\u000B
		 * instead of \\a and \\v for strict JSON conformance.
		 * @param s
		 * @param strictJSON
		 * @return
		 */
		static std::string Escape(const std::string &s, bool strictJSON = false);

		/**
		 * Escapes a string. Special characters like tab, backslash, ... are
		 * escaped. Unicode characters are escaped to \uxxxx.
		 * If strictJSON is true, \a and \v will be escaped to \\u0007 and \\u000B
		 * instead of \\a and \\v for strict JSON conformance.
		 *
		 * @param begin
		 * @param end
		 * @param strictJSON
		 * @return
		 */
		static std::string Escape(const std::string::const_iterator &begin, const std::string::const_iterator &end,
								  bool strictJSON = false);

		/**
		 * Creates an UTF8 string from a string that contains escaped characters.
		 *
		 * @param s
		 * @return
		 */
		static std::string Unescape(const std::string &s);

		/**
		 * Creates an UTF8 string from a string that contains escaped characters.
		 *
		 * @param begin
		 * @param end
		 * @return
		 */
		static std::string Unescape(const std::string::const_iterator &begin, const std::string::const_iterator &end);
	};

}




#endif //EXPORT_GIGGLE_UTF8STRING_HPP
