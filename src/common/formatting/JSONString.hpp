/*
* export-giggle
* JSONString.hpp
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

#ifndef EXPORT_GIGGLE_JSONSTRING_HPP
#define EXPORT_GIGGLE_JSONSTRING_HPP

#include <ostream>
#include <string>

namespace giggle::common::formatting
{

	enum JSONOptions
	{
		/**
		 * Applies to JSON::Object. If specified, the Object will
		 * preserve the item insertion order. Otherwise, items
		 * will be sorted by keys.
		 *
		 * Has no effect on toJSON() function.
		 */
		JSON_PRESERVE_KEY_ORDER = 1,

		/**
		 * If specified, when the object is stringified, all
		 * unicode characters will be escaped in the resulting
		 * string.
		 */
		JSON_ESCAPE_UNICODE = 2,

		/**
		 * If specified, the object will preserve the items
		 * insertion order. Otherwise, items will be sorted by keys.
		 */
		JSON_WRAP_STRINGS = 4
	};

	/**
	 * Formats string value into the supplied output stream by
	 * escaping control characters.
	 * If JSON_WRAP_STRINGS is in options, the resulting strings is enclosed in double quotes
	 * If JSON_ESCAPE_UNICODE is in options, all unicode characters will be escaped, otherwise
	 * only the compulsory ones.
	 *
	 * @param l_value
	 * @param l_options
	 */
	void toJSON(const std::string& l_value, std::ostream& l_out, int l_options);

	/**
	 * Formats string value by escaping control characters.
	 * If JSON_WRAP_STRINGS is in options, the resulting string is enclosed in double quotes
	 * If JSON_ESCAPE_UNICODE is in options, all unicode characters will be escaped, otherwise
	 * only the compulsory ones.
	 *
	 * If escapeAllUnicode is true, all unicode characters will be escaped, otherwise only the compulsory ones.
	 *
	 * @param l_value
	 * @param l_options
	 * @return formatted string
	 */
	std::string toJSON(const std::string& l_value, int l_options);

} // namespace formatting




#endif //EXPORT_GIGGLE_JSONSTRING_HPP
