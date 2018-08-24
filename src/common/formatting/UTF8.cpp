/*
* export-giggle
* UTF8.cpp
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

#include "UTF8.hpp"

using namespace giggle::common::formatting;

int UTF8::ICompare(const std::string &str, std::string::size_type pos,
				   std::string::size_type n, std::string::const_iterator it2,
				   std::string::const_iterator end2)
{
	// TODO: Implement
	return 0;
}

int UTF8::ICompare(const std::string &str1, const std::string &str2)
{
	return ICompare(str1, 0, str1.size(), str2.begin(), str2.end());
}

int UTF8::ICompare(const std::string &str1, std::string::size_type n1,
				   const std::string &str2, std::string::size_type n2)
{
	if (n2 > str2.size()) n2 = str2.size();
	return ICompare(str1, 0, n1, str2.begin(), str2.begin() + n2);
}

int UTF8::ICompare(const std::string &str1, std::string::size_type n,
				   const std::string &str2)
{
	if (n > str2.size()) n = str2.size();
	return ICompare(str1, 0, n, str2.begin(), str2.begin() + n);
}

int UTF8::ICompare(const std::string &str1, std::string::size_type pos,
				   std::string::size_type n, const std::string &str2)
{
	return ICompare(str1, pos, n, str2.begin(), str2.end());
}

int UTF8::ICompare(const std::string &str1, std::string::size_type pos1,
				   std::string::size_type n1, const std::string &str2,
				   std::string::size_type pos2, std::string::size_type n2)
{
	std::string::size_type sz2 = str2.size();
	if (pos2 > sz2) pos2 = sz2;
	if (pos2 + n2 > sz2) n2 = sz2 - pos2;
	return ICompare(str1, pos1, n1, str2.begin() + pos2, str2.begin() + pos2 + n2);
}

int UTF8::ICompare(const std::string &str1, std::string::size_type pos1,
				   std::string::size_type n, const std::string &str2,
				   std::string::size_type pos2)
{
	std::string::size_type sz2 = str2.size();
	if (pos2 > sz2) pos2 = sz2;
	if (pos2 + n > sz2) n = sz2 - pos2;
	return ICompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
}

int UTF8::ICompare(const std::string &str, std::string::size_type pos,
				   std::string::size_type n, const std::string::value_type *ptr)
{
	std::string str2(ptr); // TODO: optimize
	return ICompare(str, pos, n, str2.begin(), str2.end());
}

int UTF8::ICompare(const std::string &str, std::string::size_type pos,
				   const std::string::value_type *ptr)
{
	return ICompare(str, pos, str.size() - pos, ptr);
}

int UTF8::ICompare(const std::string &str, const std::string::value_type *ptr)
{
	return ICompare(str, 0, str.size(), ptr);
}

std::string UTF8::ToUpper(const std::string &str)
{
	return std::string();
}

std::string &UTF8::ToUpperInPlace(std::string &str)
{
	std::string* s;
	return *s;
}

std::string UTF8::ToLower(const std::string &str)
{
	return std::string();
}

std::string &UTF8::ToLowerInPlace(std::string &str)
{
	std::string* s;
	return *s;
}

void UTF8::RemoveBOM(std::string &str)
{

}

std::string UTF8::Escape(const std::string &s, bool strictJSON)
{
	return std::string();
}

std::string UTF8::Escape(const std::string::const_iterator &begin,
						 const std::string::const_iterator &end, bool strictJSON)
{
	return std::string();
}

std::string UTF8::Unescape(const std::string &s)
{
	return std::string();
}

std::string UTF8::Unescape(const std::string::const_iterator &begin,
						   const std::string::const_iterator &end)
{
	return std::string();
}
