/*
* export-giggle
* JSONString.cpp
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

#include <ostream>
#include "JSONString.hpp"

using namespace giggle::common::formatting;

namespace
{
	template <typename  T, typename S>
	struct WriteFunc
	{
		typedef  T& (T::*Type)(const char* s, S n);
	};

	template <typename T, typename S>
	void writeString(const std::string &l_value, T& l_obj, typename WriteFunc<T, S>::Type l_write, int l_options)
	{
		bool wrap = ((l_options & JSONOptions::JSON_WRAP_STRINGS) != 0);
		bool escapeAllUnicode= ((l_options & JSONOptions::JSON_ESCAPE_UNICODE) != 0);

		if (l_value.empty())
		{
			if (wrap) (l_obj.*l_write)("\"\"", 2);
			return;
		}

		if (wrap) (l_obj.*l_write)("\"", 1);

		if (escapeAllUnicode)
		{
			std::string str = UTF8::escape(l_value.begin(), l_value.end(), true);
			(l_obj.*l_write)(str.c_str(), str.size());
		}
		else
		{
			for(auto it = l_value.begin(), end = l_value.end(); it != end; ++it)
			{
				// Forward slash isn't strictly required by JSON spec, but some parser expect it.
				if ((*it >= 0 && *it <= 31) || (*it == '"') || (*it == '\\') || (*it == '/'))
				{
					std::string str = UTF8::escape(it, it + 1, true);
					(l_obj.*l_write)(str.c_str(), str.size());
				}
				else
				{
					(l_obj.*l_write)(&(*it), 1);
				}
			}

		}

		if (wrap) (l_obj.*l_write)("\"", 1);
	}

} // namespace

void giggle::common::formatting::toJSON(const std::string& l_value, std::ostream& l_out, int l_options)
{
	writeString<std::ostream, std::streamsize>(l_value, l_out, &std::ostream::write, l_options);
}

std::string giggle::common::formatting::toJSON(const std::string& l_value, int l_options)
{
	std::string ret;

	writeString<std::string, std::string::size_type>(l_value, ret, &std::string::append, l_options);

	return ret;
}
